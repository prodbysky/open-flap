main: src/main.c
	gcc src/main.c -o build/main -Iinclude/ -Llib/ -lglfw3 -lGL -lGLEW -lX11 -lm -Wall -Werror -O3

run: main
	cd build; ./main; cd ..
