
#if 0
gcc -s -O2 -o internet_check -Wno-unused-result internet_check.c
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Function to check if wireless interface is up
bool is_wireless_up() {
    FILE *wireless_file = fopen("/proc/net/wireless", "r");
    if (!wireless_file) {
        return false; // If file can't be opened, assume no wireless
    }

    char line[256];
    int line_count = 0;
    bool found = false;

    while (fgets(line, sizeof(line), wireless_file)) {
        line_count++;
        if (line_count > 2) { // Lines after the 2nd indicate wireless interfaces
            found = true;
            break;
        }
    }

    fclose(wireless_file);
    return found;
}

// Function to check if we can ping a public DNS server (e.g., Google)
bool is_internet_accessible() {
    int ret = system("ping -c 1 -W 1 8.8.8.8 > /dev/null 2>&1");
    return ret == 0; // Return true if ping succeeds
}

int main() {
    const char *connected_icon = "^c#f6bbe7^ ^d^";
    const char *disconnected_icon = "^c#4c566a^ ^d^";

    // Check if wireless interface is up
    if (is_wireless_up()) {
        // Check if internet is accessible
        if (is_internet_accessible()) {
            printf("%s\n", connected_icon);
        } else {
            printf("%s (no internet)\n", disconnected_icon);
        }
    } else {
        printf("%s\n", disconnected_icon);
    }

    return 0;
}
