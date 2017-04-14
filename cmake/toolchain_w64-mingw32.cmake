# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)
set(MSYS 1)

set(TOOLSET_PREFIX "x86_64-w64-mingw32")

# which compilers to use for C and C++
set(CMAKE_C_COMPILER /usr/bin/${TOOLSET_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/${TOOLSET_PREFIX}-g++)
set(CMAKE_RC_COMPILER /usr/bin/${TOOLSET_PREFIX}-windres)

# target environment location
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLSET_PREFIX} ${CMAKE_SOURCE_DIR}/ext/prefix_w64-mingw32)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)