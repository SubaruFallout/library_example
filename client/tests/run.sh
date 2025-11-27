#!/bin/bash
set -e
 
 g++ -I.. -I ../.. test.cpp ../client.cpp ../../book/book.cpp -o test -lgtest
 ./test
