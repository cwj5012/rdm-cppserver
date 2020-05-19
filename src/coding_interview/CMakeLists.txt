file(
        GLOB CPP_FILES
        "*.h"
        "*.cpp"
        "*/*.h"
        "*/*.cpp"
        "*/*/*.h"
        "*/*/*.cpp"
        "*/*/*/*.h"
        "*/*/*/*.cpp"
)

add_executable(
        coding_interview
        ${CPP_FILES}
)
