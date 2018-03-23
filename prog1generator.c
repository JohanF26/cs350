#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "parsers.h"

//in C strings are char arrays (char*)

int main(int argc, char** argv){
	
	//-n
	int num_integers = 100;

	//-m
	int min_int = 1;

	//-M
	int max_int = 255;

	//-s
	unsigned long seed = time(0);

	//-o set to false by default
	int isDashO = 0;
	char* output_file_name = NULL;
	FILE* output_file;
	
	//These values will not be used by the generator but are needed for the parser
	int temp1 = 0;
	char* temp2 = NULL;
	int temp3 = 0;
	char* temp4 = NULL;
	//u, n, m, M, s, o
	//putting a colon means the argument has a reguired argument, u does not need an argument
	
	//to be able to use the same function for both programs like specified in the description we need to
	//pass all the possible things that could be parsed from the command line
	
	inputParser("prog1generator", argc, argv, &num_integers, &min_int, &max_int, &seed, &isDashO, &output_file_name, "un:m:M:s:o:", &temp1, &temp2, &temp3, &temp4);
	
	
	//check n input
	if(num_integers < MIN_NUM_INTS || num_integers > MAX_NUM_INTS){
		fprintf(stderr, "The number of integers cannot be less than 0 or greater than 1000000.\n");
		exit(1);
	}
	
	//check m input
	if(min_int < MIN_MIN_INT){
		fprintf(stderr, "The minimum value of the integers cannot be less than 1.\n");
		exit(1);
	}
	
	//check M input
	if(max_int > MAX_MAX_INT){
		fprintf(stderr, "The maximum value of the integers cannot be greater than 1000000.\n");
		exit(1);
	} else if(max_int < min_int){
		fprintf(stderr, "The maximum value of the integers cannot be less than the minimum value.\n");
		exit(1);
	}
	
	//seed the random generator with time or with an input
	srand(seed);
	
	int randInt;
	//check o input
	if(isDashO != 1){
		printf("%d\n", num_integers);
		for(int i = 0; i < num_integers; i++){
			//to generate a random int between a range we do
			//rand() % (max + 1 - min) + min
			randInt = rand() % (max_int + 1 - min_int) + min_int;
			printf("%d\n", randInt);
		}
	} else{
		//open output file and write to it, also 
		output_file = fopen(output_file_name, "w");
		//insert the number of integers being generated as first line
		if(output_file != NULL){
			fprintf(output_file, "%d\n", num_integers);
		} else{
			fprintf(stderr, "Invalid file name\n");
			exit(1);
		}
		
		for(int i = 0; i < num_integers; i++){
			randInt = rand() % (max_int + 1 - min_int) + min_int;
			fprintf(output_file, "%d\n", randInt);
		}
		fclose(output_file);
	}
	
	return 0;
	
}





























