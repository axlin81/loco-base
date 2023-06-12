#ifndef LOCO_BASE_PUBLISHER__H
#define LOCO_BASE_PUBLISHER__H

#include <loco-base/config.h>
#include <loco-base/object.h>

typedef void (*loco_subscriber_callback_t)(loco_handle_t, loco_handle_t);

loco_handle_t loco_publisher_create(const char *name,
                                    loco_handle_t owner);

void loco_publisher_publish(loco_handle_t instance);

bool loco_publisher_add_subscription(loco_handle_t instance,
                                     loco_handle_t object,
                                     loco_subscriber_callback_t callback);

#endif
