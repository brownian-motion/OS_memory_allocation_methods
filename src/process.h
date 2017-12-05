#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memblock.h"

/**
 * Defines "processes", which are just
 * memory blocks associated with some name
 */

typedef struct process {
	char* name;
	memblock_t* memory;
} process_t;

process_t* process_alloc(int num){
	return (process_t*) malloc(sizeof(process_t) * num);
}

process_t* process_new(char* name, memblock_t* memory){
	process_t* out = process_alloc(1);
	*out = (process_t) {name, memory};
	return out;
}

void fprint_process(FILE* file, process_t* process){
	fprintf(file,
		"(%s, %d, %d)",
		process->name,
		process->memory->start_index,
		process->memory->size);
}

int process_name_matches(process_t* process, char* name){
	return !strcmp(process->name, name);
}