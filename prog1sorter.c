#include <stdio.h>
#include <stdlib.h>
#include "parsers.h"
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

int comparator(const void *x, const void *y){
	int* l = (int*)x;
	int* r = (int*)y;
	return *(l) - *(r);
}

int main(int argc, char** argv){
	
	
	//-n
	int num_integers = 100;

	//-m
	int min_int = 1;

	//-M
	int max_int = 255;

	//-s
	unsigned long temp1 = 1;

	//-o set to false by default
	int isDashO = 0;
	char* output_file_name = NULL;
	FILE* output_file;
	
	//-i set to false by default
	int isDashI = 0;
	char* input_file_name = NULL;
	FILE* input_file;
	
	//-c set to false by default
	int isDashC = 0;
	char* count_file_name = NULL;
	FILE* count_file;
	
	//time variables
	struct timeval startTime, finishTime;
	double total_time;
	
	int num_to_sort;
	int curr_int;
	
	//allocating memory
	int* ints_to_sort;
	ints_to_sort = (int *) malloc (num_integers * sizeof(int));
	// check return value
	if(ints_to_sort == NULL){
		fprintf(stderr, "Could not allocate memory\n");
		exit(1);
	}
	
	
	inputParser("prog1sorter", argc, argv, &num_integers, &min_int, &max_int, &temp1, &isDashO, &output_file_name, "un:m:M:i:o:c:", &isDashI, &input_file_name, &isDashC, &count_file_name);
	
	//start timing after parsing
	gettimeofday(&startTime, NULL);
	
	
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
	
	
	
	//take input from file or from terminal
	int validInputs = 0;
	
	if(isDashI != 1){
		//get the first integer from terminal
		scanf("%d", &num_to_sort);
		if(num_to_sort < 0){
			fprintf(stderr, "Number of integers to sort cannot be negative\n");
			exit(1);
		}
		if(num_to_sort > num_integers){
			fprintf(stderr, "Number of integers to sort according to input is greater than specified by -n\n");
			exit(1);
		} else if(num_to_sort < num_integers){
			fprintf(stderr, "Number of integers to sort according to input is less than specified by -n\n");
			exit(1);
		} else{
			for(int i=0; i < num_integers; i++){
				if(!feof(stdin)){
					scanf("%d", &curr_int);
					if(curr_int > max_int){
						fprintf(stderr, "Integer %d is greater than 255\n", curr_int);
						exit(1);
					} else if(curr_int < min_int){
						fprintf(stderr, "Integer %d is less than 1\n", curr_int);
						exit(1);
					} else{
						//add current number to array if it is valid
						ints_to_sort[i] = curr_int;
						validInputs = i;
					}
				}
			}
		}
	
	} else{
		input_file = fopen(input_file_name, "r");
		if(input_file != NULL){
			//char = fgetc(input_file);
			//while(ch != EOF)
			
			fscanf(input_file, "%d\n", &num_to_sort);
			if(num_to_sort < 0){
				fprintf(stderr, "Number of integers to sort cannot be negative\n");
				exit(1);
			}
			if(num_to_sort > num_integers){
				fprintf(stderr, "Number of integers to sort according to input is greater than specified by -n\n");
				exit(1);
			} else if(num_to_sort < num_integers){
				fprintf(stderr, "Number of integers to sort according to input is less than specified by -n\n");
				exit(1);
			} else{
				for(int i=0; i < num_integers; i++){
					//c = getc(input_file);
					if(!feof(input_file)){
						if(feof(input_file)){
							break;
						}
						fscanf(input_file,"%d\n", &curr_int);
						if(curr_int > max_int){
							fprintf(stderr, "Integer %d is greater than 255\n", curr_int);
							exit(1);
						} else if(curr_int < min_int){
							fprintf(stderr, "Integer %d is less than 1\n", curr_int);
							exit(1);
						} else{
							//add current number to array if it is valid
							ints_to_sort[i] = curr_int;
							validInputs = i;
						}
					}
				}
			}
			fclose(input_file);
		} else{
			fprintf(stderr, "Invalid file name\n");
			exit(1);
		}
	}
	
	
	//validInputs++;
	qsort((void*) ints_to_sort, validInputs, sizeof(int), comparator);
	//check o input
	if(isDashO != 1){
		printf("%d\n", num_integers);
		for(int i = 0; i < validInputs; i++){
			printf("%d\n", ints_to_sort[i]);
		}
	} else{
		//open output file and write to it, also 
		output_file = fopen(output_file_name, "w");
		//insert the number of integers being sorted as first line
		if(output_file != NULL){
			fprintf(output_file, "%d\n", num_integers);
		} else{
			fprintf(stderr, "Invalid file name\n");
			exit(1);
		}
		
		for(int i = 0; i < validInputs; i++){
			fprintf(output_file, "%d\n", ints_to_sort[i]);
		}
		fclose(output_file);
	}
	
	char* username = getenv("USER");
	
	//array to count how many of each letter there are
	int* asciiVals;
	asciiVals = (int *) malloc (strlen(username) * sizeof(int));
	// check return value
	if(asciiVals == NULL){
		fprintf(stderr, "Could not allocate memory\n");
		exit(1);
	}
	
	//initiate all counts to 0
	for(int i = 0; i < strlen(username); i++){
		asciiVals[i] = 0;
	}
	
	//loops to count
	for(int i = 0; i < validInputs; i++){
		for(int j = 0; j < strlen(username); j++){
			//if the current integer is equal to the ASCII valie of the current letter of username
			if(ints_to_sort[i] == ((int) username[j])){
				asciiVals[j]++;
			}
		}
	}
	
	if(isDashC != 1){
		for(int i = 0; i < strlen(username); i++){
			printf("%c %d %d\n", username[i], (int)username[i], asciiVals[i]);
			
		}
	} else{
		count_file = fopen(count_file_name, "w");
		if(count_file != NULL){
			for(int i = 0; i < strlen(username); i++){
				fprintf(count_file, "%c %d %d\n", username[i], (int)username[i], asciiVals[i]);
			
			}
		} else{
			fprintf(stderr, "Invalid file name\n");
			exit(1);
		}
	
	}
	
	//sleep(2);
	//stop timer after writing output
	gettimeofday(&finishTime, NULL);
	
	//computing the time elapsed and setting to milliseconds
	total_time = (finishTime.tv_sec - startTime.tv_sec);
	total_time += (finishTime.tv_usec - startTime.tv_usec) / 1000000.0;
	fprintf(stderr, "Total Elapsed Time: %.6f seconds.\n", total_time);
	
	free(ints_to_sort);
	free(asciiVals);
	
	return 0;
	
}



















