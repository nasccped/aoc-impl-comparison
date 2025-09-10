PC=python
CC=gcc
PYDIR=python
OUTDIR=out
TEMPDIR=temps
CSOURCES=$(wildcard c/*.c)
CFLAGS=-Wall -Wextra
# use .exe since Windows only suport Makefile checking with file extensions
CMAIN=main.exe

all:
	@echo build and run this project!
	@echo Possible args:
	@echo   - pyrun: runs Python project
	@echo   - pytest: runs Python tests only
	@echo   - cbuild: compile C sources
	@echo   - crun: runs C binary
	@echo   - ctest: runs C tests
	@echo warn: crun and ctest requires cbuild first

pyrun:
	@$(PC) $(PYDIR)

pytest:
	@$(PC) $(PYDIR) test

cbuild: $(CSOURCES)
	@if [ ! -d $(OUTDIR) ]; then \
		mkdir $(OUTDIR); \
	fi;
	@if [ ! -d $(TEMPDIR) ]; then \
		mkdir $(TEMPDIR); \
	fi;
	@gcc $(CFLAGS) $^ -d $(OUTDIR)/$(CMAIN)

crun: $(OUTDIR)/$(CMAIN)
	@$<

ctest: $(OUTDIR)/$(CMAIN)
	@$< test

.PHONY: all pyrun pytest cbuild crun ctest
