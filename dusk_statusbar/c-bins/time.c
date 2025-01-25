#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime = time(NULL); // Get the current time
  struct tm timeinfo;          // Struct to store local time
  char buffer[20];             // Buffer for formatted time

  localtime_r(&rawtime, &timeinfo); // Thread-safe conversion to local time

  // Convert 24-hour format to 12-hour format and determine AM/PM
  int hour = timeinfo.tm_hour % 12;
  if (hour == 0)
    hour = 12; // Handle midnight and noon

  const char *ampm = (timeinfo.tm_hour >= 12) ? "PM" : "AM";

  // Format the time: "hh:mm:ss AM/PM"
  snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d %s", hour, timeinfo.tm_min,
           timeinfo.tm_sec, ampm);

  // Output the formatted time
  puts(buffer);

  return 0;
}
