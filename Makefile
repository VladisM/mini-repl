PRG = repl
BUILDDIR = build
SRCDIR = src

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(addprefix $(BUILDDIR)/, $(notdir $(SRCS:%.c=%.o)))

CC = gcc
CFLAGS = -g -std=c99 -Wall -Iinc/
LDFLAGS = -lm

.PNOHY: clean all start

all: $(BUILDDIR)/$(PRG)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
$(BUILDDIR)/tree.o: $(SRCDIR)/tree.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
$(BUILDDIR)/my_math.o: $(SRCDIR)/my_math.c
	$(CC) -c $(CFLAGS) -o $@ $^
	
$(BUILDDIR)/stack.o: $(SRCDIR)/stack.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	
$(BUILDDIR)/$(PRG): $(BUILDDIR) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BUILDDIR)/$(PRG)
	
clean:
	rm -rf $(BUILDDIR)

start: all
	$(BUILDDIR)/$(PRG)
