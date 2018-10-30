# Download and unpack googlebenchmark at configure time
configure_file(${CMAKE_SOURCE_DIR}/cmake/GoogleBenchmark-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googlebenchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googlebenchmark-download )
if(result)
  message(FATAL_ERROR "CMake step for googlebenchnmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googlebenchmark-download )
if(result)
  message(FATAL_ERROR "Build step for googlebenchmark failed: ${result}")
endif()

# Add googlebenchmark directly to our build.
add_subdirectory(${CMAKE_BINARY_DIR}/googlebenchmark-src
                 ${CMAKE_BINARY_DIR}/googlebenchmark-build
                 EXCLUDE_FROM_ALL)


add_executable(simd-mt-bench src/bench.cpp)
target_compile_features(simd-mt-bench PRIVATE cxx_auto_type)
target_compile_features(simd-mt-bench PRIVATE cxx_alignas)
target_compile_features(simd-mt-bench PRIVATE cxx_constexpr)

target_include_directories(simd-mt-bench
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test/src>
)

target_link_libraries(simd-mt-bench benchmark_main)
target_compile_options(simd-mt-bench PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -march=native>)
add_custom_target(
    run_benchmark
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/simd-mt-bench
    COMMENT "Running google benchmarks"
)
