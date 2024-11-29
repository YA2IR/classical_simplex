## Overview
This is an implementation of the classical [Simplex algorithm](https://en.wikipedia.org/wiki/Simplex_algorithm) in C, with several examples taken from _Operations Research: Applications and Algorithms by Wayne L. Winston_.

## Usage
You can uncomment any of the examples provided in the main function of `simplex.c` (they're quite different, one of them is cycling, one of them is unbounded... etc), then compile and run:
```
gcc examples.c simplex.c -o simplex && ./simplex
```

## Misc Notes
- This program operates on the simplex tableau in canonical form. The examples are provided in this format.
- It supports less-than-or-equal constraints, but adapting it to handle greater-than-or-equal constraints should be straightforward.
