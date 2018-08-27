#!/bin/bash
mpicc -g -Wall -o mpitrape.out mpitrape.c -lm
mpiexec -n 4 ./mpitrape.out
