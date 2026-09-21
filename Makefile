make:
	gcc -g main.c -I./raylib/raylib-6.0_linux_amd64/include ./raylib/raylib-6.0_linux_amd64/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -o ./build/app && ./build/app

run:
	gcc -g main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo -o ./build/main && ./build/main

pull:
	git pull origin main

push:
	git push origin main
