#include <stdio.h>
// might need some more include files here

#define GRADING
#ifndef GRADING
#define HEAPSTATS
#else
#define HEAPSTATS __heapstats((__heapprt)fprintf, stdout)
#endif
