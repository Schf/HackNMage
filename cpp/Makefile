MAINFILE= main
SRCFILES=
EXECNAME= game

CC= g++
CCLINKS= -lSDL2
CCFLAGS= -std=c++17
OBJDIR=bin
OBJSFX=.o
SRCDIR=src
SRCSFX=.cpp
LIBDIR=$(SRCDIR)
LIBSFX=.hpp

objfunc = $(addprefix $(OBJDIR)/, $(addsuffix $(OBJSFX), $(notdir $(1))))
objects = $(call objfunc,$(MAINFILE))
objects += $(call objfunc,$(SRCFILES))

srcfunc = $(addprefix $(SRCDIR)/, $(addsuffix $(SRCSFX), $(1)))
sources = $(call srcfunc,$(MAINFILE))
sources += $(call srcfunc,$(SRCFILES))

libfunc = $(addprefix $(LIBDIR)/, $(addsuffix $(LIBSFX), $(1)))
libraries = $(call libfunc,$(SRCFILES))

run: all
	./$(EXECNAME)

all: $(objects) $(sources) $(libraries)
	$(CC) $(CCLINKS) -o $(EXECNAME) $(objects)

$(objects): $(sources) $(libraries) | $(OBJDIR)
	$(foreach file,$(sources),$(CC) $(CCFLAGS) -c $(file) -o \
	$(addsuffix $(OBJSFX), $(addprefix $(OBJDIR)/, $(notdir $(basename $(file))))) |) :

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXECNAME)
