main: src/main.c
	cp src/default.frag.glsl build/default.frag.glsl
	cp src/default.vert.glsl build/default.vert.glsl
	cp src/texture.frag.glsl build/texture.frag.glsl
	cp src/texture.vert.glsl build/texture.vert.glsl
	cp resources/* build/
	gcc src/stb_image.o src/*.c -o build/main -Iinclude/ -Llib/ -lglfw3 -lGL -lGLEW -lX11 -lm -Wall -Werror -ggdb

run: main
	cd build; ./main; cd ..
