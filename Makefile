 
CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := lib/libmgl.so

BUILDTIME = $(shell date +%Y%m%d-%H%M%S)
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -D"__LIBNAME="\"MGlBase\" -D"__BUILD_DATE="\"$(BUILDTIME)\" -O0 -g -Wall -c -fmessage-length=0 -std=c++14 -fPIC
LIB := 
INC := -I/home/cromas/newgit/json/src -I/usr/include/freetype2 -I/usr/include -I include -I/home/cromas/newgit/mgl/include -I/home/cromas/externalsources/boost_1_58_0

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB) -shared

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p lib
	@mkdir -p $(BUILDDIR)/mglDebug
	@mkdir -p $(BUILDDIR)/mglDataLayer
	@mkdir -p $(BUILDDIR)/mglGui
	@mkdir -p $(BUILDDIR)/mglValues
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)


# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
