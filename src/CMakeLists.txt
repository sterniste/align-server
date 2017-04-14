cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(src)

add_custom_target(clang-format-src DEPENDS clang-format-universals clang-format-jwt_verify clang-format-align_server_app clang-format-main)
add_custom_target(clang-tidy-src DEPENDS clang-tidy-universals clang-tidy-jwt_verify clang-tidy-align_server_app clang-tidy-main)

find_package(IWYU)

# once for all subprojects
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-DLEVEL_LOGGING -DBOOST_LOG_DYN_LINK -D__USE_W32_SOCKETS)

add_subdirectory(universals) # a static library (depends on INCLUDES: Boost)
add_subdirectory(jwt_verify) # a static library (depends on INCLUDES: Boost, openssl, universals)
add_subdirectory(align_server_app) # a static library (depends on INCLUDES: Boost, cpp-netlib, jwt_verify, universals)

add_subdirectory(main) # ia_core_ape executable (depends on INCLUDES: Boost, universals, align_server_app; LIBS: cpp-netlib, openssl, ICU4C, Boost, universals, jwt_verify, align_server_app)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_SOURCE_DIR}/doc/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()
