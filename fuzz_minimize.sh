set -x
set -e
rm -rf ./corpus_new
mkdir corpus_new
./fuzz_cppfront -merge=1 corpus_new corpus
rm -rf ./corpus
mv corpus_new corpus
