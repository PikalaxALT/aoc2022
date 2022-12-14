#!/usr/bin/make

CXXFLAGS := -O3 -g -std=c++20

.PHONY: all clean test

all: aoc2022
test: aoc2022-test

clean:
	$(RM) aoc2022 aoc2022-test

aoc2022: main.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

aoc2022-test: test.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ test.cpp
