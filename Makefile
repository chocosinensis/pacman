make:
	gcc -g main.c -I./raylib/raylib-6.0_linux_amd64/include ./raylib/raylib-6.0_linux_amd64/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -o ./build/app && ./build/app

pull:
	git pull origin main

push:
	git push origin main
