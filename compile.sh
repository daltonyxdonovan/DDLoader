#!/bin/bash

g++ -c Source.cpp

g++ Source.o -o LOAD-R -lsfml-graphics -lsfml-window -lsfml-system

./LOAD-R


