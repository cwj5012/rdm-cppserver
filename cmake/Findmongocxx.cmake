if (WIN32)
	FIND_PATH(LIBMONGOCXX_INCLUDE_DIR
        NAME mongocxx
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(LIBMONGOCXX_INCLUDE_DIR
            NAME cppconn
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(LIBMONGOCXX_LIBRARY
        NAMES mongocxx.lib
        PATHS ${CMAKE_LIBRARY_PATH})
	FIND_LIBRARY(LIBBSONCXX_LIBRARY
        NAMES bsoncxx.lib
        PATHS ${CMAKE_LIBRARY_PATH})

    set(LIBMONGOCXX_LIBRARY
            ${LIBMONGOCXX_LIBRARY}
            ${LIBBSONCXX_LIBRARY})
else()
	FIND_LIBRARY(LIBMONGOCXX_LIBRARY
            NAMES mongocxx.so
            PATHS /usr/local/lib)
endif()

if (LIBMONGOCXX_INCLUDE_DIR)
    MESSAGE(STATUS "mongocxx include dir: " ${LIBMONGOCXX_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "mongocxx include dir not found")
endif ()

if (LIBMONGOCXX_LIBRARY)
    MESSAGE(STATUS "mongocxx library: " ${LIBMONGOCXX_LIBRARY})
else ()
    MESSAGE(WARNING "mongocxx library not found")
endif ()
