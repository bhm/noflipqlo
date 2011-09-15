#!/bin/bash
echo "I'll modify keys for gnome"
gconftool-2 --type boolean -s /apps/gnome_settings_daemon/screensaver/start_screensaver false
echo "Gnome-screensaver shouldn't autostart"
echo "If it still starts up run:"
echo "sudo chmod -x /usr/bin/gnome-screensaver"
echo "Bye"
