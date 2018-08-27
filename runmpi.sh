#!/bin/bash
mpicc -g -std=c99 -Wall -o mpitimer.out mpitimer.c -lm 
mpiexec -n 4 ./mpitimer.out
