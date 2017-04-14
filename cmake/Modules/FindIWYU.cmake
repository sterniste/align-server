option(BUILD_IWYU "Run the include-what-you-use static analyzer on the source code of the project." OFF)

if (BUILD_IWYU)
  find_program(iwyu NAMES include-what-you-use iwyu)
  if (NOT iwyu)
    message(FATAL_ERROR "Could not find the program include-what-you-use")
  endif ()
endif ()
