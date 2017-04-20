#!/bin/bash

make -f clean
make -f Makefile.compare build

make clean
make build

rm -rf results
mkdir results

if [ ! -f words ]; then
  echo "-10p : Executabil lipsa!"
  exit 0
fi

./words tests/test1a results/out1a > /dev/null
./compare 1 tests/test1a tests/out1a results/out1a 1.0

./words tests/test1b results/out1b > /dev/null
./compare 2 tests/test1b tests/out1b results/out1b 2.0

./words tests/test1c results/out1c > /dev/null
./compare 3 tests/test1c tests/out1c results/out1c 0.5

./words tests/test2a results/out2a > /dev/null
./compare 4 tests/test2a tests/out2a results/out2a 1.0

./words tests/test2b results/out2b > /dev/null
./compare 5 tests/test2b tests/out2b results/out2b 2.0

./words tests/test2c results/out2c > /dev/null
./compare 6 tests/test2c tests/out2c results/out2c 0.5

./words tests/test3a results/out3a > /dev/null
./compare 7 tests/test1a tests/out3a results/out3a 1.0

./words tests/test3b results/out3b > /dev/null
./compare 8 tests/test3b tests/out3b results/out3b 2.0

./words tests/test3c results/out3c > /dev/null
./compare 9 tests/test3c tests/out3c results/out3c 1.0

