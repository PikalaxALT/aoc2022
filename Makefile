#!/usr/bin/make

CXXFLAGS := -O3 -g -std=c++17
CXXSRCS := main.cpp

.PHONY: all clean

all: aoc2022

aoc2022: $(CXXSRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(CXXSRCS)
