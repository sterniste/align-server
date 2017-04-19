cmake_minimum_required(VERSION 3.0)

project(test-jwt_verify CXX)

file(GLOB CC_FILES *.cc)

find_package(Threads REQUIRED)

include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include" ${BOOST_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${universals_INCLUDE_DIRS})

add_library(ssl STATIC IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libssl.a)
add_library(crypto STATIC IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libcrypto.a)

include_directories(${universals_INCLUDE_DIRS} ${jwt_verify_INCLUDE_DIRS})

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
if (WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
else()
  set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
endif()
add_executable(test-json_web_token ${CC_FILES})

if (WIN32)
  target_link_libraries(test-json_web_token jwt_verify universals ssl crypto "${gmock_BINARY_DIR}/libgmock.a" "${gtest_BINARY_DIR}/libgtest.a" ${CMAKE_THREAD_LIBS_INIT} crypt32.lib ws2_32.lib wsock32.lib)
else()
  target_link_libraries(test-json_web_token jwt_verify universals ssl crypto "${gmock_BINARY_DIR}/libgmock.a" "${gtest_BINARY_DIR}/libgtest.a" ${CMAKE_THREAD_LIBS_INIT} -ldl)
endif()

add_test(NAME test-json_web_token COMMAND test-json_web_token)
