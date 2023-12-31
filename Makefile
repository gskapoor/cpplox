CXX := g++            # Compiler
CXXFLAGS := -std=c++17 # Compiler flags
SRCDIR := src          # Source code directory
BUILDDIR := build      # Build directory
TARGET := main.out   # Executable name

# Source files
SRCEXT := cpp
SOURCES := src/Literal.cpp src/Scanner.cpp src/Token.cpp src/main.cpp
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(info SOURCES: $(SOURCES))
$(info OBJECTS: $(OBJECTS))

# Build executable
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CXX) $^ -o $(TARGET)

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " Compiling $<..."
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo " Cleaning..."
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: run

run: $(TARGET)
	@echo " Running..."
	./$(TARGET)
