#!/usr/bin/env bash

year=2022
day=$1

make -s
./aoc2022 $1 $2 <(curl -s -H "Cookie: session=$(cat session)" -H "UserAgent: PikalaxALT curl test https://github.com/PikalaxALT/aoc2022" https://adventofcode.com/$year/day/$day/input)
