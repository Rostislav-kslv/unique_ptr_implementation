project(tests)


set(test1_source test1.cpp)


add_executable(test1 ${test1_source})


target_include_directories(test1 PUBLIC ${CMAKE_SOURCE_DIR}/u_ptr)

target_link_libraries(test1 gtest gmock pthread)


add_test(NAME Test1 COMMAND test1)

