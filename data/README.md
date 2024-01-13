# Sudoku data file formats

There's primarily two variants of file formats. In each of them, blanks are represented by periods
(`.`) or zeros (`0`).

## Grid based

These are intended to be human readable / editable

```
0 0 3 | 0 2 0 | 6 0 0
9 0 0 | 3 0 5 | 0 0 1
0 0 1 | 8 0 6 | 4 0 0
------+-------+------
0 0 8 | 1 0 2 | 9 0 0
7 0 0 | 0 0 0 | 0 0 8
0 0 6 | 7 0 8 | 2 0 0
------+-------+------
0 0 2 | 6 0 9 | 5 0 0
8 0 0 | 2 0 3 | 0 0 9
0 0 5 | 0 1 0 | 3 0 0
```

As an implementation detail, all whitespace and non-digit characters are ignored, so the puzzle
above is also equivalent to

```
003020600
900305001
001806400
008102900
700000008
006708200
002609500
800203009
005010300
```

## Line based

This is the easiest for a machine to parse. All 81 digits are on a single line, with blanks
represented by `.` or `0`.

In this format, the puzzle above looks like
```
..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..
```
