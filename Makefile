BUILDDIR = ./build/
SOURCEDIR = ./source/

SDL_INCLUDE = -I/usr/include/SDL2 #-I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks
SDL_LIB = -lSDL2main -lSDL2 -lSDL2_ttf #-framework SDL2 -framework SDL2_ttf


LIBS = # -framework OpenGL -framework GLUT -lpng

CC = gcc-9
CFLAGS = -std=c17 -Wall -Wno-deprecated $(pkg-config --cflags --libs sdl2)#-arch x86_64 # -mmacosx-version-min=10.15 -w

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm

HEADERS = -I./source/headers
TEMP = $(wildcard $(SOURCEDIR)*.c)
SOURCES = $(filter-out $(SOURCEDIR)main.c, $(TEMP))

OBJ = $(subst $(SOURCEDIR), $(BUILDDIR), $(SOURCES:.c=.o)) # change .c to .o
# OBJ = $(SOURCES:.c=.o)


# make_dir:
# 	@mkdir -p $(BUILDDIR)
# 	@mkdir -p $(SOURCEDIR)



TARGET = GB 


.PHONY: depend clean


all: $(TARGET)


$(TARGET) : $(BUILDDIR)main.o $(OBJ)
	$(CC) $(HEADERS) -o $(TARGET) $(OBJ) $(BUILDDIR)main.o $(CFLAGS) $(SDL_INCLUDE) $(SDL_LIB) $(LIBS)


$(BUILDDIR)%.o: $(SOURCEDIR)%.c
	$(CC) $(HEADERS) -c $< -o $@ $(CFLAGS) $(SDL_INCLUDE) $(SDL_LIB) $(LIBS)



clean:
	rm $(BUILDDIR)* $(TARGET)

depend: $(SOURCES)
	makedepend $(HEADERS) $^
