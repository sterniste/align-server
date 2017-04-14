cmake_minimum_required(VERSION 3.0)

project(test-jwt_verify CXX)

file(GLOB CC_FILES *.cc)

include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")

include_directories(${BOOST_INCLUDE_DIR} ${openssl_INCLUDE_DIRS} ${json_INCLUDE_DIRS} ${universals_INCLUDE_DIRS})

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libssl.so)
add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libcrypto.so)

include_directories(${universals_INCLUDE_DIRS})

include_directories(${jwt_verify_INCLUDE_DIRS})

add_executable(test-json_web_token ${CC_FILES})

target_link_libraries(test-json_web_token jwt_verify universals ssl crypto "${gmock_BINARY_DIR}/libgmock.a" "${gtest_BINARY_DIR}/libgtest.a" -lpthread)

add_test(NAME test-json_web_token COMMAND test-json_web_token)
