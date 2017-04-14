# Additional target to perform clang-format/clang-tidy run
# Requires clang-format and clang-tidy

file(GLOB PROJECT_SRC_FILES *.cc *.h)

add_custom_target(
        clang-format-${PROJECT_NAME}
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${PROJECT_SRC_FILES}
)

add_custom_target(
        clang-tidy-${PROJECT_NAME}
        COMMAND /usr/bin/clang-tidy
        ${PROJECT_SRC_FILES}
        -config=''
        --
        -std=c++14
        ${INCLUDE_DIRECTORIES}
)