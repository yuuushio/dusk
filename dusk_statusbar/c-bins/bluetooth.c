#if 0
gcc -s -O2 -o bt_check -Wno-unused-result bt_check.c
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TEMP_FILE "$HOME/.dwm/dwmblocks_scripts/.bt_tmp" // Adjust the path as needed
#define CONNECTED_ICON "^c#f6bbe7^ 󰂯 ^d^"
#define DISCONNECTED_ICON "^c#4c566a^ 󰂲 ^d^"

// Function to check if the AirPods are connected
bool is_airpods_connected() {
    FILE *cmd = popen("bluetoothctl info | grep 'Connected: yes'", "r");
    if (!cmd) {
        perror("Failed to execute bluetoothctl");
        return false;
    }

    char buffer[128];
    bool connected = false;
    if (fgets(buffer, sizeof(buffer), cmd)) {
        connected = true; // If "Connected: yes" is found, AirPods are connected
    }

    pclose(cmd);
    return connected;
}

// Function to get the previous notification state
int get_previous_state() {
    FILE *file = fopen(TEMP_FILE, "r");
    if (!file) {
        return 1; // Default state if file doesn't exist
    }

    int state;
    if (fscanf(file, "%d", &state) != 1) {
        state = 1; // Default state if reading fails
    }

    fclose(file);
    return state;
}

// Function to save the current state
void save_state(int state) {
    FILE *file = fopen(TEMP_FILE, "w");
    if (!file) {
        perror("Failed to write to temp file");
        return;
    }

    fprintf(file, "%d", state);
    fclose(file);
}

// Function to send a notification
void send_notification(const char *icon_path, const char *title, const char *message) {
    char command[512];
    snprintf(command, sizeof(command),
             "dunstify -i %s -u normal -h string:x-dunst-stack-tag:screenshot -a '♦ Bluetooth ♦' '%s' '%s'",
             icon_path, title, message);
    system(command);
}

int main() {
    bool connected = is_airpods_connected();
    int prev_state = get_previous_state();

    if (connected) {
        if (prev_state == 1) {
            send_notification("$HOME/.dwm/notif_icons/airpods_vec.png",
                              "AirPods Connected!", "Your AirPods are now connected.");
            save_state(2);
        }
        printf("%s\n", CONNECTED_ICON);
    } else {
        if (prev_state == 2) {
            send_notification("$HOME/.dwm/notif_icons/airpods_disconnected.png",
                              "AirPods Disconnected!", "Your AirPods have been disconnected.");
        }
        save_state(1);
        printf("%s\n", DISCONNECTED_ICON);
    }

    return 0;
}
