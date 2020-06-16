if (WIN32)
	FIND_PATH(YAMLCPP_INCLUDE_DIR
        NAME yaml-cpp/yaml.h
        PATHS ${CMAKE_INCLUDE_PATH})
else()
	FIND_PATH(YAMLCPP_INCLUDE_DIR
            NAME yaml-cpp/yaml.h
            PATHS /usr/local/include/)
endif()

if (WIN32)
	FIND_LIBRARY(YAMLCPP_LIBRARY
        NAMES yaml-cpp.lib
        PATHS ${CMAKE_LIBRARY_PATH})
else()
	FIND_LIBRARY(YAMLCPP_LIBRARY
            NAMES YAMLCPP.so
            PATHS /usr/local/lib)
endif()

if (YAMLCPP_INCLUDE_DIR)
    MESSAGE(STATUS "yaml-cpp include dir: " ${YAMLCPP_INCLUDE_DIR})
else ()
    MESSAGE(WARNING "yaml-cpp include dir not found")
endif ()

if (YAMLCPP_LIBRARY)
    MESSAGE(STATUS "yaml-cpp library: " ${YAMLCPP_LIBRARY})
else ()
    MESSAGE(WARNING "yaml-cpp library not found")
endif ()
