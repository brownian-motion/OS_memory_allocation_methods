#pragma once

#include "memblock.h"


int get_first_fit_index(memblock_t** memblock_arr, int size){
	for(int i = 0 ; memblock_arr[i] != NULL ; i++){
		if(memblock_arr[i] >= size){
			return i;
		}
	}
	return -1;
}


/**
 * Finds a block big enough to hold the requested memory,
 * splits it into a piece exactly the right size,
 * takes that piece out of the array of free memory,
 * and returns that piece.
 */
memblock_t* get_first_fit_block(memblock_t** arr, int size){
	int best_fit_index = get_first_fit_index(arr, size);

	if(best_fit_index == -1)
		return NULL; //indicate that we could not allocate memory

	//now, get a piece
	memblock_t* best_fit_block = arr[best_fit_index];
	if(best_fit_block->size == size){ //it's exactly the right size, so take it out and return it
		return (memblock_t*) remove_from_array(arr, best_fit_index);
	} else { //it's too big , so we need to split it up
		memblock_t* new_piece = memblock_alloc(1);
		*new_piece = memblock_split_head(best_fit_block, size);
		return new_piece;
	}
}

int best_fit_index(memblock_t** memblock_arr, int size){
	int best_index = -1; //what to report if we find no match
	for(int i = 0 ; memblock_arr[i] != NULL ; i++){
		if(memblock_arr[i]->size >= size){
			if(best_index == -1 //no match yet
				|| memblock_arr[i]->size < memblock_arr[best_index]){
				best_index = i;
			}
		}
	}
	return best_index;
}