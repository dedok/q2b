#!/bin/sh

[ -e ./bin ] && rm ./bin/* > /dev/null
make clean > /dev/null
qmake && make -j4

