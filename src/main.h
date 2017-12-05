#pragma once 

#include <stdio.h>
#include "process_list.h"
#include "fit_functions.h"
#include "memblock.h"
#include "split.h"
#include "debug.h"
#include "str_helpers.h"

#define streq(a, b) (!strcmp(a, b))

#define MAX_NUM_PROCESSES 100
#define MAX_NUM_MEMBLOCKS 100
long int TOTAL_MEMORY_SIZE;

#define STRING_BUFFER_SIZE 100
char buffer[STRING_BUFFER_SIZE];

int MAX_ARGS;
char** args;

int interactive = 1;
#define PROMPT "==> "
#define print_prompt() fprintf(stderr, "%s", PROMPT)

memblock_t* free_memory[MAX_NUM_MEMBLOCKS];
process_t* processes[MAX_NUM_PROCESSES];

#define LIST_FREE_MEMORY_COMMAND "MEMORY"
#define LIST_PROCESSES_COMMAND "PROCESSES"
#define REQUEST_MEMORY_COMMAND "REQUEST"
#define RELEASE_PROCESS_COMMAND "RELEASE"
#define EXIT_COMMAND "EXIT"

memblock_t* (* fit_function)(memblock_t**, int) = get_first_fit_block;

void print_processes(){
	for(int i = 0 ; i < curr_size((void**) processes); i++){
		fprint_process(stdout, processes[i]);
		fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

void print_free_memory(){
	debugln("Processes:");
	for(int i = 0 ; i < curr_size((void**) free_memory); i++){
		fprint_memblock(stdout, free_memory[i]);
		fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

int find_insertion_location(memblock_t** arr, memblock_t* block){
	for(int i = 0 ; i < curr_size((void**) arr) ; i++){
		if(memblock_left_comes_before_right(block, arr[i])){
			return i;
		}
	}
	return curr_size((void**)arr);
}

void connect_to_next_memory_block(memblock_t** arr, int index){
	if(index >= 0 && arr[index+1] != NULL){
		if(memblock_are_continuous(arr[index], arr[index+1])) {
			memblock_merge(arr[index], arr[index+1]);
			free(remove_from_array((void**)arr, index+1)); //get rid of the second one, since the first was merged in
		}
	}
}

void reconnect_memory_blocks_at(memblock_t** arr, int index){
	//merge on the right
	connect_to_next_memory_block(arr, index);

	//then merge on the left (merging left shifts the array elements)
	connect_to_next_memory_block(arr, index-1);
}

void restore_memory(memblock_t* block){
	// debug("Restoring block ");
	// fprint_memblock(stderr, block);
	// debugln("");
	int reinsert_index = find_insertion_location(free_memory, block);
	fprintf(stderr, "Reinserting at %d\n", reinsert_index);
	insert_into_array((void**) free_memory, reinsert_index, block);
	reconnect_memory_blocks_at(free_memory, reinsert_index);
}

void release_process(char* name){
	// debug("Actually releasing process ");
	// debugln(name);
	process_t* process = remove_process(processes, name);
	// free( name );
	// process->name = NULL; //be safe
	restore_memory(process->memory);
	free( process );
}

void make_process(char* name, int memsize){
	//assume first fit
	// char* name_copy = alloc_str_copy(name);
	memblock_t* big_enough_block = fit_function(free_memory, memsize);
	append_to_end((void**) processes, process_new(name, big_enough_block));
}
