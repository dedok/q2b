#!/bin/sh

make clean > /dev/null
qmake -Wall ../../src/examples/*.pro && make -j

