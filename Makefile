# Compiler
CC = cc

# Compiler Flags
COFLAGS = -DGL_SILENCE_DEPRECATION
CCFLAGS = -lglfw -framework OpenGL

# Directories
SRCDIR = src
SHADERDIR = shaders
BUILDDIR = build
BINDIR = bin

BINSHADERDIR = $(BINDIR)/shaders

# Target executable
TARGET = $(BINDIR)/cCraft

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Shader files
SHADERS := $(wildcard $(SHADERDIR)/*.vert) $(wildcard $(SHADERDIR)/*.frag)
SHADER_TARGETS := $(patsubst $(SHADERDIR)/%, $(BINSHADERDIR)/%, $(SHADERS))

# Create build and bin directories if they don't exist
$(shell mkdir -p $(BUILDDIR) $(BINDIR) $(BINSHADERDIR))

# Default target
all: $(TARGET) shaders

# Link object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(COFLAGS) -c $< -o $@

# Copy shader files to bin directory
shaders: $(SHADER_TARGETS)

$(BINSHADERDIR)/%.vert: $(SHADERDIR)/%.vert | $(BINSHADERDIR)
	cp $< $@

$(BINSHADERDIR)/%.frag: $(SHADERDIR)/%.frag | $(BINSHADERDIR)
	cp $< $@

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean build and bin directories
clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

.PHONY: all clean
