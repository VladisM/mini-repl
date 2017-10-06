PRG = repl
OBJS = main

BUILDDIR = build

all: $(BUILDDIR)/$(PRG)

$(BUILDDIR)/$(PRG): src/$(OBJS).c
	gcc $< -lm -o $@

.PHONY: clean start

clean:
	rm -rf $(BUILDDIR)

start: $(BUILDDIR)/$(PRG)
	$(BUILDDIR)/$(PRG)
