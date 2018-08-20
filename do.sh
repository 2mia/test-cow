#!/bin/bash
set -e

cd /src
gcc -o test test.c

./test&
TEST_PID=$!

pstree -apA

echo "-------- parent ----------" && pmap $TEST_PID | grep anon

(while true; do
  kill -0 $TEST_PID &> /dev/null || break
  ps -eo min_flt,maj_flt,%cpu,rss,vsz,cmd
done )&
MON_PID=$! 

# ./nginx-memuse $TEST_PID
wait $TEST_PID
kill -9 $MON_PID