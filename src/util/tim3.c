#include <sys/time.h>
#include <mach/mach_time.h>
#include <time.h>

static double mach_conversion_factor = 0.0;

void init_mach_conversion_factor() {
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);
  mach_conversion_factor = (double)info.numer / (double)info.denom;
}

void time_init() {
  init_mach_conversion_factor();
}

long get_time_ns() {
  uint64_t mach_time = mach_absolute_time();
  double time_ns = (double)mach_time * mach_conversion_factor;
  return (long)time_ns;;
}

void sleep_ns(long ns) {
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = ns;
  nanosleep(&req, NULL);
}
