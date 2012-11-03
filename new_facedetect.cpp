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



static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
static CvHaarClassifierCascade* nested_cascade = 0;
int use_nested_cascade = 0;

void detect_and_draw( IplImage* image);

const char* cascade_name =
    "haarcascade_frontalface_alt.xml";
const char* nested_cascade_name =
    "haarcascade_eye_tree_eyeglasses.xml";

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
            detect_and_draw( frame );
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
            detect_and_draw( frame );
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
        detect_and_draw( image );
        cvWaitKey(0);
        cvReleaseImage( &image );
        cvDestroyWindow( "result" );
    } 

}







































void detect_and_draw( IplImage* img )
{
    static CvScalar colors[] = 
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    IplImage *gray, *small_img, *copy;
    FLANDMARK_Model *model = flandmark_init("flandmark_model.dat");
    float *landmarks = (float*) malloc(2 * model->data.options.M * sizeof(float));
    int *bbox = (int*) malloc(4 * sizeof(int));
    IplImage** faces_themselves = (IplImage**) malloc(10 * sizeof(IplImage*));
    int i, j;
    bool flag = false;
    int num_detected = 0;
    gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)), 8, 1 );

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );

    if( cascade )
    {
        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0
                                            //|CV_HAAR_FIND_BIGGEST_OBJECT
                                            //|CV_HAAR_DO_ROUGH_SEARCH
                                            |CV_HAAR_DO_CANNY_PRUNING
                                            //|CV_HAAR_SCALE_IMAGE
                                            ,
                                            cvSize(30, 30) );
        t = (double)cvGetTickCount() - t;
        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {

            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvMat small_img_roi;
            CvSeq* nested_objects;
            CvPoint center;
            CvScalar color = colors[i%8];
               
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);


            if ( (r -> height) && (r -> width) )
            {   
                flag = true;
                num_detected = i + 1;
                cvSetImageROI(img, cvRect( center.x - radius,
                                         center.y - radius,
                                         2 * radius,
                                         2 * radius));
                faces_themselves[i] = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
                cvCopy(img, faces_themselves[i], NULL);
                cvResetImageROI(img);


                

                printf("%d %d %d %d\n", center.x - radius, center.y - radius,
                                        center.x + radius, center.y + radius);
                bbox[0] = center.x - radius;
                bbox[1] = center.y - radius;
                bbox[2] = center.x + radius;
                bbox[3] = center.y + radius;

                t = (double)cvGetTickCount();
                if( flandmark_detect(gray, bbox, model, landmarks) )
                {
                    fprintf( stderr, "Error during detection of face features\n" );
                    exit(-1);
                }
                t = (double)cvGetTickCount() - t;
                printf( "face features' detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
                cvCircle(img, cvPoint((int)landmarks[0], (int)landmarks[1]), 3, CV_RGB(0, 0,255), CV_FILLED);
                for (int ii = 2; ii < 2 * model->data.options.M; ii += 2)
                {
                    cvCircle(img, cvPoint(int(landmarks[ii]), int(landmarks[ii+1])), 3, CV_RGB(255,0,0), CV_FILLED);
                }
                
            }


            cvCircle( img, center, radius, color, 3, 8, 0 );
        }
    }

    cvShowImage( "result", img );
    if(flag)
    {
        for (i = 0; i < num_detected; i++)
        {
            char win_name[256]; 
            sprintf(win_name, "face_%d", i);
            cvNamedWindow( win_name, CV_WINDOW_AUTOSIZE );
            cvShowImage( win_name, faces_themselves[i] );
        }
    }

    for (i = 0; i < num_detected; i++)
    {
        char win_name[256]; 
        sprintf(win_name, "face_%d", i);
        cvDestroyWindow("win_name");
    }

    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
    free(landmarks);
    free(bbox);
    flandmark_free(model);
}
