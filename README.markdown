	/*
	 * Copyright (c) 2010 Kuźniarski Jacek <JKuźniarski@gmail.com>
	 *
	 * Permission to use, copy, modify, and distribute this software for any
	 * purpose with or without fee is hereby granted, provided that the above
	 * copyright notice and this permission notice appear in all copies.
	 *
	 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
	 */

#Whats that?
It's Open Source port of Fliqlo screensaver for Windows and OSX platforms.
Uses SDL libraries to draw to screen.
No idea who uses screensavers these days, but still was fun to write it.

##What's that?
It's Open Source implementation of Fliqlo screensaver that's available for Windows and OSX platforms.
It uses SDL libraries to draw. 
Ever seen a flip clock? No. Google one out. Freaky technology.

#Changelog
##2.0
* Code was cleaned up
* Moved away from using a bitmap onto drawing with primitives to draw a background. Still needs aliasing for jagged corners;
* Custom width, height, Truetype font now supported.

#INSTALLATION
Compile and install files with:

	make && sudo make install
	
Install dependencies with

	install-dependancies.sh

To force xscreensaver use

	force_gnome-screensaver_off.sh
