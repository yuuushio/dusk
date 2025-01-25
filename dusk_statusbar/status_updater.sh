#!/bin/bash

# Directory for status bar scripts
STATUSBAR_DIR="./c-bins"

# Function to check for existing script instances and kill them
for pid in $(pidof -x "$(basename "$0")"); do
    if [ "$pid" != "$$" ]; then
        echo "$(date +"%F %T"): $(basename "$0") is already running with PID $pid, killing"
        kill "$pid"
    fi
done

# Artificial sleep to ensure the IPC handler is ready
sleep 0.5

SETSTATUS="duskc --ignore-reply run_command setstatus"

# Seconds counter
secs=0

while true; do
    # Modules that need frequent updates
    $SETSTATUS 0 "$("$STATUSBAR_DIR/time")" &
    $SETSTATUS 1 "$("$STATUSBAR_DIR/clock")" &
    $SETSTATUS 4 "$("$STATUSBAR_DIR/vol_bar")" &

    # Modules that need less frequent updates
    if [ $((secs % 15)) -eq 0 ]; then
        $SETSTATUS 2 "$("$STATUSBAR_DIR/network")" &
        $SETSTATUS 3 "$("$STATUSBAR_DIR/bluetooth")" &
        $SETSTATUS 5 "$("$STATUSBAR_DIR/mem_perc")" &
        $SETSTATUS 6 "$("$STATUSBAR_DIR/mem_used")" &
    fi

    # Uncomment and modify this block if you want hourly updates
    # if [ $((secs % 3600)) -eq 0 ]; then
    #     $SETSTATUS 4 "$("$STATUSBAR_DIR/sysupdates_paru")" &
    # fi

    ((secs++))
    sleep 1
done
