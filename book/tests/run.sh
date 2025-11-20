#!/bin/bash
set -e
 
 g++ -I.. test.cpp ../book.cpp -o test -lgtest
 ./test
