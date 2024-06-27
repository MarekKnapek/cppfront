set -x
set -e
./fuzz_cppfront -timeout=86400 corpus
