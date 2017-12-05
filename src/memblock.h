#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct memory_block {
	int start_index;
	int size;
} memblock_t;

void memblock_move(memblock_t* block, int offset){
	block->start_index += offset;
}

void memblock_expand(memblock_t* block, int size){
	block->size += size;
}

void memblock_shrink(memblock_t* block, int size){
	memblock_expand(block, -size);
}

/**
 * Chops off the head of the given block, and returns it to us.
 * 
 * Modifies the old block so that it starts where the new block ends.
 */
memblock_t memblock_split_head(memblock_t* source_block, int new_size){
	memblock_t head_block = {source_block->start_index, new_size};

	// move and shrink the old block to start after the 
	memblock_move(source_block, new_size);
	memblock_shrink(source_block, new_size);

	return head_block;
}

int memblock_are_continuous(memblock_t* first, memblock_t* second){
	return (first->start_index + first->size) == second->start_index;
}

/**
 * Merges two memblock_t objects, which are assumed to be continuous.
 * Merging happens by expanding the first to include the second's memory.
 *
 * After this point, the second block should not be accessed.
 * It will be neither deleted nor modified, so handle memory outside.
 */
void memblock_merge(memblock_t* first, memblock_t* second){
	memblock_expand(first, second->size);
}

memblock_t* memblock_alloc(int num){
	return (memblock_t*) malloc(sizeof(memblock_t) * num);
}

/**
 * Allocate a single new memblock_t with the given properties.
 */
memblock_t* memblock_new(int start_index, int size){
	memblock_t* out = memblock_alloc(1);
	*out = (memblock_t){start_index, size};
	return out;
}

/**
 * returns a negative number if the left block comes before right,
 * a positive number if the right block comes before left,
 * and 0 if they are at the same spot.
 */
int memblock_compare_order(memblock_t* left, memblock_t* right){
	return (left->start_index) - (right->start_index);
}

int memblock_left_comes_before_right(memblock_t* left, memblock_t* right){
	return memblock_compare_order(left, right) < 0;
}

memblock_t* memblock_get_first(memblock_t* one, memblock_t* two){
	if(memblock_left_comes_before_right(one, two)){
		return one;
	}
	return two;
}

memblock_t* memblock_get_last(memblock_t* one, memblock_t* two){
	if(memblock_left_comes_before_right(one, two)){
		return two;
	}
	return one;
}

void fprint_memblock(FILE* file, memblock_t* block){
	fprintf(file, "@%d: %d", block->start_index, block->size);
}