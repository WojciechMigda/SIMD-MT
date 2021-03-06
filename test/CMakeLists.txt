# https://github.com/pabloariasal/modern-cmake-sample/blob/master/libjsonutils/test/CMakeLists.txt

include(GoogleTest)

# Download and unpack googletest at configure time
configure_file(${CMAKE_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(simd-mt-test src/main.cpp)
target_compile_features(simd-mt-test PRIVATE cxx_auto_type)
target_compile_features(simd-mt-test PRIVATE cxx_alignas)
target_compile_features(simd-mt-test PRIVATE cxx_constexpr)

target_include_directories(simd-mt-test
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(simd-mt-test gtest_main)
target_compile_options(simd-mt-test PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -march=native>)

gtest_discover_tests(simd-mt-test)
add_test(NAME monolithic COMMAND simd-mt-test)
