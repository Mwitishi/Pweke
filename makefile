CC=gcc
WIN_CC=i586-mingw32msvc-gcc
CFLAGS=-Wall
WINFLAGS=-Wall -lmingw32 -lglu32
SDLFLAGS=-lSDLmain -lSDL -lSDL_image
GLFLAGS=-lGL
WINGLFLAGS=-lopengl32 -lglu32

SOURCEDIR=.
BINDIR=../bin

CSOURCE=pweke.c pwent.c
INDIR_CSOURCE=$(addprefix $(SOURCEDIR)/,$(CSOURCE))
CHEADER=pweke.h
INDIR_CHEADER=$(addprefix $(SOURCEDIR)/,$(CHEADER))
BIN=pweke
EXE=pweke.exe

all: $(BINDIR)/$(BIN)

win: $(BINDIR)/$(EXE)

clean:
	rm -f $(BINDIR)/$(BIN) $(BINDIR)/$(EXE)

$(BINDIR)/$(BIN): $(INDIR_CSOURCE) $(INDIR_CHEADER)
	$(CC) $(CFLAGS) $(INDIR_CSOURCE) -o $(BINDIR)/$(BIN) $(SDLFLAGS) $(GLFLAGS)

$(BINDIR)/$(EXE): $(INDIR_CSOURCE) $(INDIR_CHEADER)
	$(WIN_CC) $(WINFLAGS) $(INDIR_CSOURCE) -o $(BINDIR)/$(EXE) $(SDLFLAGS) $(WINGLFLAGS)

