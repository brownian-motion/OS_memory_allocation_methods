#pragma once
#include "process.h"
#include "array_operations.h"

int find_process_index(process_t** arr, char* name){
	for(int i = 0; i < curr_size((void**)arr); i++){
		if(process_name_matches(arr[i], name)){
			return i;
		}
	}
	return -1;
}

process_t* remove_process(process_t** arr, char* name){
	int index = find_process_index(arr, name);
	return (process_t*) remove_from_array((void**) arr, index);
}