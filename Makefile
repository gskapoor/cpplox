CXX := g++
CXXFLAGS := -std=c++23
SRCDIR := src
BUILDDIR := build 
TARGET := main.out

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT)) # GET ALL SOURCE FILES
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)%,$(SOURCES:.$(SRCEXT)=.o))

all: $(TARGET)

main.out: main.o
	$(CXX) -o main.out main.o

main.o: src/main.cpp
	$(CXX) -c src/main.cpp

clean:
	@echo " Cleaning..."; 
	rm -f *.o *~ main

.PHONY: clean