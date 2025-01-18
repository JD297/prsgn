PREFIX        = /usr/local
BINDIR        = $(PREFIX)/bin
MANDIR        = $(PREFIX)/share/man

TARGET        = prsgn
TARGETDIR     = bin
BUILDDIR      = build
SRCDIR        = src
SRCINCLUDEDIR = include
TESTDIR       = tests

SRCFILEEXT    = c
SRCFILES      = $(wildcard $(SRCDIR)/*.$(SRCFILEEXT))
OBJFILEEXT    = o
OBJFILES      = $(patsubst $(SRCDIR)/%.$(SRCFILEEXT),$(BUILDDIR)/%.$(OBJFILEEXT),$(SRCFILES))


CC            = cc
CCLIBS        = -static
CCFLAGS       = -Wall -Wextra -Wpedantic -g
CCINCLUDE     = -I $(SRCINCLUDEDIR)
CCFLAGSPROG   = -DTARGET=\"$(TARGET)\"

$(TARGETDIR)/$(TARGET): $(OBJFILES)
	$(CC) $(CCFLAGS) $(CCINCLUDE) $(OBJFILES) -o $(TARGETDIR)/$(TARGET) $(CCLIBS)

$(BUILDDIR)/%.$(OBJFILEEXT): $(SRCDIR)/%.$(SRCFILEEXT)
	$(CC) $(CCFLAGS) $(CCINCLUDE) $(CCFLAGSPROG) -c -o $@ $<

clean:
	rm -f $(BUILDDIR)/*.$(OBJFILEEXT) $(TARGETDIR)/$(TARGET)

install: $(TARGET)
	cp $(TARGETDIR)/$(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: tests-always-fail

tests: $(TARGETDIR)/$(TARGET) tests-always-fail
	make -f $(TESTDIR)/Makefile TESTDIR="$(TESTDIR)" CC="$(CC)" CCINCLUDE="$(CCINCLUDE)" CCFLAGS="$(CCFLAGS)" BUILDDIR="$(BUILDDIR)" TARGET="$(TARGET)" SRCFILEEXT="$(SRCFILEEXT)" OBJFILEEXT="$(OBJFILEEXT)" OBJFILES="$(OBJFILES)"
