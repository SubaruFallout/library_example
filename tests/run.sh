#!/bin/bash
set -e
 
 g++ -I.. test.cpp ../library.cpp ../client/client.cpp ../book/book.cpp -o test -lgtest
 ./test
