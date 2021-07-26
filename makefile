CC=g++
SRCDIR=src
BUILDDIR=bin

CFILES  = $(shell find $(SRCDIR) -name '*.cpp')
OBJ=$(CFILES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: build

build: setupBinDir link

link: $(OBJ)
	@$(CC) $(OBJ) -o j

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "[$(CC)][$<]"
	@$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

setupBinDir:
	@mkdir -p $(BUILDDIR)
	@cd $(SRCDIR) && dirs=$$(find -type d) && cd ../$(BUILDDIR) && mkdir -p $$dirs

clean:
	rm -rf bin j