#if 0
gcc -s -O2 -o mem -Wno-unused-result mem.c -lm
exit
#endif

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (!meminfo) {
        perror("Failed to open /proc/meminfo");
        return 1;
    }

    char line[256];
    long total_mem = 0, free_mem = 0, available_mem = 0;

    // Read /proc/meminfo line by line and extract required fields
    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_mem) == 1) continue;
        if (sscanf(line, "MemFree: %ld kB", &free_mem) == 1) continue;
        if (sscanf(line, "MemAvailable: %ld kB", &available_mem) == 1) break; // Exit early after collecting required fields
    }
    fclose(meminfo);

    // Calculate used memory in kilobytes
    long used_mem = total_mem - available_mem; // This closely matches "used" memory in `top`

    // Convert to gigabytes with one decimal place
    double used_mem_gb = used_mem / 1048576.0; // Convert KB to GB (1 GB = 1024 * 1024 KB)

    // Print the result
    printf("%.1fG\n", used_mem_gb);

    return 0;
}
