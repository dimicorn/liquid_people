#!/bin/bash

g++ $1 -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/gsl/2.7.1/include -o out -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++20 -lgsl
