cmake_minimum_required(VERSION 3.0)

# Download and unpack googletest at configure time
configure_file(${CMAKE_SOURCE_DIR}/cmake/CMakeLists-gtest.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
 
# Prevent GoogleTest from overriding our compiler/linker options when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
# Add googletest directly to our build. This adds the following targets: gtest, gtest_main, gmock and gmock_main
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src ${CMAKE_CURRENT_BINARY_DIR}/googletest-build)

# Now simply link your own targets against gtest, gmock, etc. as appropriate

# once for all subprojects
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall)

add_subdirectory(jwt_verify)
