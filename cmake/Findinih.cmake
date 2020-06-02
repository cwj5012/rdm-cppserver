if (WIN32)
	FIND_PATH(INIH_INCLUDE_DIR
        NAME INIReader.h
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(INIH_INCLUDE_DIR
            NAME INIReader.h
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(INIH_LIBRARYS
        NAMES inih.lib
        PATHS ${CMAKE_LIBRARY_PATH})
else()
	FIND_LIBRARY(INIH_LIBRARYS
            NAMES INIH.so
            PATHS /usr/local/lib)
endif()

if (INIH_INCLUDE_DIR)
    MESSAGE(STATUS "inih include dir: " ${INIH_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "inih include dir not found")
endif ()

if (INIH_LIBRARYS)
    MESSAGE(STATUS "inih library: " ${INIH_LIBRARYS})
else ()
    MESSAGE(WARNING "inih library not found")
endif ()
