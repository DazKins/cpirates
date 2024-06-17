# Compiler
CC = cc

# Compiler Flags
CFLAGS = -lglfw -framework OpenGL

# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/cCraft

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILDDIR) $(BINDIR))

# Default target
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build and bin directories
clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

.PHONY: all clean
