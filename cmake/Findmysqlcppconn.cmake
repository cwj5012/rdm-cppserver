if (WIN32)
	FIND_PATH(LIBMYSQLCPPCONN_INCLUDE_DIR
        NAME cppconn
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(LIBMYSQLCPPCONN_INCLUDE_DIR
            NAME cppconn
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(LIBMYSQLCPPCONN_LIBRARY
        NAMES mysqlcppconn.lib
        PATHS ${CMAKE_LIBRARY_PATH})
else()
	FIND_LIBRARY(LIBMYSQLCPPCONN_LIBRARY
            NAMES libmysqlcppconn.so
            PATHS /usr/local/lib)
endif()

if (LIBMYSQLCPPCONN_INCLUDE_DIR)
    MESSAGE(STATUS "mysqlcppconn include dir: " ${LIBMYSQLCPPCONN_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "mysqlcppconn include dir not found")
endif ()

if (LIBMYSQLCPPCONN_LIBRARY)
    MESSAGE(STATUS "mysqlcppconn library: " ${LIBMYSQLCPPCONN_LIBRARY})
else ()
    MESSAGE(WARNING "mysqlcppconn library not found")
endif ()
