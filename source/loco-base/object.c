#include <loco-base/object.h>
#include <loco-base/allocator.h>

loco_handle_t loco_object_create(const char *name, size_t size, loco_handle_t allocator)
{
	loco_object_t *object = loco_allocator_alloc(allocator, size);
	
	if (object != NULL) {
		if (name != NULL) {
			strncpy(object->name, name, LOCO_CONFIG_OBJECT_NAME_MAX);
		}
		
		object->allocator = allocator;
	}

	return object;
}
