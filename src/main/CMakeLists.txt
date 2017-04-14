cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(main CXX)

file(GLOB CC_FILES *.cc)

find_package(Threads REQUIRED)

include_directories(${BOOST_INCLUDE_DIR})
add_library(boost_date_time SHARED IMPORTED)
set_target_properties(boost_date_time PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_date_time-mt.so)
add_library(boost_random SHARED IMPORTED)
set_target_properties(boost_random PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_random-mt.so)
add_library(boost_regex SHARED IMPORTED)
set_target_properties(boost_regex PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_regex-mt.so)
add_library(boost_chrono SHARED IMPORTED)
set_target_properties(boost_chrono PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_chrono-mt.so)
add_library(boost_atomic SHARED IMPORTED)
set_target_properties(boost_atomic PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_atomic-mt.so)
add_library(boost_log SHARED IMPORTED)
set_target_properties(boost_log PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_log-mt.so)
add_library(boost_log_setup SHARED IMPORTED)
set_target_properties(boost_log_setup PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_log_setup-mt.so)
add_library(boost_program_options SHARED IMPORTED)
set_target_properties(boost_program_options PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_program_options-mt.so)
add_library(boost_filesystem SHARED IMPORTED)
set_target_properties(boost_filesystem PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_filesystem-mt.so)
add_library(boost_system SHARED IMPORTED)
set_target_properties(boost_system PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_system-mt.so)
add_library(boost_thread SHARED IMPORTED)
set_target_properties(boost_thread PROPERTIES IMPORTED_LOCATION ${BOOST_LIB_DIR}/libboost_thread-mt.so)

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libssl.so)
add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES IMPORTED_LOCATION ${OPENSSL_LIB_DIR}/libcrypto.so)

include_directories(${universals_INCLUDE_DIRS})

include_directories(${asio_https_INCLUDE_DIRS})

include_directories(${jwt_verify_INCLUDE_DIRS})

add_executable(task_list ${CC_FILES})

if (BUILD_IWYU)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu})
endif()  

target_link_libraries(task_list task_list_app asio_https universals ssl crypto boost_date_time boost_random boost_regex boost_chrono boost_atomic boost_log boost_log_setup boost_program_options boost_filesystem boost_system boost_thread ${CMAKE_THREAD_LIBS_INIT} -lstdc++fs -ldl)
