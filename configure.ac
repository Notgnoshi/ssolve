AC_PREREQ([2.71])
AC_INIT([ssolve],[0.1])
AM_INIT_AUTOMAKE([foreign subdir-objects])
LT_INIT
# Not portable, but all the stackoverflow links I found didn't work
: ${CFLAGS="-g -O2 -std=c11 \
    -Wall -Wextra -Wpedantic -Wshadow -Wstrict-overflow -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
    -Wformat=2 -Wno-unused-parameter -Wwrite-strings -Wstrict-prototypes -Wold-style-definition \
"}
AC_LANG([C])
AC_PROG_CC
AC_CONFIG_FILES(Makefile)
AC_OUTPUT
