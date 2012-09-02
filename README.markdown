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

----------------------------------
##Whats that?
----------------------------------
It's Open Source port of Fliqlo screensaver for Windows and OSX platforms.
It uses SDL libraries to draw. 
Ever seen a flip clock? No. Google one out. Freaky technology.

It uses xscreensaver. Gnome-screensaver for some reason doesn't like and says "I ain't seen shit" even tho supposedly should see  this program.
If you'd like to fight with it for some time try copying noflipql.desktop file to /usr/share/applications/screensavers/ or ~/.local/share/applications/screensavers/.
Gnome-screensaver is a poopoohead anyway.
a) You won't be able easily switch time mode(24h or AM/PM)
b) It sees screensaver, but it won't do anything. Seems I'd need to drop event handling.


----------------------------------
##Code
----------------------------------

It needs reimplementation to draw via SVG and/or with higher resolution background.
Needs major clean up.

----------------------------------
##INSTALLATION
----------------------------------
Compile and install files with:

	make && sudo make install
	
Install dependencies with

	install-dependancies.sh

To force xscreensaver use

	force_gnome-screensaver_off.sh


