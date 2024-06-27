set -x
set -e
git fetch --all --force --prune
git reset --hard mk/fuzz3
bash fuzz_build.sh
bash fuzz_minimize_all.sh
bash fuzz_run.sh
