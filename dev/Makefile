
# project name (generate executable with this name)
TARGET   = DAFT_dev

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall -Werror 

LIBS = -fopenmp -pthread -lm -ldl `pkg-config --cflags gtk+-3.0 --libs sdl2 SDL2_image` -g
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
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) $(LIBS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(LIBS) -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

