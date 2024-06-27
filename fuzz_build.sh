set -x
set -e
clang++ -std=c++20 -O0 -g -fsanitize=address,fuzzer source/cppfront.cpp -o fuzz_cppfront
