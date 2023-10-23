#!/bin/bash

g++ $1 $2 -I/opt/homebrew/Cellar/sfml/2.6.0/include -o out -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system -std=c++20 -fsanitize=address,undefined -fno-sanitize-recover=all -O2 -Wall -Werror -Wsign-compare && ./out
