#!/bin/bash
set -e
 
 g++ -I.. -I ../.. test.cpp ../client.cpp -o test -lgtest
 ./test
