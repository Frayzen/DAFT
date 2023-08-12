# project name (generate executable with this name)
TARGET   = DAFT_dev

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -Werror -fopenmp 

# linking flags here
PKG_CONFIG = $(shell pkg-config --libs sdl2 SDL2_image)
PKG_CONFIG_LINKER = $(shell pkg-config --libs sdl2 SDL2_image)
ifdef OS
#remove -mwindows flag on windows
PKG_CONFIG_LINKER := $(subst -mwindows,,$(PKG_CONFIG_LINKER))
endif
LIBS = $(PKG_CONFIG) -lm -fopenmp -g
LIBS_LINKER = $(PKG_CONFIG_LINKER) -lm -fopenmp -g
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
	rmdir 	 = rmdir /Q /S
	rm 	 = rm
	mkdir = if not exist "$(strip $(1))" mkdir "$(strip $(1))"
	CFLAGS := -std=c99
else
# Linux stuff
	rm       = rm -f
	rmdir       = rm -f
	mkdir = mkdir -p $(1)
	CFLAGS := -std=c99
	LIBS := -fsanitize=address
endif



$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(call mkdir, $(BINDIR))
	@$(call mkdir, $(OBJDIR))
	@$(call mkdir, $(dir $@))
	$(LINKER) $(OBJECTS) $(LFLAGS) $(LIBS_LINKER) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(call mkdir, $(dir $@))
	$(CC) -c $< $(CFLAGS) $(LIBS) -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rmdir) $(OBJDIR)
	@echo "Cleanup complete!"

debug: $(BINDIR)/$(TARGET)
	gdb -ex=r --args $(BINDIR)/$(TARGET) .\test

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

