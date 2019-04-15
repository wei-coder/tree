#!/bin/bash

rm -rf core.*
rm -rf bin_tree
gcc -g binary_tree.c -o bin_tree
./bin_tree

