#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define bar constants
#define NUM_BARS 10
#define FILLED_BAR "─"  // Character for filled bars
#define EMPTY_BAR "─"   // Character for empty bars

int main() {
    int volume;
    bool is_error = false;

    // Check for error using a placeholder method (replace with actual logic)
    FILE *err_check = popen("python ~/.dwm/dwmblocks_scripts/is_error.py", "r");
    if (err_check == NULL) {
        perror("Failed to run is_error.py");
        return 1;
    }
    char err_result[6];
    if (fscanf(err_check, "%5s", err_result) == 1 && strcmp(err_result, "true") == 0) {
        is_error = true;
    }
    pclose(err_check);

    if (is_error) {
        printf("- -\n");
        return 0;
    }

    // Get the current volume using pamixer
    FILE *vol_cmd = popen("pamixer --get-volume", "r");
    if (vol_cmd == NULL) {
        perror("Failed to run pamixer");
        return 1;
    }
    if (fscanf(vol_cmd, "%d", &volume) != 1) {
        perror("Failed to parse volume");
        pclose(vol_cmd);
        return 1;
    }
    pclose(vol_cmd);

int curr_vol_bars = (volume * NUM_BARS) / 100;  // Calculate filled bars
    int remaining_bars = NUM_BARS - curr_vol_bars;  // Calculate empty bars

    char fin_occ[(NUM_BARS * 3) + 1] = {0};  // Buffer for filled portion
    char fin_rem[(NUM_BARS * 3) + 1] = {0};  // Buffer for empty portion

    // Fill the buffers with the appropriate bars
    for (int i = 0; i < curr_vol_bars; i++) {
        strcat(fin_occ, FILLED_BAR);
    }
    for (int i = 0; i < remaining_bars; i++) {
        strcat(fin_rem, EMPTY_BAR);
    }
    // Generate final output
    const char *ICON_SYMB = "^c#4c566a^";
    const char *VOL_COL = "^c#b8dceb^";
    printf("%s^c#b8dceb^%s^d^^c#434c5e^%s%s% d%%^d^\n",
           ICON_SYMB, fin_occ, fin_rem, VOL_COL, volume);

    return 0;
}
