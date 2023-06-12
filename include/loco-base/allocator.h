#ifndef LOCO_BASE_ALLOCATOR__H
#define LOCO_BASE_ALLOCATOR__H

#include <loco-base/config.h>
#include <loco-base/object.h>
#include <stdint.h>

loco_handle_t loco_allocator_create(const char *name,
                                    uintptr_t addr_beg,
                                    uintptr_t addr_end,
                                    uintptr_t alignment);

void *loco_allocator_alloc(loco_handle_t instance,
                           size_t bytes);

#endif
