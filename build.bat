#!/bin/bash
g++ -c Source.cpp
g++ Source.o -o DDLoader -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

