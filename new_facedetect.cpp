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



static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
static CvHaarClassifierCascade* nested_cascade = 0;
int use_nested_cascade = 0;

void detect_and_draw( IplImage* image, double scale, CvMemStorage* storage, CvHaarClassifierCascade* cascade );

const char* cascade_name =
    "haarcascade_frontalface_alt.xml";

double scale = 1;

int        g_slider_position = 0;
CvCapture* g_capture         = NULL;

void onTrackbarSlide(int pos) {
    cvSetCaptureProperty(
        g_capture,
        CV_CAP_PROP_POS_FRAMES,
        pos
    );
}

int main( int argc, char** argv ) {

    CvCapture* capture = NULL;
    IplImage *frame, *frame_copy = 0;
    IplImage *image = 0;
    const char* scale_opt = "--scale=";
    int scale_opt_len = (int)strlen(scale_opt);
    int i;
    const char* input_name = 0;

    for( i = 1; i < argc; i++ )
    {
        if( strncmp( argv[i], scale_opt, scale_opt_len ) == 0 )
        {
            if( !sscanf( argv[i] + scale_opt_len, "%lf", &scale ) || scale < 1 )
                scale = 1;
        }
        else if( argv[i][0] == '-' )
        {
            fprintf( stderr, "WARNING: Unknown option %s\n", argv[i] );
        }
        else
            input_name = argv[i];
    }

    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        fprintf( stderr,
        "Usage: facedetect [--cascade=\"<cascade_path>\"]\n"
        "   [--scale[=<image scale>\n"
        "   [filename|camera_index]\n" );
        return -1;
    }
    storage = cvCreateMemStorage(0);
    
    if( !input_name || (isdigit(input_name[0]) && input_name[1] == '\0') )
        capture = cvCaptureFromCAM( !input_name ? 0 : input_name[0] - '0' );
    else if( input_name )
    {
        image = cvLoadImage( input_name, 1 );
        if( !image )
            g_capture = cvCreateFileCapture( input_name );
    }
    else
        image = cvLoadImage( "test.jpg", 1 );

    cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );

























    if (g_capture)
    {
        IplImage *foo = cvQueryFrame( g_capture);


        int frames = (int) cvGetCaptureProperty(
            g_capture,
            CV_CAP_PROP_FRAME_COUNT
        );

        cvCreateTrackbar(
            "Position",
            "result",
            &g_slider_position,
            frames,
            onTrackbarSlide
        );
        frames = 0;
        while(1) {
            frame = cvQueryFrame( g_capture );
            if( !frame ) break;
            int frames = cvGetCaptureProperty( g_capture, CV_CAP_PROP_POS_FRAMES);
            cvSetTrackbarPos("Position","result",frames);
            // cvShowImage( "result", frame );
            detect_and_draw( frame, scale, storage, cascade );
            char c = (char)cvWaitKey(10);
            if( c == 112 )
            {
                while (1)
                {
                    char pause = (char)cvWaitKey(10);
                    if (pause == 112) break;
                }
            }
        }
        cvReleaseCapture( &g_capture );
        cvDestroyWindow( "result" );
        return(0);
    }

    else if (capture)
    {
        while(1) {
            frame = cvQueryFrame( capture );
            if( !frame ) break;
            // cvShowImage( "result", frame );
            detect_and_draw( frame, scale, storage, cascade );
            char c = (char)cvWaitKey(10);
            if( c == 112 )
            {
                while (1)
                {
                    char pause = (char)cvWaitKey(10);
                    if (pause == 112) break;
                }
            }
        }
        cvReleaseCapture( &capture );
        cvDestroyWindow( "result" );  
    }

    else if (image)
    {
        detect_and_draw( image, scale, storage, cascade );
        cvWaitKey(0);
        cvReleaseImage( &image );
        cvDestroyWindow( "result" );
    } 

}
