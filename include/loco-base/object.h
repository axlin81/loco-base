#ifndef LOCO_BASE_OBJECT__H
#define LOCO_BASE_OBJECT__H

#include <loco-base/config.h>

typedef void *loco_handle_t;

typedef struct loco_object_s {
	const char name[LOCO_CONFIG_OBJECT_NAME_MAX + 1];
	loco_handle_t allocator;
} loco_object_t;

loco_handle_t loco_object_create(const char *name, size_t size, loco_handle_t allocator);

#endif
