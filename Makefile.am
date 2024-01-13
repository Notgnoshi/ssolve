bin_PROGRAMS = ssolve
ssolve_SOURCES = \
	src/check.c src/check.h \
	src/parse.c src/parse.h \
	src/puzzle.c src/puzzle.h \
	src/main.c

TESTS = \
	tests/cases/check-empty.txt \
	tests/cases/check-easy1.txt \
	tests/cases/check-easy1-with-violation.txt \
	tests/cases/empty.txt \
	tests/cases/invalid-full.txt \
	tests/cases/invalid-rows.txt \
	tests/cases/incomplete-row1.txt \
	tests/cases/incomplete-row2.txt
TESTS_ENVIRONMENT = $(srcdir)/tests/runner.sh
