#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include "flandmark/data/cpp/flandmark_detector.h"
#include "detect_and_draw.cpp"



void detect_and_draw( IplImage* image, double scale, CvMemStorage* storage,
                    CvHaarClassifierCascade* cascade, bool show );

const char* cascade_name =
    "haarcascade_frontalface_alt.xml";

int main(int argc, char const *argv[])
{
    IplImage *frame, *frame_copy = 0;
    IplImage *image = 0;






    return 0;
}