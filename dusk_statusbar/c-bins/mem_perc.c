#if 0
gcc -s -O2 -o mem -Wno-unused-result mem.c -lm
exit
#endif

#include <stdio.h>

int main() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (!meminfo) {
        perror("Failed to open /proc/meminfo");
        return 1;
    }

    long total_mem = 0, available_mem = 0;
    char line[256];

    // Read only the necessary fields from /proc/meminfo
    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_mem) == 1) continue;
        if (sscanf(line, "MemAvailable: %ld kB", &available_mem) == 1) break;
    }
    fclose(meminfo);

    // Calculate percentage of memory used, rounded to the nearest whole number
    int used_percent = (int)(0.5 + 100.0 * (total_mem - available_mem) / total_mem);

    // Print the percentage
    printf("(%d%)\n", used_percent);

    return 0;
}
