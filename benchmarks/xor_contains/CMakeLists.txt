add_executable(xor_contains xor_contains.cpp)

target_compile_options(xor_contains PRIVATE -march=native)
target_compile_features(xor_contains PRIVATE cxx_std_20)
target_link_libraries(xor_contains benchmark::benchmark)
