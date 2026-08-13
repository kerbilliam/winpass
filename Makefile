CC = cl

CFLAGS = /nologo /Iinclude /W4 /c

OBJ = build\main.obj build\commands.obj build\path.obj

LDFLAGS = shlwapi.lib

TARGET = build\passw.exe


all: build $(TARGET)

build:
	if not exist build mkdir build


$(TARGET): $(OBJ)
	$(CC) $(OBJ) /Fe$(TARGET) $(LDFLAGS)


build\main.obj: src\main.c include\commands.h include\path.h
	$(CC) $(CFLAGS) /Fobuild\ src\main.c

build\commands.obj: src\commands.c include\commands.h
	$(CC) $(CFLAGS) /Fobuild\ src\commands.c

build\path.obj: src\path.c include\path.h
	$(CC) $(CFLAGS) /Fobuild\ src\path.c


clean:
	del /Q build\*.obj build\*.exe
