#ifndef PAINT_H
#define PAINT_H

	typedef struct Canvas_struct {
        char** c; 
        int totalRows;
        int totalColumns;
    } Canvas;
    Canvas createCanvas(int argc, char** argv);
    void displayCanvas(Canvas canvas);
    void freeCanvas(Canvas canvas);
    void quit(Canvas canvas);
    void print_help();
    void write(Canvas canvas, int row1, int col1, int row2, int col2);
    void erase(Canvas canvas, int rowToErase, int columnToErase);
    Canvas add(Canvas canvas, char rowOrColumn, int dimToInsert);
    Canvas deleteDim(Canvas canvas, char rowOrColumn, int dimToDelete);
    Canvas resize(Canvas canvas, int resizedRow, int resizedColumn);
    void save(Canvas canvas, char *fileName);
    Canvas load(Canvas canvas, char *fileName);
    void runPaint(Canvas canvas);
    int checkArg(int argc, char** argv);

#endif
