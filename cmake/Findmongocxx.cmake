if (WIN32)
	FIND_PATH(MONGOCXX_INCLUDE_DIR
        NAME mongocxx
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(MONGOCXX_INCLUDE_DIR
            NAME cppconn
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(MONGOCXX_LIBRARY
        NAMES mongocxx.lib
        PATHS ${CMAKE_LIBRARY_PATH})
	FIND_LIBRARY(LIBBSONCXX_LIBRARY
        NAMES bsoncxx.lib
        PATHS ${CMAKE_LIBRARY_PATH})

    set(MONGOCXX_LIBRARY
            ${MONGOCXX_LIBRARY}
            ${LIBBSONCXX_LIBRARY})
else()
	FIND_LIBRARY(MONGOCXX_LIBRARY
            NAMES mongocxx.so
            PATHS /usr/local/lib)
endif()

if (MONGOCXX_INCLUDE_DIR)
    MESSAGE(STATUS "mongocxx include dir: " ${MONGOCXX_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "mongocxx include dir not found")
endif ()

if (MONGOCXX_LIBRARY)
    MESSAGE(STATUS "mongocxx library: " ${MONGOCXX_LIBRARY})
else ()
    MESSAGE(WARNING "mongocxx library not found")
endif ()
