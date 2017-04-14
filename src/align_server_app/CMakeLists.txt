cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(task_list_app CXX)

file(GLOB CC_FILES *.cc)

include_directories(${BOOST_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${asio_https_INCLUDE_DIRS} ${jwt_verify_INCLUDE_DIRS} ${universals_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${CC_FILES})

if (BUILD_IWYU)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu})
endif()  

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE OFF)

# Specify here the include directories exported by this library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME})

# Expose definitions to other subprojects through cache variable.
set(${PROJECT_NAME}_DEFINITIONS ${universals_DEFINITIONS} ${jwt_verify_DEFINITIONS} ${asio_https_DEFINITIONS} CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
# Expose public includes (e.g. Boost, asio_https, jwt_verify, universals; transitively) to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} ${BOOST_INCLUDE_DIR} ${universals_INCLUDE_DIRS} ${asio_https_INCLUDE_DIRS} ${jwt_verify_INCLUDE_DIRS} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
