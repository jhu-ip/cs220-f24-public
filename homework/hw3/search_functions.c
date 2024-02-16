// search_functions.c
// <STUDENT: ADD YOUR INFO HERE: name, JHED, etc.>
//
//


#include <stdio.h>
#include "search_functions.h"



/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */
int populate_grid(char grid[][MAX_SIZE], char filename_to_read_from[]){

  return -1; // replace this stub

}


/* 
 * <Replace this with your own useful comment.> 
 */
int find_right(char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  return -1; // replace this stub

}


/* 
 * <Replace this with your own useful comment.> 
 */
int find_left (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  return -1; // replace this stub

}


/* 
 * <Replace this with your own useful comment.> 
 */
int find_down (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  return -1; // replace this stub

}


/* 
 * <Replace this with your own useful comment.> 
 */
int find_up   (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  return -1; // replace this stub

}


/* 
 * <Replace this with your own useful comment.> 
 */
int find_all  (char grid[][MAX_SIZE], int n, char word[], FILE *write_to) {

  return -1; // replace this stub

} 


/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match. The definition of this function is provided 
 * for you.
 */
int file_eq(char lhs_name[], char rhs_name[]) {
  FILE* lhs = fopen(lhs_name, "r");
  FILE* rhs = fopen(rhs_name, "r");

  // don't compare if we can't open the files
  if (lhs == NULL || rhs == NULL) return 0;

  int match = 1;
  // read until both of the files are done or there is a mismatch
  while (!feof(lhs) || !feof(rhs)) {
	if (feof(lhs) ||                      // lhs done first
		feof(rhs) ||                  // rhs done first
		(fgetc(lhs) != fgetc(rhs))) { // chars don't match
	  match = 0;
	  break;
	}
  }
  fclose(lhs);
  fclose(rhs);
  return match;
}

