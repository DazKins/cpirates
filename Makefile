# Compiler
CC = clang

# Compiler Flags
COFLAGS = -I./src -DGL_SILENCE_DEPRECATION
CCFLAGS = -lpng -lglfw -framework OpenGL

# Directories
SRCDIR = src
RESDIR = res
BUILDDIR = build
BINDIR = bin

BINRESDIR = $(BINDIR)/res

# Target executable
TARGET = $(BINDIR)/cpirates

# Source files
SOURCES = $(shell find ${SRCDIR} -name '*.c')

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Shader files
RESS := $(wildcard $(RESDIR)/*)
RES_TARGETS := $(patsubst $(RESDIR)/%, $(BINRESDIR)/%, $(RESS))

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILDDIR) $(BINDIR) $(BINRESDIR))

# Default target
all: $(TARGET) ress

# Link object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(COFLAGS) -c $< -o $@

# Copy shader files to bin directory
ress: $(RES_TARGETS)

$(BINRESDIR)/%: $(RESDIR)/% | $(BINRESDIR)
	cp -r $< $@

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean build and bin directories
clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

.PHONY: all clean
