#!/bin/bash

rm -rf core.*
rm -rf main
gcc -g main.c -o main
./main

