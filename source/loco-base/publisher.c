#include <loco-base/publisher.h>

typedef struct loco_publisher_s {
	loco_object_t loco_obj;

	loco_handle_t owner;
	size_t num_subscribers;

	struct {
		loco_handle_t object;
		loco_subscriber_callback_t callback;
	} subscribers[LOCO_CONFIG_MAX_SUBSCRIBERS];
} loco_publisher_t;

loco_handle_t loco_publisher_create(const char *name,
                                    loco_handle_t owner)
{
	loco_object_t *owner_obj = (loco_object_t *)owner;
	loco_publisher_t *new_publisher = loco_object_create(name, sizeof *new_publisher, owner_obj->allocator);
	new_publisher->owner = owner_obj;
	
	return new_publisher;
}

void loco_publisher_publish(loco_handle_t instance)
{
	loco_publisher_t *self = (loco_publisher_t *)instance;
	for (size_t i = 0; i < self->num_subscribers; ++i) {
		self->subscribers[i].callback(self->subscribers[i].object, self->owner);
	}
}

bool loco_publisher_add_subscription(loco_handle_t instance,
                                     loco_handle_t object,
                                     loco_subscriber_callback_t callback)
{
	loco_publisher_t *self = (loco_publisher_t *)instance;

	if (self->num_subscribers < LOCO_CONFIG_MAX_SUBSCRIBERS) {
		self->subscribers[self->num_subscribers].object = object;
		self->subscribers[self->num_subscribers].callback = callback;
		self->num_subscribers++;

		return true;
	}

	return false;
}
