#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "paint.h"

int main(int argc, char** argv) {
	argc = checkArg(argc, argv);
    Canvas canvas = createCanvas(argc, argv);
    displayCanvas(canvas);
    runPaint(canvas);
    return 0;
}