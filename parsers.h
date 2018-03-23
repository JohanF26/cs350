#ifndef PARSERS
#define PARSERS

#define MIN_NUM_INTS 0
#define MAX_NUM_INTS 1000000

#define MIN_MIN_INT 1
#define MAX_MAX_INT 1000000

int inputParser(char* curr_prog, int argc, char** argv, int* num_integers, int* min_int, int* max_int, unsigned long* seed, int* isDashO, char** output_file_name, char* arguments, int* isDashI, char** input_file_name, int* isDashC, char** count_file_name);

#endif
