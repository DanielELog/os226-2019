#!/bin/bash

. ../test/lib.sh

make

testouts test ./main || exit 1
testouts test ./main.sh || exit 1
