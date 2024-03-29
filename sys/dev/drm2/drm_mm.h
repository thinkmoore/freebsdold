/**************************************************************************
 *
 * Copyright 2006-2008 Tungsten Graphics, Inc., Cedar Park, TX. USA.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: stable/9/sys/dev/drm2/drm_mm.h 249081 2013-04-04 05:39:37Z kib $");

/*
 * Authors:
 * Thomas Hellstrom <thomas-at-tungstengraphics-dot-com>
 */

#ifndef _DRM_MM_H_
#define _DRM_MM_H_

#include <dev/drm2/drm_linux_list.h>

struct drm_mm_node {
	struct list_head node_list;
	struct list_head hole_stack;
	unsigned hole_follows : 1;
	unsigned scanned_block : 1;
	unsigned scanned_prev_free : 1;
	unsigned scanned_next_free : 1;
	unsigned scanned_preceeds_hole : 1;
	unsigned allocated : 1;
	unsigned long start;
	unsigned long size;
	struct drm_mm *mm;
	void *private;
};

struct drm_mm {
	struct list_head hole_stack;
	struct drm_mm_node head_node;
	struct list_head unused_nodes;
	int num_unused;
	struct mtx unused_lock;
	unsigned int scan_check_range : 1;
	unsigned scan_alignment;
	unsigned long scan_size;
	unsigned long scan_hit_start;
	unsigned scan_hit_size;
	unsigned scanned_blocks;
	unsigned long scan_start;
	unsigned long scan_end;
	struct drm_mm_node *prev_scanned_node;
};

static inline bool drm_mm_node_allocated(struct drm_mm_node *node)
{
	return node->allocated;
}

static inline bool drm_mm_initialized(struct drm_mm *mm)
{
	return (mm->hole_stack.next != NULL);
}
#define drm_mm_for_each_node(entry, mm) list_for_each_entry(entry, \
						&(mm)->head_node.node_list, \
						node_list)
#define drm_mm_for_each_scanned_node_reverse(entry, n, mm) \
	for (entry = (mm)->prev_scanned_node, \
		next = entry ? list_entry(entry->node_list.next, \
			struct drm_mm_node, node_list) : NULL; \
	     entry != NULL; entry = next, \
		next = entry ? list_entry(entry->node_list.next, \
			struct drm_mm_node, node_list) : NULL)

/*
 * Basic range manager support (drm_mm.c)
 */
extern struct drm_mm_node *drm_mm_get_block_generic(struct drm_mm_node *node,
						    unsigned long size,
						    unsigned alignment,
						    int atomic);
extern struct drm_mm_node *drm_mm_get_block_range_generic(
						struct drm_mm_node *node,
						unsigned long size,
						unsigned alignment,
						unsigned long start,
						unsigned long end,
						int atomic);
static inline struct drm_mm_node *drm_mm_get_block(struct drm_mm_node *parent,
						   unsigned long size,
						   unsigned alignment)
{
	return drm_mm_get_block_generic(parent, size, alignment, 0);
}
static inline struct drm_mm_node *drm_mm_get_block_atomic(struct drm_mm_node *parent,
							  unsigned long size,
							  unsigned alignment)
{
	return drm_mm_get_block_generic(parent, size, alignment, 1);
}
static inline struct drm_mm_node *drm_mm_get_block_range(
						struct drm_mm_node *parent,
						unsigned long size,
						unsigned alignment,
						unsigned long start,
						unsigned long end)
{
	return drm_mm_get_block_range_generic(parent, size, alignment,
						start, end, 0);
}
static inline struct drm_mm_node *drm_mm_get_block_atomic_range(
						struct drm_mm_node *parent,
						unsigned long size,
						unsigned alignment,
						unsigned long start,
						unsigned long end)
{
	return drm_mm_get_block_range_generic(parent, size, alignment,
						start, end, 1);
}
extern int drm_mm_insert_node(struct drm_mm *mm, struct drm_mm_node *node,
			      unsigned long size, unsigned alignment);
extern int drm_mm_insert_node_in_range(struct drm_mm *mm,
				       struct drm_mm_node *node,
				       unsigned long size, unsigned alignment,
				       unsigned long start, unsigned long end);
extern void drm_mm_put_block(struct drm_mm_node *cur);
extern void drm_mm_remove_node(struct drm_mm_node *node);
extern void drm_mm_replace_node(struct drm_mm_node *old, struct drm_mm_node *new);
extern struct drm_mm_node *drm_mm_search_free(const struct drm_mm *mm,
					      unsigned long size,
					      unsigned alignment,
					      int best_match);
extern struct drm_mm_node *drm_mm_search_free_in_range(
						const struct drm_mm *mm,
						unsigned long size,
						unsigned alignment,
						unsigned long start,
						unsigned long end,
						int best_match);
extern int drm_mm_init(struct drm_mm *mm, unsigned long start,
		       unsigned long size);
extern void drm_mm_takedown(struct drm_mm *mm);
extern int drm_mm_clean(struct drm_mm *mm);
extern unsigned long drm_mm_tail_space(struct drm_mm *mm);
extern int drm_mm_remove_space_from_tail(struct drm_mm *mm,
					 unsigned long size);
extern int drm_mm_add_space_to_tail(struct drm_mm *mm,
				    unsigned long size, int atomic);
extern int drm_mm_pre_get(struct drm_mm *mm);

static inline struct drm_mm *drm_get_mm(struct drm_mm_node *block)
{
	return block->mm;
}

void drm_mm_init_scan(struct drm_mm *mm, unsigned long size,
		      unsigned alignment);
void drm_mm_init_scan_with_range(struct drm_mm *mm, unsigned long size,
				 unsigned alignment,
				 unsigned long start,
				 unsigned long end);
int drm_mm_scan_add_block(struct drm_mm_node *node);
int drm_mm_scan_remove_block(struct drm_mm_node *node);

void drm_mm_debug_table(struct drm_mm *mm, const char *prefix);

#endif
