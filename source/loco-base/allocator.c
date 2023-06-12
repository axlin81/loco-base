#include <loco-base/allocator.h>
#include <loco-base/memory.h>

typedef struct allocator_s {
	uintptr_t addr_beg;
	uintptr_t addr_cur;
	uintptr_t addr_end;
	uintptr_t alignment;
	uintptr_t max_unaligned;
	uintptr_t alignment_mask;
} allocator_t;

static struct {
	uint8_t meta_alloc_mem[LOCO_CONFIG_META_ALLOCATOR_MEM];
	allocator_t meta_alloc;
} g_allocator LOCO_MEMORY_CACHE_ALIGN = {
	.meta_alloc_mem = { 0 },
	.meta_alloc = {
		.addr_beg = (uintptr_t)&g_allocator.meta_alloc_mem[0],
		.addr_cur = (uintptr_t)&g_allocator.meta_alloc_mem[0],
		.addr_end = (uintptr_t)&g_allocator.meta_alloc_mem[LOCO_CONFIG_META_ALLOCATOR_MEM],
		.alignment = 1,
		.max_unaligned = 0,
		.alignment_mask = ~0
	}
};

static inline uintptr_t round_up_to_alignment(loco_handle_t inst, uintptr_t addr)
{
	allocator_t *self = (allocator_t *)inst;
	return (addr + self->max_unaligned) & self->alignment_mask;
}

loco_handle_t loco_allocator_create(const char *name, uintptr_t addr_beg, uintptr_t addr_end, uintptr_t alignment)
{
	const uintptr_t max_unaligned = alignment - 1;
	const uintptr_t alignment_mask = ~max_unaligned;
	const uintptr_t addr_cur = (addr_beg + max_unaligned) & alignment_mask;

	const bool valid_alignment = (alignment != 0) || ((alignment & max_unaligned) == 0);
	const bool valid_address_range = (addr_end > addr_cur);

	allocator_t *new_allocator = NULL;

	if (valid_alignment && valid_address_range) {
		new_allocator = loco_object_create(name, sizeof *new_allocator, &g_allocator);

		if (new_allocator != NULL) {
			new_allocator->addr_beg = addr_beg;
			new_allocator->addr_cur = addr_cur;
			new_allocator->addr_end = addr_end;
			new_allocator->alignment = alignment;
			new_allocator->max_unaligned = max_unaligned;
			new_allocator->alignment_mask = alignment_mask;
		}
	}

	return new_allocator;
}

void *loco_allocator_alloc(loco_handle_t instance, size_t bytes)
{
	allocator_t *self = (allocator_t *)instance;
	bytes = round_up_to_alignment(instance, bytes);

	const uintptr_t next_cur = self->addr_cur + bytes;
	if (next_cur > self->addr_end) return NULL;

	void *allocation = (void *)self->addr_cur;
	memset(allocation, 0, bytes);
	self->addr_cur = next_cur;

	return allocation;
}
