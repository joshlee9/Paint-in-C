#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "paint.h"
// Canvas struct which includes a 2D array of char, total number of rows, and total number of columns
// Creates a canvas given arguments in command line
Canvas createCanvas(int argc, char** argv) {
	Canvas canvas;
	int totalRows; 
	int totalColumns;
	
	char should_be_blank;
	char should_be_blank1;
	char blank_char = '*';
	
	if (argc == 1) {
		totalRows = 10;
		totalColumns = 10;
	}
	if (argc == 3) {
		// totalRows = argv[1];
		sscanf(argv[1], "%d %c", &totalRows, &should_be_blank);
		// totalColumns = argv[2];
		sscanf(argv[2], "%d %c", &totalColumns, &should_be_blank1);
	}
	
	canvas.totalRows = totalRows; 
	canvas.totalColumns = totalColumns;

	canvas.c = calloc(totalRows, sizeof(canvas.c));
		for (int i = 0; i < totalRows; ++i) {
			canvas.c[i] = calloc(totalColumns, sizeof(canvas.c[i]));
			for(int j = 0; j < totalColumns; ++j) {
				canvas.c[i][j] = blank_char;
			}
		}
		return canvas;
}
// Displays canvas in printed form 
void displayCanvas(Canvas canvas) {
	for(int i = 0; i < canvas.totalRows; ++i) {
		printf("%-d  ", canvas.totalRows - i - 1); //row header
		for(int j = 0; j < canvas.totalColumns; ++j) {
			printf("%c  ", canvas.c[i][j]);
		}
		printf("\n");
	}
	//column headers
	printf("   ");
	for(int i = 0; i < canvas.totalColumns; ++i){
		printf("%-d  ", i);
	}
	printf("\n");
}
// Frees all the 2D array of canvas
void freeCanvas(Canvas canvas) {
	for(int i = 0; i < canvas.totalRows; i++) {
	    free(canvas.c[i]);  // Free individual cells 
	}
	free(canvas.c);  // Free canvas
}
// Quits the program by freeing memory and exiting 
void quit(Canvas canvas) {
	freeCanvas(canvas);
	exit(0);
}

