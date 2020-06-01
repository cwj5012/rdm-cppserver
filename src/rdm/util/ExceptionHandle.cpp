#ifdef WIN32

#include "ExceptionHandle.h"

#include <stdlib.h>
#include <signal.h>
#include <new.h>
#include <eh.h>
#include <time.h>
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <dbghelp.h>
#include <intrin.h>

#pragma comment(lib, "dbghelp.lib")

int localtime(
        struct tm* t,
        const time_t* time
) {
    int ret = 0;
#ifdef WIN32
    ret = localtime_s(t, time);
#else
#error platform is not supported.
#endif
    return ret;
}

int sprintf(
        char* buffer,
        size_t sizeOfBuffer,
        const char* format,
        ...
) {
    int ret = 0;
#ifdef WIN32
    va_list arglist;
            va_start(arglist, format);
    ret = _vsprintf_s_l(buffer, sizeOfBuffer, format, NULL, arglist);
            va_end(arglist);
#else
#error platform is not supported.
#endif
    return ret;
}

int vsprintf(
        char* buffer,
        size_t sizeOfBuffer,
        const char* format,
        va_list argptr
) {
    int ret = 0;
#ifdef WIN32
    ret = _vsprintf_s_l(buffer, sizeOfBuffer, format, NULL, argptr);
#else
#error platform is not supported.
#endif
    return ret;
}

void* _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)

#if defined (_M_IX86) || defined (_M_X64)
void* _AddressOfReturnAddress(void);
#pragma intrinsic(_AddressOfReturnAddress)
#endif  /* defined (_M_IX86) || defined (_M_X64) */

// custom exception code
#define CUSTOM_EXCEPTION_CODE_SIGNAL_ABORT            0xF0000001
#define CUSTOM_EXCEPTION_CODE_SIGNAL_FPE            0xF0000002
#define CUSTOM_EXCEPTION_CODE_INVALID_PARAMERTER    0xF0000010
#define CUSTOM_EXCEPTION_CODE_PURE_CALL                0xF0000011
#define CUSTOM_EXCEPTION_CODE_NEW                    0xF0000012
#define CUSTOM_EXCEPTION_CODE_TERMINATE                0xF0000013
#define CUSTOM_EXCEPTION_CODE_UNEXPECTED            0xF0000014

class Locker {
public:
    Locker() {
        InitializeCriticalSection(&m_cs);
    }

    ~Locker() {
        DeleteCriticalSection(&m_cs);
    }

    void lock() {
        EnterCriticalSection(&m_cs);
    }

    void unlock() {
        LeaveCriticalSection(&m_cs);
    }

private:
    CRITICAL_SECTION m_cs;
};

class LockGuard {
public:
    explicit LockGuard(Locker* l)
            : m_lock(l) {
        m_lock->lock();
    }

    ~LockGuard() {
        m_lock->unlock();
    }

private:
    Locker* m_lock;
};

