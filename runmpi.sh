#!/bin/bash
mpicc -g -Wall -o mpitimer.out mpitimer.c -lm 
mpiexec -n 4 ./mpitimer.out
