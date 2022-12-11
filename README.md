# AOC2022

These are my solutions to the 2022 season of [Advent of Code](https://adventofcode.com/2022). They are implemented in C++.

Header file `Solution.h` defines the abstract base class for each day's solution. Header file `DayX.h` defines the class implementing the solution for day X. Each puzzle has two parts, each with a separate class. Depending on the demands for that day, the `DayX` class is either implemented as a template with the `DayXPartY` classes as specializations, or as its own class with specified abstract methods defined in the subclass for its part.

All solutions are included in `main.cpp`, and the specific solution to run is chosen by the two positional arguments. Usage:

```bash
./main <DAY> <PART> <INPUT.txt>
```

Input datasets are not included as they are unique for each user.