// static global variable
static Locker callstack_locker;
static char log_buffer[64 * 1024];
static char symbol_buffer_1[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
static char symbol_buffer_2[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
static void* dump_buffer = NULL;
#define DUMP_BUFFER_SIZE    (5 * 1024 * 1024)

static void log(const char* szFile, const char* szLog, size_t log_len) {
    HANDLE hFile = NULL;
    time_t tt;
    struct tm st;
    char szTime[32] = {0};
    int ret = 0;
    DWORD dwBytesWritten = 0;

    time(&tt);
    ret = localtime(&st, &tt);
    if (ret != 0) {
        return;
    }

    ret = sprintf(
            szTime,
            sizeof(szTime),
            "%04d-%02d-%02d %02d:%02d:%02d ",
            st.tm_year + 1900,
            st.tm_mon + 1,
            st.tm_mday,
            st.tm_hour,
            st.tm_min,
            st.tm_sec
    );

    if (ret == -1) {
        return;
    }

    hFile = CreateFileA(
            szFile,
            FILE_APPEND_DATA,
            0,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return;
    }

    WriteFile(hFile, szTime, ret, &dwBytesWritten, NULL);
    WriteFile(hFile, szLog, (DWORD) log_len, &dwBytesWritten, NULL);
    WriteFile(hFile, "\r\n", 2, &dwBytesWritten, NULL);
    CloseHandle(hFile);
}

static void logf(const char* szFileName, const char* fmt, ...) {
    int ret = 0;

    va_list arglist;
            va_start(arglist, fmt);
    ret = vsprintf(log_buffer, sizeof(log_buffer), fmt, arglist);
            va_end(arglist);
    if (ret < 0) {
        return;
    }

    log(szFileName, log_buffer, ret);
}

static void* get_current_context(CONTEXT* context) {
    ZeroMemory(context, sizeof(CONTEXT));

#ifdef _M_IX86
    CONTEXT aContext;
    ZeroMemory(&aContext, sizeof(CONTEXT));
    __asm {
        mov dword ptr[aContext.Eax], eax
        mov dword ptr[aContext.Ecx], ecx
        mov dword ptr[aContext.Edx], edx
        mov dword ptr[aContext.Ebx], ebx
        mov dword ptr[aContext.Esi], esi
        mov dword ptr[aContext.Edi], edi
        mov word ptr[aContext.SegSs], ss
        mov word ptr[aContext.SegCs], cs
        mov word ptr[aContext.SegDs], ds
        mov word ptr[aContext.SegEs], es
        mov word ptr[aContext.SegFs], fs
        mov word ptr[aContext.SegGs], gs
        pushfd
        pop[aContext.EFlags]
    }

    aContext.ContextFlags = CONTEXT_CONTROL;
    *context = aContext;
#pragma warning(push)
#pragma warning(disable:4311)
    context->Eip = (ULONG)_ReturnAddress();
    context->Esp = (ULONG)_AddressOfReturnAddress();
#pragma warning(pop)
    context->Ebp = *((ULONG *)_AddressOfReturnAddress() - 1);
#elif defined (_M_IA64) || defined (_M_X64)
    RtlCaptureContext(context);
#else
#error Architecture is not supported.
#endif

    return _ReturnAddress();
}

static void get_thread_context(HANDLE hThread, CONTEXT* context) {
    ZeroMemory(context, sizeof(CONTEXT));

    context->ContextFlags = (CONTEXT_FULL);
    SuspendThread(hThread);
    GetThreadContext(hThread, context);
    ResumeThread(hThread);
}

static void get_stackframe(STACKFRAME64* frame, CONTEXT* context) {
    ZeroMemory(frame, sizeof(STACKFRAME64));

#ifdef _M_IX86
    frame->AddrPC.Offset = context->Eip;
    frame->AddrPC.Mode = AddrModeFlat;
    frame->AddrFrame.Offset = context->Ebp;
    frame->AddrFrame.Mode = AddrModeFlat;
    frame->AddrStack.Offset = context->Esp;
    frame->AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    frame->AddrPC.Offset = context->Rip;
    frame->AddrPC.Mode = AddrModeFlat;
    frame->AddrFrame.Offset = context->Rbp;
    frame->AddrFrame.Mode = AddrModeFlat;
    frame->AddrStack.Offset = context->Rsp;
    frame->AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
    frame->AddrPC.Offset = context->StIIP;
    frame->AddrPC.Mode = AddrModeFlat;
    frame->AddrFrame.Offset = context->IntSp;
    frame->AddrFrame.Mode = AddrModeFlat;
    frame->AddrBStore.Offset = context->RsBSP;
    frame->AddrBStore.Mode = AddrModeFlat;
    frame->AddrStack.Offset = context->IntSp;
    frame->AddrStack.Mode = AddrModeFlat;
#else
#error Architecture is not supported.
#endif
}

static void log_call_stack(const char* szFileName, CONTEXT* pcontext = NULL) {
    CONTEXT context;
    STACKFRAME64 stack;
    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();

    if (NULL == pcontext) {
        get_current_context(&context);
    } else {
        context = *pcontext;
    }
    get_stackframe(&stack, &context);

    SymCleanup(hProcess);
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    SymInitialize(hProcess, NULL, TRUE);

    for (int frame = 0;; frame++) {
        DWORD image_type;
#ifdef _M_IX86
        image_type = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
        image_type = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
        image_type = IMAGE_FILE_MACHINE_IA64;
#else
#error Architecture is not supported.
#endif

        if (!StackWalk64(
                image_type,
                hProcess,
                hThread,
                &stack,
                &context,
                NULL,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                NULL
        )
                ) {
            break;
        }

        DWORD64 dw64Displacement = 0;
        DWORD dwDisplacement = 0;
        IMAGEHLP_LINE64 line;
        ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        DWORD64 dwAddress = stack.AddrPC.Offset;
        SYMBOL_INFO* symbol = (PSYMBOL_INFO) symbol_buffer_1;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        BOOL name_ok = SymFromAddr(hProcess, dwAddress, &dw64Displacement, symbol);
        BOOL addr_ok = SymGetLineFromAddr64(hProcess, dwAddress, &dwDisplacement, &line);

        if (name_ok && addr_ok) {
            logf(szFileName,
                 "Frame %d: %s %s line:%u",
                 frame, symbol->Name, line.FileName, line.LineNumber
            );
        } else if (name_ok) {
            logf(szFileName,
                 "Frame %d: %s",
                 frame, symbol->Name
            );
        } else if (addr_ok) {
            logf(szFileName,
                 "Frame %d: %s line:%u",
                 frame, line.FileName, line.LineNumber
            );
        }
    }
}

static void call_stack_to_string(
        HANDLE hThread,
        char* output,
        size_t size
) {
    CONTEXT context;
    STACKFRAME64 stack;
    HANDLE hProcess = GetCurrentProcess();
    if (NULL == hThread) {
        get_current_context(&context);
    } else {
        get_thread_context(hThread, &context);
    }
    get_stackframe(&stack, &context);

    SymCleanup(hProcess);
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    SymInitialize(hProcess, NULL, TRUE);

    size_t pos = 0;
    for (int frame = 0; pos < size; ++frame) {
        DWORD image_type;
#ifdef _M_IX86
        image_type = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
        image_type = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
        image_type = IMAGE_FILE_MACHINE_IA64;
#else
#error Architecture is not supported.
#endif

        if (!StackWalk64(
                image_type,
                hProcess,
                hThread,
                &stack,
                &context,
                NULL,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                NULL
        )
                ) {
            break;
        }

        DWORD64 dw64Displacement = 0;
        DWORD dwDisplacement = 0;
        IMAGEHLP_LINE64 line;
        ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        DWORD64 dwAddress = stack.AddrPC.Offset;
        SYMBOL_INFO* symbol = (PSYMBOL_INFO) symbol_buffer_2;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        BOOL name_ok = SymFromAddr(hProcess, dwAddress, &dw64Displacement, symbol);
        BOOL addr_ok = SymGetLineFromAddr64(hProcess, dwAddress, &dwDisplacement, &line);

        if (name_ok && addr_ok) {
            int ret = sprintf(output + pos, size - pos,
                                         "Frame %d: %s %s line:%u\r\n",
                                         frame, symbol->Name, line.FileName, line.LineNumber
            );
            if (ret < 0) {
                return;
            }
            pos += ret;
        } else if (name_ok) {
            int ret = sprintf(output + pos, size - pos,
                                         "Frame %d: %s\r\n",
                                         frame, symbol->Name
            );
            if (ret < 0) {
                return;
            }
            pos += ret;
        } else if (addr_ok) {
            int ret = sprintf(output + pos, size - pos,
                                         "Frame %d: %s line:%u\r\n",
                                         frame, line.FileName, line.LineNumber
            );
            if (ret < 0) {
                return;
            }
            pos += ret;
        }
    }
}

static void log_exception_callstack(CONTEXT* context = NULL) {
    char szFileName[256] = {0};
    int ret = 0;

    ret = sprintf(
            szFileName,
            sizeof(szFileName),
            "exception_handler-%u-%u.log",
            GetCurrentProcessId(),
            GetCurrentThreadId());
    if (ret == -1) {
        return;
    }

    log_call_stack(szFileName, context);
}

static void write_minidump(EXCEPTION_POINTERS* pExceptions) {
    free(dump_buffer);
    dump_buffer = NULL;

    HANDLE hFile = NULL;
    MINIDUMP_EXCEPTION_INFORMATION mei;
    MINIDUMP_CALLBACK_INFORMATION mci;
    HANDLE hProcess = GetCurrentProcess();
    DWORD dwProcessId = GetCurrentProcessId();
    DWORD dwThreadId = GetCurrentThreadId();
    char szFileName[256] = {0};
    int ret = 0;

    ret = sprintf(
            szFileName,
            sizeof(szFileName),
            "crashdump-%u-%u-%u.dmp",
            dwProcessId,
            dwThreadId,
            GetTickCount());
    if (ret == -1) {
        return;
    }

    hFile = CreateFileA(
            szFileName,
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return;
    }

    mei.ThreadId = dwThreadId;
    mei.ExceptionPointers = pExceptions;
    mei.ClientPointers = FALSE;
    mci.CallbackRoutine = NULL;
    mci.CallbackParam = NULL;

    MiniDumpWriteDump(
            hProcess,
            dwProcessId,
            hFile,
            static_cast<MINIDUMP_TYPE>(MiniDumpWithFullMemory | MiniDumpIgnoreInaccessibleMemory),
            &mei,
            NULL,
            &mci);

    CloseHandle(hFile);
}

/*
* dwExceptionCode: custom defined exception code
*				   Don't conflict with system code,
*				   such as STATUS_INVALID_CRUNTIME_PARAMETER etc in winnt.h
*/
static void write_minidump_ex(DWORD dwExceptionCode) {
    EXCEPTION_RECORD exception;
    CONTEXT context;
    EXCEPTION_POINTERS ExceptionPointers = {&exception, &context};

    void* ret_addr = get_current_context(&context);
    ZeroMemory(&exception, sizeof(EXCEPTION_RECORD));
    exception.ExceptionCode = dwExceptionCode;
    exception.ExceptionAddress = ret_addr;

    write_minidump(&ExceptionPointers);
}

static LONG WINAPI my_unhandle_exception_filter(
        struct _EXCEPTION_POINTERS* pExceptionInfo
) {
    log_exception_callstack(pExceptionInfo->ContextRecord);
    write_minidump(pExceptionInfo);
    TerminateProcess(GetCurrentProcess(), 1);

    return EXCEPTION_EXECUTE_HANDLER;
}

static void my_invalid_param_handler(
        const wchar_t*,
        const wchar_t*,
        const wchar_t*,
        unsigned int,
        uintptr_t
) {
    // do nothing
    return;
}

static void my_purecall_handler() {
    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_PURE_CALL);
    TerminateProcess(GetCurrentProcess(), 1);
}

static int my_new_handler(size_t want_alloc) {
    // TODO: log more info, want_alloc eg.

    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_NEW);
    TerminateProcess(GetCurrentProcess(), 1);
    return 0;
}

