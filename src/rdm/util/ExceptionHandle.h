#pragma once

namespace rdm {

class ExceptionHandle {
public:
    /********************************************************************
    * method: InitProcessExceptionHandler
    * return: void
    * NOTE: set exception handler on per-process
    *********************************************************************/
    static void InitProcessExceptionHandler();

    /********************************************************************
    * method: InitThreadExceptionHandler
    * return: void
    * NOTE: set exception handler on per-thread
    *********************************************************************/
    static void InitThreadExceptionHandler();

    /********************************************************************
    * method: GetCallStackString
    * param:
    *		thread: thread handle
    *		buffer: callstack string buffer
    *		size:	buffer size
    *********************************************************************/
    static void GetCallStackString(void* thread, char* buffer, size_t size);
};

}


