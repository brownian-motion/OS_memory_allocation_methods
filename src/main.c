//// This is a mockup of the OS project

#include "main.h"

int main(int argc, char** argv){
	free_memory[0] = NULL;
	processes[0] = NULL;

	if(argc >= 3){
		TOTAL_MEMORY_SIZE = atoi(argv[2]); //read integer from string argument
	}
	append_to_end((void**)free_memory, memblock_new(0, TOTAL_MEMORY_SIZE));

	if(argc >= 2){
		if(streq(argv[1], "BESTFIT")){
			fit_function = get_best_fit_block;
		}
		else if(streq(argv[1], "FIRSTFIT")){
			fit_function = get_first_fit_block;
		}
		else if(streq(argv[1], "NEXTFIT")){
			//fit_function = get_next_fit_block;
		}
		else if(streq(argv[1], "BUDDY")){
			//fit_function = get_buddy_fit_block;
			//TODO: also change the 'restore' function
		}
	}

	if(argc >= 4){
		freopen(argv[3], "r", stdin); //so I can test it by scripting
		debug("Reading from ");
		debugln(argv[3]);
		interactive = 0;
	}

	//assume first fit for now, for simplicity
	while(!feof(stdin)){
		buffer[0] = '\0'; //empty string to start
		print_prompt();
		fgets(buffer, STRING_BUFFER_SIZE, stdin);
		strtok(buffer, "\n"); //take out trailing newline if not empty string
		if(!interactive)
			fprintf(stderr, "%s\n", buffer); //so we can see what it was
		if(strlen(buffer) == 0){
			continue;
		}
		args = str_split(buffer, ' ');
		int num_args = curr_size((void**) args);
		if(num_args > 0){
			if(streq(args[0], LIST_FREE_MEMORY_COMMAND)){
				debugln("Listing free memory: ");
				print_free_memory();
				// debugln("PRINTED MEMORY");
			} else if(streq(args[0], LIST_PROCESSES_COMMAND)) {
				debugln("Listing processes:");
				print_processes();
			} else if(streq(args[0], REQUEST_MEMORY_COMMAND)) {
				if(num_args >= 3){
					// debug("Requesting ");
					// debug(args[2]);
					// debug(" units of memory for process ");
					// debug(args[1]);
					// debugln(":");
					make_process(args[1], atoi(args[2]));
				}
			} else if(streq(args[0], RELEASE_PROCESS_COMMAND)){
				if(num_args >= 2){
					// debug("Releasing process ");
					// debug(args[1]);
					// debugln(":");
					release_process(args[1]);
				}
			} else if(streq(args[0], EXIT_COMMAND)){
				return 0;
			}
		}
	}

	debugln("");
}