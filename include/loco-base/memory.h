#ifndef LOCO_BASE_MEMORY__H
#define LOCO_BASE_MEMORY__H

#include <loco-base/config.h>

#define LOCO_MEMORY_CACHE_ALIGN                 __attribute__((aligned(LOCO_CONFIG_CACHE_LINE_SIZE)))

#endif
