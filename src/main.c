//// This is a mockup of the OS project

#include "main.h"

int main(int argc, char** argv){
	free_memory[0] = NULL;
	processes[0] = NULL;

	debug("Made it to main()\n");

	TOTAL_MEMORY_SIZE = atoi(argv[1]); //read integer from string argument
	append_to_end((void**)free_memory, memblock_new(0, TOTAL_MEMORY_SIZE));

	if(argc >= 2)
		freopen(argv[2], "r", stdin); //so I can test it by scripting

	debug("Opened stdin\n");

	//assume first fit for now, for simplicity
	while(!feof(stdin)){
		debug("==> ");
		fgets(buffer, STRING_BUFFER_SIZE, stdin);
		args = str_split(buffer, ' ');
		if(streq(args[0], LIST_FREE_MEMORY_COMMAND)){
			print_free_memory();
		}
	}
}