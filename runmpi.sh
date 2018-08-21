#!/bin/bash
mpicc -g -Wall -o mpicreatestruct.out mpicreatestruct.c -lm
mpiexec -n 3 ./mpicreatestruct.out
