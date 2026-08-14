CC = cl

CFLAGS = /nologo /utf-8 /Iinclude /Zi /c

OBJ = build\main.obj build\commands.obj build\path.obj build\tree.obj

LDFLAGS = /DEBUG shlwapi.lib

TARGET = winpass.exe


all: build $(TARGET)

build:
	if not exist build mkdir build
	
run: all
	$(TARGET)


$(TARGET): $(OBJ)
	$(CC) $(OBJ) /Fe$(TARGET) /link $(LDFLAGS)


build\main.obj: src\main.c include\commands.h include\path.h
	$(CC) $(CFLAGS) /Fobuild\ src\main.c

build\commands.obj: src\commands.c include\commands.h
	$(CC) $(CFLAGS) /Fobuild\ src\commands.c

build\path.obj: src\path.c include\path.h
	$(CC) $(CFLAGS) /Fobuild\ src\path.c

build\tree.obj: src\tree.c include\tree.h
	$(CC) $(CFLAGS) /Fobuild\ src\tree.c

clean:
	del /Q build\*.obj $(TARGET) *.ilk *.pdb
