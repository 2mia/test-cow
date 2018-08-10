#!/bin/bash
set -e

cd /src
gcc -o test test.c

./test&
TEST_PID=$!
sleep 7                         # wait for pages to go away ( flush ? )
pmap -p $TEST_PID
#pmap -p 13
#pmap -p 15
./nginx-memuse $TEST_PID
wait $TEST_PID

