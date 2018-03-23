#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parsers.h"
#include <string.h>



//in C strings are char arrays (char*)
int inputParser(char* curr_prog, int argc, char** argv, int* num_integers, int* min_int, int* max_int, unsigned long* seed, int* isDashO, char** output_file_name, char* arguments, int* isDashI, char** input_file_name, int* isDashC, char** count_file_name){

	opterr = 0;
	
	int currArg;
	char* arg;
	
	//-1 represents end of the arguments
	while((currArg = getopt (argc, argv, arguments)) != -1)
		switch (currArg)
			{
			case 'u':
				//print to stferr
				if(strcmp(curr_prog,"prog1generator") == 0){
					fprintf(stderr, "prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(strcmp(curr_prog,"prog1sorter") == 0){
					fprintf(stderr, "prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
				}
				exit(1);
				break;
			case 'n':
				arg = optarg;
				//from ascii to integer
				*num_integers = atoi(arg);
				break;
			case 'm':
				arg = optarg;
				*min_int = atoi(arg);
				break;
			case 'M':
				arg = optarg;
				*max_int = atoi(arg);
				break;
			case 's':
				arg = optarg;
				*seed = atoi(arg);
				break;
			case 'o':
				*isDashO = 1;
				arg = optarg;
				*output_file_name = arg;
				break;
			case 'i':
				*isDashI = 1;
				arg = optarg;
				*input_file_name = arg;
				break;
			case 'c':
				*isDashC = 1;
				arg = optarg;
				*count_file_name = arg;
				break;
			case '?':
				if(optopt == 'n'){
					fprintf (stderr, "-n is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 'm'){
					fprintf (stderr, "-m is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 'M'){
					fprintf (stderr, "-M is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 's'){
					fprintf (stderr, "-s is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 'o'){
					fprintf (stderr, "-o is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 'i'){
					fprintf (stderr, "-i is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else if(optopt == 'c'){
					fprintf (stderr, "-c is missing an argument.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
				} else{
					fprintf(stderr, "Unknown option character %d.\nprog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n", optopt);
				}
				exit(1);
			default:
				abort();
			}
			
	return 0;

}

//int sorterParser(){
//
//}

