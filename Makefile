main: src/main.c
	cp src/default.frag.glsl build/default.frag.glsl
	cp src/default.vert.glsl build/default.vert.glsl
	gcc src/*.c -o build/main -Iinclude/ -Llib/ -lglfw3 -lGL -lGLEW -lX11 -lm -Wall -Werror -ggdb

run: main
	cd build; ./main; cd ..
