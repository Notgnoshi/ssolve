bin_PROGRAMS = ssolve
ssolve_SOURCES = \
	src/puzzle.c \
	src/puzzle.h \
	src/parse.c \
	src/parse.h \
	src/main.c

TESTS = \
	tests/cases/empty.txt \
	tests/cases/invalid-full.txt \
	tests/cases/invalid-rows.txt \
	tests/cases/incomplete-row1.txt \
	tests/cases/incomplete-row2.txt
TESTS_ENVIRONMENT = $(srcdir)/tests/runner.sh
