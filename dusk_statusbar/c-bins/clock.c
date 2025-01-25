#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime = time(NULL); // Get the current time
  struct tm timeinfo;          // Struct to store local time
  char buffer[20];             // Buffer for formatted date
  const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  localtime_r(&rawtime, &timeinfo); // Thread-safe conversion to local time

  // Construct the formatted date: "Mon, Jan 01"
  snprintf(buffer, sizeof(buffer), "%s, %s %02d", days[timeinfo.tm_wday],
           months[timeinfo.tm_mon], timeinfo.tm_mday);

  // Output the formatted date
  puts(buffer);

  return 0;
}
