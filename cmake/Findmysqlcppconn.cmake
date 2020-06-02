if (WIN32)
	FIND_PATH(MYSQLCPPCONN_INCLUDE_DIR
        NAME cppconn
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(MYSQLCPPCONN_INCLUDE_DIR
            NAME cppconn
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(MYSQLCPPCONN_LIBRARYS
        NAMES mysqlcppconn.lib
        PATHS ${CMAKE_LIBRARY_PATH})
else()
	FIND_LIBRARY(MYSQLCPPCONN_LIBRARYS
            NAMES libmysqlcppconn.so
            PATHS /usr/local/lib)
endif()

if (MYSQLCPPCONN_INCLUDE_DIR)
    MESSAGE(STATUS "mysqlcppconn include dir: " ${MYSQLCPPCONN_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "mysqlcppconn include dir not found")
endif ()

if (MYSQLCPPCONN_LIBRARYS)
    MESSAGE(STATUS "mysqlcppconn library: " ${MYSQLCPPCONN_LIBRARYS})
else ()
    MESSAGE(WARNING "mysqlcppconn library not found")
endif ()

# copy dll
if (EXISTS ${USER_LOCAL_PATH}/lib/${CMAKE_BUILD_TYPE}/mysqlcppconn.dll)
    configure_file(${USER_LOCAL_PATH}/lib/${CMAKE_BUILD_TYPE}/mysqlcppconn.dll
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)
endif ()
