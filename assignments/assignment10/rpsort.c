#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>


/* 
 * Represent a slot in the buffer, containing a record (integer >= 0, -1
 * represents empty slot), marked either "on" or "off".
 */
typedef enum {OFF=0, ON=1} state;
typedef struct {
    int record;
    state state;
} slot;

/* 
 * Allocate buffer with buffer_size. Initialize with record -1 (empty) and ON
 * state.
 */
slot* init_buffer(int buffer_size) {
  slot *buffer = (slot*) malloc(sizeof(slot) * buffer_size);
  
  for(int i = 0; i < buffer_size; ++i) {
    buffer[i].record = -1;
    buffer[i].state = ON;
  }
  
  return buffer;
}

/* 
 * Read the next record (integer) from input_seq file. At the end of input_seq,
 * if all records are read, -1 is returned instead.
 */
int read_next(FILE *input_seq) {
    assert(input_seq);

    int line_size = 32;
    char line[line_size];

    if (fgets(line, line_size, input_seq))
    {
        return atoi(line);
    }        
    return -1;
}

/* 
 * Create a new output_run file in the current directory on disc. Close the
 * current output_run.
 */
FILE* start_next_output_run(FILE* output_run) {
    if (output_run)
    {
        fclose(output_run);
    }
    char new_filename[16];
    static int run_count = 0;

    sprintf(new_filename, "out_%d.run", ++run_count);
    output_run = fopen(new_filename, "w");
    assert(output_run);

    return output_run;
}

/* Write a record (integer) to current output_run file on disc */
void write_output(int record, FILE *output_run) {
    fprintf(output_run, "%d\n", record);
}

/* Implementation of replacement sort ala Knuth, TAoCP, volume 3 */
void replacement_sort(slot *buffer, int buffer_size, FILE *input_seq, FILE *output_run) {
    /*** YOUR CODE HERE ***/
}

int main(int argc, char **args)
{ 
    /* input arguments */
    int buffer_size;
    char *input_file_name;

    FILE *input_seq;         /* pointer to input run file */
    FILE *output_run = NULL; /* pointer to current output run file */

    slot *buffer;   /* buffer with buffer_size slots */

    /* read input arguments, print usage information */
    if(argc != 3) 
    {
        printf(
            "USAGE:\trpsort <buffer size> <input file name>\n"
            "\n"
            "OPTIONS:\n"
            "<buffer size>\n"
            "\tThe buffer size is a positive integer greater 2.\n"
            "<input file>\n"
            "\tPath to the file holding the input. The sequence has to be\n"
            "\tin the form of a line break separated list. The pages (each\n"
            "\tcontaining exactly one integer value) are read line by line.\n"
            "\n"
            "OUTPUT:\n"
            "\tFiles containing the output runs are created in the current\n"
            "\tdirectory. Existing files are overwritten.\n"
            "\n"
        );
        return 0;
    }
    buffer_size = atoi(args[1]);
    input_file_name = args[2];

    /* prepare buffer */
    buffer = init_buffer(buffer_size);

    /* open input and initial output run */
    input_seq = fopen(input_file_name, "r");
    assert(input_seq);
    output_run = start_next_output_run(output_run);

    /* perform Pass 0, using replacement sort */
    replacement_sort(buffer, buffer_size, input_seq, output_run);

    return 0;
}



