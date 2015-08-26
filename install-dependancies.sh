#!/bin/bash

echo -e "Needed libs to compile \n libsdl1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev libx11-dev"
sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev libx11-dev
echo "Done"
echo "We'll need droid fonts too. Otherwise it'll crash"
sudo apt-get install fonts-droid
echo "Done"
echo "You'll need to switch to xscreensaver. Installing."
sudo apt-get install xscreensaver
echo "Done"
