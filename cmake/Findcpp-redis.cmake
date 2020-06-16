if (WIN32)
	FIND_PATH(CPPREDIS_INCLUDE_DIR
        NAME cpp_redis/cpp_redis
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(CPPREDIS_INCLUDE_DIR
            NAME cpp-redis/yaml.h
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(CPPREDIS_LIBRARY
        NAMES cpp_redis.lib
        PATHS ${CMAKE_LIBRARY_PATH})
	FIND_LIBRARY(TACOPIE_LIBRARY
        NAMES tacopie.lib
        PATHS ${CMAKE_LIBRARY_PATH})
    set(CPPREDIS_LIBRARY
            ${CPPREDIS_LIBRARY}
            ${TACOPIE_LIBRARY})
else()
	FIND_LIBRARY(CPPREDIS_LIBRARY
            NAMES CPPREDIS.so
            PATHS /usr/local/lib)
endif()

if (CPPREDIS_INCLUDE_DIR)
    MESSAGE(STATUS "cpp-redis include dir: " ${CPPREDIS_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "cpp-redis include dir not found")
endif ()

if (CPPREDIS_LIBRARY)
    MESSAGE(STATUS "cpp-redis library: " ${CPPREDIS_LIBRARY})
else ()
    MESSAGE(WARNING "cpp-redis library not found")
endif ()
