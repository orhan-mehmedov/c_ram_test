BINDIR  := ../bin
OBJDIR  := ../build
APPNAME := $(BINDIR)/c_ram_test
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,$(OBJDIR)/%.o, $(SOURCES))

INCLUDE := 
LIBPATH := -L/usr/lib
LIBS    := 
CCFLAGS := -g -O0 -Wall # -Wextra -Wpedantic

CC  := gcc

.PHONY: all dirs clean

all: dirs $(OBJECTS)	
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(APPNAME) $(LIBPATH) $(LIBS)

dirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@
  
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
