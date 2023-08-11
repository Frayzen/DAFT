# project name (generate executable with this name)
TARGET   = DAFT_dev

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -Werror 

# linking flags here
PKG_CONFIG = $(shell pkg-config --libs sdl2 SDL2_image)
LIBS = -fopenmp -lSDL2 -lm $(PKG_CONFIG) -g
LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -Werror 

# change these to proper directories where each file should be
SRCDIR   = src
INCLUDEDIR = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
OBJECTS  := $(subst $(SRCDIR), $(OBJDIR), $(SOURCES:.c=.o))

ifdef OS
# Windows stuff
	LIBS := $(LIBS) -IC:\mingw64\x86_64-w64-mingw32\include\SDL2
	LFLAGS := $(LFLAGS) -LC:\mingw64\x86_64-w64-mingw32\lib
	rmdir 	 = rmdir /Q /S
	rm 	 = rm
	mkdir = if not exist "$(strip $(1))" mkdir "$(strip $(1))"
	CFLAGS := -std=gnu99
else
# Linux stuff
	rm       = rm -f
	rmdir       = rm -f
	mkdir = mkdir -p $(1)
	CFLAGS := -std=c99
endif



$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(call mkdir, $(BINDIR))
	@$(call mkdir, $(OBJDIR))
	@$(call mkdir, $(dir $@))
	@$(LINKER) $(OBJECTS) $(LIBS) -o $@ $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(call mkdir, $(dir $@))
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rmdir) $(OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