// print_help taken from given.c starter code. 
void print_help() {
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

void write(Canvas canvas, int row1, int col1, int row2, int col2) {
	// Check to ensure not out of bounds
	if ((row1 > canvas.totalRows) || (row2 > canvas.totalRows) || (col1 > canvas.totalColumns) || (col2 > canvas.totalColumns)) {
		printf("Cannot draw the line as it is not straight.\n");
		displayCanvas(canvas);
		return;
	}
	// is it a single point, horizontal, vertical, diagonal left or diagonal right?
	// is it a single point?
	if ((row1 == row2) && (col1 == col2)) {
		if ((canvas.c[canvas.totalRows - row1 - 1][col1] == '-') || (canvas.c[canvas.totalRows - row1 - 1][col1] == '*')) {
			canvas.c[canvas.totalRows - row1 - 1][col1] = '-';
		} else {
			canvas.c[canvas.totalRows - row1 - 1][col1] = '+';
		}
		displayCanvas(canvas);
		return;
	}
	// is horizontal? if row1 == row2
	else if (row1 == row2) {
		for (int i = 0; i < abs(col2 - col1) + 1; i++) {
			if ((canvas.c[canvas.totalRows - row1 - 1][i + (int) fmin(col1, col2)] == '-') || ((canvas.c[canvas.totalRows - row1 - 1][i + (int) fmin(col1, col2)] == '*'))) {
				canvas.c[canvas.totalRows - row1 - 1][i + (int) fmin(col1, col2)] = '-';
			} else {
				canvas.c[canvas.totalRows - row1 - 1][i + (int) fmin(col1, col2)] = '+';
			}
			// input '-' into canvas.c[]
		}
	}
	// is vertical? if col1 == col2
	else if (col1 == col2) {
		for (int i = 0; i < abs(row2 - row1) + 1; i++) {
			if ((canvas.c[canvas.totalRows - ((int) fmin(row1, row2) + i) - 1][col1] == '|') || (canvas.c[canvas.totalRows - ((int) fmin(row1, row2) + i) - 1][col1] == '*')) {
				canvas.c[canvas.totalRows - ((int) fmin(row1, row2) + i) - 1][col1] = '|';
			} else {
				canvas.c[canvas.totalRows - ((int) fmin(row1, row2) + i) - 1][col1] = '+';
			}
		}
	}
	// is diagonal left? if (col2 - col1)/(row2 - row1) == 1
	else if (((double)(col2 - col1)/(double)(row2 - row1)) == 1) {
		// starting at the bottom left corner, either canvas.c[row1 + i][col1+ i] or canvas.c[row2 + i][col2 + i] depending on which one is bottom left. so first determine which is bottom left
		for (int i = 0; i < abs(row1 - row2) + 1; i++) {
			if (col1 < col2) {
				// in this case col1 is the bottom left corner
				if ((canvas.c[canvas.totalRows - (row1 + i) - 1][col1 + i] == '/') || (canvas.c[canvas.totalRows - (row1 + i) - 1][col1 + i] == '*')) {
					canvas.c[canvas.totalRows - (row1 + i) - 1][col1 + i] = '/';
				} else {
					canvas.c[canvas.totalRows - (row1 + i) - 1][col1 + i] = '+';
				}
				
			}
			if (col1 > col2) {
				// in this case col2 is the bottom left corner
				if ((canvas.c[canvas.totalRows - (row2 + i) - 1][col2 + i] == '/') || (canvas.c[canvas.totalRows - (row2 + i) - 1][col2 + i] == '*')) {
					canvas.c[canvas.totalRows - (row2 + i) - 1][col2 + i] = '/';
				} else {
					canvas.c[canvas.totalRows - (row2 + i) - 1][col2 + i] = '+';
				}
				
			}
		}
	}
	// is diagonal right? if (col2 - col1)/(row2 - row1) == -1
	else if (((double)(col2 - col1)/(double)(row2 - row1)) == -1) {
		//starting at bottom right corner, either canvas.c[row1 + i][col1 - i] or canvas.c[row2 + i][col2 + i]
		for (int i = 0; i < abs(row1 - row2) + 1; i++) {
			if (col1 > col2) {
				// in this case col1 is in the bottom right corner
				if ((canvas.c[canvas.totalRows - (row1 + i) - 1][col1 - i] == '\\') || (canvas.c[canvas.totalRows - (row1 + i) - 1][col1 - i] == '*')) {
				canvas.c[canvas.totalRows - row1 - i - 1][col1 - i] = '\\';
				} else {
				canvas.c[canvas.totalRows - row1 - i - 1][col1 - i] = '+';
				}
			}
			if (col1 < col2) {
				// in this case col2 is in the bottom right corner
				if ((canvas.c[canvas.totalRows - row2 - i - 1][col2 - i] == '\\') || (canvas.c[canvas.totalRows - row2 - i - 1][col2 - i] == '*')) {
					canvas.c[canvas.totalRows - row2 - i - 1][col2 - i] = '\\';
				} else {
					canvas.c[canvas.totalRows - row2 - i - 1][col2 - i] = '+';
				}
			}
		}
	}
	else {
		printf("Improper draw command.\n");
		displayCanvas(canvas);
		return;
	}
	displayCanvas(canvas);
}
// Erase a cell at (row, col)
void erase(Canvas canvas, int rowToErase, int columnToErase) {
	canvas.c[canvas.totalRows - rowToErase - 1][columnToErase] = '*';
	displayCanvas(canvas);
}
// Returns a new identical canvas after adding a row or column
Canvas add(Canvas canvas, char rowOrColumn, int dimToInsert) {
	char blank_char = '*';
	Canvas newCanvas; 
	newCanvas = canvas;
	
	if ((rowOrColumn == 'r') || (rowOrColumn == 'c')) {
		if (rowOrColumn == 'r') {
			// If row, create new canvas with size of old canvas and new row 
			newCanvas.totalRows = canvas.totalRows + 1;
			newCanvas.c = calloc(newCanvas.totalRows, sizeof(newCanvas.c));
			for (int i = 0; i < newCanvas.totalRows; ++i) {
				newCanvas.c[i] = calloc(newCanvas.totalColumns, sizeof(newCanvas.c[i]));
				for(int j = 0; j < newCanvas.totalColumns; ++j) {
					newCanvas.c[i][j] = blank_char;
				}
			}
			int skippedRow = 0;
			// For each row and column in old canvas, copy it to new canvas cell by cell
			for (int i = canvas.totalRows; i > 0; i--) {
				for (int j = 0; j < canvas.totalColumns; j++) {
					if (i == (newCanvas.totalRows - 1 - dimToInsert)) {
						// If the row is the one selected to be inserted at then push every row above this upward
						skippedRow = 1;
						newCanvas.c[i - skippedRow][j] = canvas.c[i - 1][j];
					} else {
						newCanvas.c[i - skippedRow][j] = canvas.c[i - 1][j];
					}
				}
			}
		}
		
		if (rowOrColumn == 'c') {
			// If column, create new canvas with size of old canvas and new row 
			newCanvas.totalColumns = canvas.totalColumns + 1;
			newCanvas.c = calloc(newCanvas.totalRows, sizeof(newCanvas.c));
			for (int i = 0; i < newCanvas.totalRows; ++i) {
				newCanvas.c[i] = calloc(newCanvas.totalColumns, sizeof(newCanvas.c[i]));
				for(int j = 0; j < newCanvas.totalColumns; ++j) {
					newCanvas.c[i][j] = blank_char;
				}
			}
			
			int skippedColumn = 0 ;
			// For each row and column in old canvas, copy it to new canvas cell by cell
			for (int j = canvas.totalColumns; j > 0; j--) {
				 for (int i = 0; i < canvas.totalRows; i++) {
					if (j == dimToInsert) {
						// If the column is the one selected to be inserted at then push every column to the right
						skippedColumn = 1;
						newCanvas.c[i][j - skippedColumn] = canvas.c[i][j - 1];
					} else {
						newCanvas.c[i][j - skippedColumn] = canvas.c[i][j - 1];
					}
				}
			}
			
		}
	} else {
		printf("Improper add command.\n");
		displayCanvas(canvas);
	}
	return newCanvas;
}
// Returns a new identical canvas after deleting a row or column
Canvas deleteDim(Canvas canvas, char rowOrColumn, int dimToDelete) {
	char blank_char = '*';
	Canvas newCanvas; 
	newCanvas = canvas;
	
	if ((rowOrColumn == 'r') || (rowOrColumn == 'c')) {
		if (rowOrColumn == 'r') {
			// If row, create new canvas with size of old canvas and new row 
			newCanvas.totalRows = canvas.totalRows - 1;
			newCanvas.c = calloc(newCanvas.totalRows, sizeof(newCanvas.c));
			for (int i = 0; i < newCanvas.totalRows; ++i) {
				newCanvas.c[i] = calloc(newCanvas.totalColumns, sizeof(newCanvas.c[i]));
				for(int j = 0; j < newCanvas.totalColumns; ++j) {
					newCanvas.c[i][j] = blank_char;
				}
			}
			// For each row and column in old canvas, copy it except the deleted row	
			int skippedRow = 0;
			for (int i = 0; i < canvas.totalRows; i++) {
				for (int j = 0; j < canvas.totalColumns; j++) {
					if (i == (canvas.totalRows - 1 - dimToDelete)) {
						// If the row is the one selected to be inserted at then push every row above this upward
						skippedRow = 1;
					} else {
						newCanvas.c[i - skippedRow][j] = canvas.c[i][j];
					}
				}
			}
			
		}
		if (rowOrColumn == 'c') {
			// If column, create new canvas with size of old canvas and new row 
			newCanvas.totalColumns = canvas.totalColumns - 1;
			newCanvas.c = calloc(newCanvas.totalRows, sizeof(newCanvas.c));
			for (int i = 0; i < newCanvas.totalRows; ++i) {
				newCanvas.c[i] = calloc(newCanvas.totalColumns, sizeof(newCanvas.c[i]));
				for(int j = 0; j < newCanvas.totalColumns; ++j) {
					newCanvas.c[i][j] = blank_char;
				}
			}
			
			int skippedColumn = 0 ;
			// For each row and column in old canvas, copy it to new canvas cell by cell
			for (int j = 0; j < canvas.totalColumns; j++) {
				for (int i = 0; i < canvas.totalRows; i++) {
					if (j == dimToDelete) {
						// If the row is the one selected to be inserted at then push every row above this upward
						skippedColumn = 1;
					} else {
						newCanvas.c[i][j - skippedColumn] = canvas.c[i][j];
					}
				}
			}
		}
	} else {
		printf("Improper delete command.\n");
		displayCanvas(canvas);
	}
	return newCanvas;
}
// Resize the canvas to any (row, column)
Canvas resize(Canvas canvas, int resizedRow, int resizedColumn) {
	char blank_char = '*';
	// Remember to set canvas.totalRows and canvas.totalColumns to new number of rows and columns.
	Canvas newCanvas; 
	newCanvas.totalRows = resizedRow;
	newCanvas.totalColumns = resizedColumn;
	int canvasRow = canvas.totalRows;
	int canvasColumn  = canvas.totalColumns;
	newCanvas.c = calloc(resizedRow, sizeof(newCanvas.c));
		for (int i = 0; i < resizedRow; ++i) {
			newCanvas.c[i] = calloc(resizedColumn, sizeof(newCanvas.c[i]));
			for(int j = 0; j < resizedColumn; ++j) {
				newCanvas.c[i][j] = blank_char;
			}
		}
		if ((newCanvas.totalRows >= canvas.totalRows) && (newCanvas.totalColumns >= canvas.totalColumns)) {
			// For each row and column in old canvas, copy it to new canvas cell by cell
			for (int i = canvas.totalRows - 1; i >= 0; i--) {
				for (int j = 0; j < canvas.totalColumns; j++) {
					newCanvas.c[i + (newCanvas.totalRows - canvas.totalRows)][j] = canvas.c[i][j];
				}
			}
		}
		else if ((newCanvas.totalRows < canvas.totalRows) && (newCanvas.totalColumns < canvas.totalColumns)) {
			for (int i = newCanvas.totalRows - 1; i >= 0; i--) {
				for (int j = 0; j < newCanvas.totalColumns; j++) {
					newCanvas.c[i][j] = canvas.c[i + (canvas.totalRows - newCanvas.totalRows)][j];
				}
			}
		}
		// IF new canvas has more rows and less column
		else if ((resizedRow >= canvasRow) && (resizedColumn < canvasColumn)) {
			// For each row we want to add, run the add row command to adjust the canvas and set it = to the newCanvas
			for (int i = 0; i < (resizedRow - canvasRow); i++) {
				// For each less row in the newCanvas, delete from the end of the column
				newCanvas = add(canvas, 'r', canvasRow + i);
				canvas = newCanvas;
			}
			for (int j = 0; j < (canvasColumn - resizedColumn); j++) {
				newCanvas = deleteDim(newCanvas, 'c', canvasColumn - 1 - j);
			}
		}
		// If new canvas has less rows and more column
		else if ((resizedRow < canvasRow) && (resizedColumn >= canvasColumn)) {
			for (int i = 0; i < (canvasRow - resizedRow); i++) {
				// For each less row in the newCanvas, delete from the end of the column
				newCanvas = deleteDim(canvas, 'r', canvasRow - 1 - i);
				canvas = newCanvas;
			}
			for (int j = 0; j < (resizedColumn - canvasColumn); j++) {
				newCanvas = add(canvas, 'c', canvasColumn + j);
				canvas = newCanvas;

			}
		}
	return newCanvas;
}
// Saves the canvas to a file with the name specified
void save(Canvas canvas, char *fileName) {
	FILE *file = fopen(fileName, "w");
	// Input validation:
	if (file == NULL) {
		printf("Failed to open file: %s\n", fileName);
		displayCanvas(canvas);
		return;
	}
	fprintf(file, "%d ", canvas.totalRows);
	fprintf(file, "%d ", canvas.totalColumns);
	for (int i = 0; i < canvas.totalRows; i++) {
		for (int j = 0; j < canvas.totalColumns; j++) {
			fprintf(file, "%c", canvas.c[i][j]);
		}
	}
	fclose(file);
}
// Loads a saved file of the canvas and displays it
Canvas load(Canvas canvas, char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Failed to open file: %s\n", fileName);
		return canvas;
	}
	char c;
	char blank_char = '*';
	Canvas newCanvas;
	int totalRows;
	int totalColumns;
	fscanf(file, "%d ", &totalRows);
	fscanf(file, "%d ", &totalColumns);
	newCanvas.totalRows = totalRows;
	newCanvas.totalColumns = totalColumns;
	newCanvas.c = calloc(newCanvas.totalRows, sizeof(newCanvas.c));
	for (int i = 0; i < newCanvas.totalRows; ++i) {
		newCanvas.c[i] = calloc(newCanvas.totalColumns, sizeof(newCanvas.c[i]));
		for(int j = 0; j < newCanvas.totalColumns; ++j) {
			newCanvas.c[i][j] = blank_char;
		}
	}
	for (int i = 0; i < newCanvas.totalRows; i++) {
		for (int j = 0; j < newCanvas.totalColumns; j++) {
			fscanf(file, "%c", &c);
			newCanvas.c[i][j] = c;
		}
	}
	fclose(file);
	return newCanvas;
}
// Run the paint program and continually ask user for next command until the quit command is issued
void runPaint(Canvas canvas) {
	bool stopProgram = false; 
	char commandLetter;
	while(stopProgram == false) {
		printf("Enter your command: ");
		
		char* str = malloc(sizeof(char));  // free this at the end
	    size_t len = sizeof(char);
	    getline(&str, &len, stdin);
	    
	    // Now we have string stored in str. 
	    sscanf(str, "%c", &commandLetter);
	    
		// Get character of command
		if (commandLetter == 'q') {
			if (strlen(str) == 2) {
				free(str);
				quit(canvas);
			} else {
				printf("Unrecognized command. Type h for help.\n");
				displayCanvas(canvas);
			}
		}
		else if (commandLetter == 'h') {
			if (strlen(str) == 2) {
				print_help();
				displayCanvas(canvas);
			} else {
				printf("Unrecognized command. Type h for help.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		// Depending on the letter, we run different commands
		else if (commandLetter == 'w') {
			char wchar;
			int row1;
			int col1; 
			int row2;
			int col2;
			char should_be_empty;
			
			int numArgs = sscanf(str, "%c %d %d %d %d %c", &wchar, &row1, &col1, &row2, &col2, &should_be_empty);
			
			if ((numArgs == 5) && (row1 >= 0) && (col1 >= 0) && (row2 >= 0) && (col2 >= 0) && (row1 <= canvas.totalRows - 1) && (row2 <= canvas.totalRows - 1) && (col1 <= canvas.totalColumns - 1) && (col2 <= canvas.totalColumns - 1)) {
				write(canvas, row1, col1, row2, col2);
			} else {
				printf("Improper draw command.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		else if (commandLetter == 'e') {
			char echar;
			int rowToErase;
			int columnToErase;
			char should_be_empty;
			int numArgs = sscanf(str, "%c %d %d %c", &echar, &rowToErase, &columnToErase, &should_be_empty);
			if ((numArgs == 3) && (rowToErase >= 0) && (columnToErase >= 0) && (rowToErase <= canvas.totalRows - 1) && (columnToErase <= canvas.totalColumns - 1)) {
				erase(canvas, rowToErase, columnToErase);
			} else {
				printf("Improper erase command.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		else if (commandLetter == 'r') {
			char rchar;
			int resizedRow;
			int resizedColumn;
			char should_be_empty;
			int numArgs = sscanf(str, "%c %d %d %c", &rchar, &resizedRow, &resizedColumn, &should_be_empty);
			if ((numArgs == 3) && (resizedRow >= 1) && (resizedColumn >= 1)) {
				canvas = resize(canvas, resizedRow, resizedColumn);
				displayCanvas(canvas);
			} else {
				printf("Improper resize command.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		else if (commandLetter == 'a') {
			char achar;
			char rowOrColumn;
			int dimToInsert;
			char should_be_empty;
			int numArgs = sscanf(str, "%c %c %d %c", &achar, &rowOrColumn, &dimToInsert, &should_be_empty);
			if (numArgs == 3) {
				if ((rowOrColumn == 'r') && (dimToInsert >= 0) && (dimToInsert <= canvas.totalRows)) {
					canvas = add(canvas, rowOrColumn, dimToInsert);
					displayCanvas(canvas);
				}
				else if ((rowOrColumn == 'c') && (dimToInsert >= 0) && (dimToInsert <= canvas.totalColumns)) {
					canvas = add(canvas, rowOrColumn, dimToInsert);
					displayCanvas(canvas);
				} else {
					printf("Improper add command.\n");
					displayCanvas(canvas);
				}
			} else {
				printf("Improper add command.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		else if (commandLetter == 'd') {
			char dchar;
			char rowOrColumn;
			int dimToDelete;
			char should_be_empty;
			int numArgs = sscanf(str, "%c %c %d %c", &dchar, &rowOrColumn, &dimToDelete, &should_be_empty);
			if (numArgs == 3) {
				if ((rowOrColumn == 'r') && (dimToDelete >= 0) && (dimToDelete <= canvas.totalRows - 1)) {
					canvas = deleteDim(canvas, rowOrColumn, dimToDelete);
					displayCanvas(canvas);
				}
				else if ((rowOrColumn == 'c') && (dimToDelete >= 0) && (dimToDelete <= canvas.totalColumns - 1)) {
					canvas = deleteDim(canvas, rowOrColumn, dimToDelete);
					displayCanvas(canvas);
				} else {
					printf("Improper delete command.\n");
					displayCanvas(canvas);
				}
			} else {
				printf("Improper delete command.\n");
				displayCanvas(canvas);
			}
			free(str);
		}
		else if (commandLetter == 's') {
			char schar;
			char* fileName;
			char should_be_empty;
			fileName = malloc(sizeof(char));
			int numArgs = sscanf(str, "%c %s %c", &schar, fileName, &should_be_empty);
			if (numArgs == 2) {
				  // free this at the end
				save(canvas, fileName);
				
				displayCanvas(canvas);
			} else {
				printf("Improper save command or file could not be created.\n");
				displayCanvas(canvas);
			}
			free(fileName);
			free(str);
		}
		else if (commandLetter == 'l') {
			char lchar;
			char *fileName;
			char should_be_empty;
			fileName = malloc(sizeof(char));
			int numArgs = sscanf(str, "%c %s %c", &lchar, fileName, &should_be_empty);
			if (numArgs == 2) {
				canvas = load(canvas, fileName);
				displayCanvas(canvas);
			} else {
				printf("Improper load command or file could not be opened.\n");
				displayCanvas(canvas);
			}
			free(fileName);
		} else {
			printf("Unrecognized command. Type h for help.\n");
			displayCanvas(canvas);
			free(str);
		}
	}
}
// Check command line arguments to ensure all is input correctly, if not set it to a 10x10 canvas
int checkArg(int argc, char** argv) {
	// If no args given
	if (argc == 1) {
		argv[1] = "10";
		argv[2] = "10";
		return 3;
	}
	// If number of rows is less than 1
	if (atoi(argv[1]) <= 0) {
		printf("The number of rows is less than 1.\n");
		printf("Making default board of 10 X 10.\n");
		argv[1] = "10";
		argv[2] = "10";
		return 3;
	}
	// If number of columns is less than 1
	if (atoi(argv[2]) <= 0) {
		printf("The number of columns is less than 1.\n");
		printf("Making default board of 10 X 10.\n");
		argv[1] = "10";
		argv[2] = "10";
		return 3;
	}
	// If number of columns is not an integer
	if (atoi(argv[2]) == 0) {
		printf("The number of columns is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
		argv[1] = "10";
		argv[2] = "10";
		return 3;
	}
	// If number of rows is not an integer
	if (atoi(argv[1]) == 0) {
		printf("The number of rows is not an integer.\n");
		printf("Making default board of 10 X 10.\n");
		argv[1] = "10";
		argv[2] = "10";
		return 3;
	}
	// If more or less than desired inputs are given
	if ((argc != 1) && (argc != 3)) {
		
		printf("Wrong number of command line arguements entered.\n");
		printf("Usage: ./paint.out [num_rows num_cols]\n");
		printf("Making default board of 10 X 10.\n");
		argv[1] = "10";
		argv[2] = "10";
		argc--;
	}
	return argc;
}
