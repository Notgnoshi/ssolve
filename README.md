# ssolve

A ISO C11 sudoku solver to learn autotools

## How to build

### The hard way

Don't do this

```sh
aclocal
autoconf
automake --add-missing --copy
./configure
make
./ssolve
```

### The easy way

Do this

```sh
autoreconf --install
mkdir build/
cd build/
../configure
make
./ssolve
```

Use `git clean -f -X -d` to clean up after in-tree builds.
