#!/bin/bash
set -e
 
 g++ -I.. test.cpp ../client.cpp -o test -lgtest
 ./test
