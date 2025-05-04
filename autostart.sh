#! /bin/bash

#~/.dwm/swap_capslock &
~/.dwm/mouse_sens.sh &
~/.dwm/xrand_display.sh &
xset r rate 300 50 &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
xbindkeys &
redshift -P -O 3300 -b 0.9:0.9 &
dbus-launch --sh-syntax --exit-with-session
# pkill pipewire &
dunst &
# slstatus &
~/.dwm/dusk_statusbar/status_updater.sh &
# dwmblocks &

# This just makes things a slow
# picom --config ~/.config/picom.conf &
picom &

feh --bg-scale ~/Other/Pictures/wallpapers/wallhaven-yx5kml_2560x1440.png &

dusk
