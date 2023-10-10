CC = emcc
CFLAGS = -s WASM=1 -s LEGACY_GL_EMULATION=1 -O3
LIBS = -lGL -lGLU -lglut
OUTPUT = index.js
WASM  = index.wasm
SOURCE = nemo.c

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(SOURCE) $(LIBS) $(CFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(WASM)
