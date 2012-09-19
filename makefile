#Compiler
CC=g++
#Flags
#CFLAGS= -Wall `sdl-config --cflags`  `sdl-config --libs` -lX11 -lSDL_ttf -lSDL_gfx main.cpp -o noflipqlo
CFLAGS= -o noflipqlo main.cpp `sdl-config --libs --cflags`
LDFLAGS=  -lX11 -lSDL_ttf -lSDL_gfx

all: noflipqlo

install-shortcuts:
	cp xscreenserver-demo.desktop ~/.config/autostart/
	cp noflipqlo.desktop ~/.local/share/applications/screensavers

noflipqlo: main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS)
install:
	install -o root noflipqlo /usr/lib/xscreensaver/
	install -o root noflipqlo.xml /usr/share/xscreensaver/config/
	install -o root back.bmp /usr/share/images/		
clean:
	rm -rf noflipqlo