static void my_signal_abrt_handle(int signal) {
    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_SIGNAL_ABORT);
    TerminateProcess(GetCurrentProcess(), 1);
}

static void my_signal_fpe_handle(int signal, int error_code) {
    // TODO: error_code check <float.h>, FPE_INVALID ...

    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_SIGNAL_FPE);
    TerminateProcess(GetCurrentProcess(), 1);
}

static void my_terminate_handler() {
    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_TERMINATE);
    TerminateProcess(GetCurrentProcess(), 1);
}

static void my_unexpected_handler() {
    log_exception_callstack();
    write_minidump_ex(CUSTOM_EXCEPTION_CODE_UNEXPECTED);
    TerminateProcess(GetCurrentProcess(), 1);
}

namespace rdm {
void ExceptionHandle::InitProcessExceptionHandler() {
    SetUnhandledExceptionFilter(my_unhandle_exception_filter);
    _set_invalid_parameter_handler(my_invalid_param_handler);
    _set_purecall_handler(my_purecall_handler);
    _set_new_handler(my_new_handler);

#ifndef _DEBUG
    SetErrorMode(
            SEM_FAILCRITICALERRORS |
            SEM_NOALIGNMENTFAULTEXCEPT |
            SEM_NOGPFAULTERRORBOX |
            SEM_NOOPENFILEERRORBOX
            );
#endif
    dump_buffer = malloc(DUMP_BUFFER_SIZE);

    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    // https://msdn.microsoft.com/en-us/library/xdkz3x12(v=vs.100)
    signal(SIGABRT, my_signal_abrt_handle);
    typedef void(* signal_handler)(int);
    signal(SIGFPE, (signal_handler) my_signal_fpe_handle);
}

void ExceptionHandle::InitThreadExceptionHandler() {
    set_terminate(my_terminate_handler);
    set_unexpected(my_unexpected_handler);
}

void ExceptionHandle::GetCallStackString(void* thread, char* buffer, size_t size) {
    if (NULL == buffer || 0 == size) {
        return;
    }

    LockGuard guard(&callstack_locker);
    call_stack_to_string((HANDLE) thread, buffer, size);
}
}
#else
namespace rdm {
void ExceptionHandle::InitProcessExceptionHandler(){}
void ExceptionHandle::InitThreadExceptionHandler(){}
void ExceptionHandle::GetCallStackString(){}
}
#endif