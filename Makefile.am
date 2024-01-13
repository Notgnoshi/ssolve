lib_LTLIBRARIES = libssolve.la
libssolve_la_SOURCES = \
	src/check.c include/ssolve/check.h \
	src/parse.c include/ssolve/parse.h \
	src/puzzle.c include/ssolve/puzzle.h

AM_CFLAGS = -I$(srcdir)/include

bin_PROGRAMS = ssolve
ssolve_SOURCES = main.c
ssolve_LDADD = libssolve.la

check_PROGRAMS = tests/test-stub
tests_test_stub_SOURCES = tests/stub.c

TESTS = \
	tests/test-stub \
	tests/cases/check-empty.txt \
	tests/cases/check-easy1.txt \
	tests/cases/check-easy1-with-violation.txt \
	tests/cases/empty.txt \
	tests/cases/invalid-full.txt \
	tests/cases/invalid-rows.txt \
	tests/cases/incomplete-row1.txt \
	tests/cases/incomplete-row2.txt

TEST_EXTENSIONS = .txt
TXT_LOG_COMPILER = $(srcdir)/tests/runner.sh

data/grid/%.txt: data/grid.tar.gz
	tar --directory data/ -xzvf data/grid.tar.gz
data/line/%.txt: data/line.tar.gz
	tar --directory data/ -xzvf data/line.tar.gz
