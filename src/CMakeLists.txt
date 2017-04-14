cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(src)

find_package(IWYU)

# once for all subprojects
add_compile_options(-std=c++14 -g -Wall -DLEVEL_LOGGING -DBOOST_LOG_DYN_LINK)

add_subdirectory(universals) # a static library (depends on INCLUDES: Boost)
add_subdirectory(asio_https) # a static library (depends on INCLUDES: Boost, universals)
add_subdirectory(jwt_verify) # a static library (depends on INCLUDES: Boost, openssl, universals, json)
add_subdirectory(task_list_app) # a static library (depends on INCLUDES: Boost, universals, asio_https, jwt_verify)

add_subdirectory(main) # ia_core_ape executable (depends on INCLUDES: Boost, universals, asio_https, task_list_app; LIBS: Boost, openssl, json, universals, asio_https, jwt_verify, task_list_app)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../doc/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif ()
