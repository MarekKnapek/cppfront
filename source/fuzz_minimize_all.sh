set -x
set -e
rm -rf ./corpus_new
mkdir corpus_new
cp -r ../../cppfront1/source/corpus corpus1
cp -r ../../cppfront2/source/corpus corpus2
cp -r ../../cppfront3/source/corpus corpus3
./fuzz_cppfront -merge=1 corpus_new corpus1 corpus2 corpus3
rm -rf ./corpus1
rm -rf ./corpus2
rm -rf ./corpus3
rm -rf ./corpus
mv corpus_new corpus
