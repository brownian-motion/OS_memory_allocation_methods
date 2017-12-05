#pragma once

#ifndef NULL
#define NULL 0
#endif

/**
 * Defines a bunch of convenience functions to 
 * interact with primitive arrays of pointers.
 *
 * This is useful to manipulate both arrays of
 * memory blocks but also arrays of processes
 */

void* remove_from_array(void** arr, int index){
	void* out = arr[index];
	//move everything towards the start to fill in the new space
	for(int i = index; arr[i] != NULL ; i++){
		arr[i] = arr[i+1];
	}
	return out;
}

int curr_size(void** arr){
	int i = 0;
	while(arr[i] != NULL)
		i++;
	return i;
}

void insert_into_array(void** arr, int index, void* elem){
	//move everything towards the end so there's room for the new element
	for(int i = curr_size(arr); i >= index; i--){
		arr[i+1] = arr[i];
	}
	arr[index] = elem;
}

void append_to_end(void** arr, void* elem){
	insert_into_array(arr, curr_size(arr), elem);
}

void* remove_from_end(void** arr){
	return remove_from_array(arr, curr_size((void**)arr) - 1);
}