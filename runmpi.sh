#!/bin/bash
mpicc -g -Wall -o mpiscattergather.out mpiscattergather.c -lm
mpiexec -n 4 ./mpiscattergather.out
