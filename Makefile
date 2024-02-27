main: src/main.c
	cp src/fragment.glsl build/fragment.glsl
	cp src/vertex.glsl build/vertex.glsl
	gcc src/*.c -o build/main -Iinclude/ -Llib/ -lglfw3 -lGL -lGLEW -lX11 -lm -Wall -Werror -ggdb

run: main
	cd build; ./main; cd ..
