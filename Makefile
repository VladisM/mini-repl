PRG = repl
BUILDDIR = build
SRCDIR = src
INCDIR = inc

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(addprefix $(BUILDDIR)/, $(notdir $(SRCS:%.c=%.o)))

CC = gcc
CFLAGS = -g -std=c99 -Wall -I$(INCDIR)
LDFLAGS = -lm

.PNOHY: clean all start

all: $(BUILDDIR)/$(PRG)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/tree.h $(INCDIR)/my_math.h $(INCDIR)/stack.h
	$(CC) -c $(CFLAGS) -o $@ $<
	
$(BUILDDIR)/tree.o: $(SRCDIR)/tree.c $(INCDIR)/tree.h
	$(CC) -c $(CFLAGS) -o $@ $<
	
$(BUILDDIR)/my_math.o: $(SRCDIR)/my_math.c $(INCDIR)/my_math.h
	$(CC) -c $(CFLAGS) -o $@ $<
	
$(BUILDDIR)/stack.o: $(SRCDIR)/stack.c $(INCDIR)/stack.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	
$(BUILDDIR)/$(PRG): $(BUILDDIR) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BUILDDIR)/$(PRG)
	
clean:
	rm -rf $(BUILDDIR)

start: all
	$(BUILDDIR)/$(PRG)
