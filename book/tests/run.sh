#!/bin/bash
set -e
 
 g++ -I.. -I../.. test.cpp ../book.cpp -o test -lgtest
 ./test
