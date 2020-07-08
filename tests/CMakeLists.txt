find_package(doctest REQUIRED)

function(build_test TEST_NAME)
  add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_NAME}.cpp)
  target_compile_definitions(${TEST_NAME} PRIVATE R3D_DEBUG)
  target_link_libraries(${TEST_NAME} PRIVATE project::options project::warnings renderer::renderer_shared
                                             doctest::doctest)
  add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

build_test(basic_test)
build_test(basic_renderer_test)
build_test(window_test)
build_test(vec_test)
