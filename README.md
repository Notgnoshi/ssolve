# ssolve

A `-std=c11` sudoku solver to learn autotools

## How to build

```sh
autoreconf --install
mkdir build/
cd build/
../configure
make
```

To run the test suite, run

```sh
make check
```

Use `git clean -f -X -d` to clean up after in-tree builds.

## How to run

The `ssolve` program takes a plaintext Sudoku file as an input. The file is a grid of single-digit
numbers. All non-digit numbers are ignored.

```sh
$ cat ./tests/cases/empty.txt
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
------+-------+------
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
------+-------+------
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
0 0 0 | 0 0 0 | 0 0 0
$ ./ssolve empty.txt
```
