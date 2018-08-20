#!/bin/bash
set -e

cd /src
gcc -o test test.c

./test&
TEST_PID=$!

sleep 1
pstree -apA

echo "-------- parent ----------" && pmap $TEST_PID | grep anon

(while true; do
  ps -eo min_flt,maj_flt,cmd
done )&
MON_PID=$!

# ./nginx-memuse $TEST_PID
wait $TEST_PID
kill -9 $MON_PID