add_library(
        submodule
        SubClass.cpp
        SubClass.h
)

add_library(rdm::submodule ALIAS submodule)