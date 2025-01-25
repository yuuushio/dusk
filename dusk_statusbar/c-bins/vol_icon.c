#include <stdio.h>
#include <stdlib.h>

int main() {
    int volume;
    char icon[4];

    // Get the volume using pamixer
    FILE *cmd = popen("pamixer --get-volume", "r");
    if (cmd == NULL) {
        perror("Failed to run pamixer");
        return 1;
    }

    // Read the volume from the command output
    if (fscanf(cmd, "%d", &volume) != 1) {
        perror("Failed to parse volume");
        pclose(cmd);
        return 1;
    }
    pclose(cmd);

    // Determine the icon based on the volume
    if (volume > 70) {
        snprintf(icon, sizeof(icon), "");
    } else if (volume < 30) {
        snprintf(icon, sizeof(icon), "");
    } else {
        snprintf(icon, sizeof(icon), "");
    }

    // Output the icon
    printf("%s\n", icon);

    return 0;
}
