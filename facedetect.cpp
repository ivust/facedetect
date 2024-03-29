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
CvCapture* capture         = NULL;


void onTrackbarSlide(int pos) {
    cvSetCaptureProperty(
        capture,
        CV_CAP_PROP_POS_FRAMES,
        pos
    );
}



int main( int argc, char** argv )
{
    CvCapture* capture = 0;
    IplImage *frame, *frame_copy = 0;
    IplImage *image = 0;
    const char* scale_opt = "--scale=";
    int scale_opt_len = (int)strlen(scale_opt);
    const char* cascade_opt = "--cascade=";
    int cascade_opt_len = (int)strlen(cascade_opt);
    int i;
    const char* input_name = 0;

    for( i = 1; i < argc; i++ )
    {
        if( strncmp( argv[i], cascade_opt, cascade_opt_len) == 0 )
            cascade_name = argv[i] + cascade_opt_len;
        else if( strncmp( argv[i], scale_opt, scale_opt_len ) == 0 )
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
            capture = cvCaptureFromAVI( input_name );
    }
    else
        image = cvLoadImage( "test.jpg", 1 );

    cvNamedWindow( "result", 1 );

    if( capture )
    {

        int frames = (int) cvGetCaptureProperty(
            capture,
            CV_CAP_PROP_FRAME_COUNT
        );
        
        cvCreateTrackbar(
            "Position",
            "result",
            &g_slider_position,
            frames,
            onTrackbarSlide
        );


        while(1)
        {
            if( !cvGrabFrame( capture ))
                break;
            frame = cvRetrieveFrame( capture );
            if( !frame )
                break;
            if( !frame_copy )
                frame_copy = cvCreateImage( cvSize(frame->width,frame->height),
                                            IPL_DEPTH_8U, frame->nChannels );
            if( frame->origin == IPL_ORIGIN_TL )
                cvCopy( frame, frame_copy, 0 );
            else
                cvFlip( frame, frame_copy, 0 );

            frames = cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES);
            cvSetTrackbarPos("Position","result",frames);

            detect_and_draw( frame_copy );

            if( cvWaitKey( 10 ) >= 0 )
                goto _cleanup_;
        }

        cvWaitKey(0);
_cleanup_:
        cvReleaseImage( &frame_copy );
        cvReleaseCapture( &capture );
    }
    else
    {
        if( image )
        {
            detect_and_draw( image );
            cvWaitKey(0);
            cvReleaseImage( &image );
        }
        else if( input_name )
        {
            /* assume it is a text file containing the
               list of the image filenames to be processed - one per line */
            FILE* f = fopen( input_name, "rt" );
            if( f )
            {
                char buf[1000+1];
                while( fgets( buf, 1000, f ) )
                {
                    int len = (int)strlen(buf), c;
                    while( len > 0 && isspace(buf[len-1]) )
                        len--;
                    buf[len] = '\0';
                    printf( "file %s\n", buf ); 
                    image = cvLoadImage( buf, 1 );
                    if( image )
                    {
                        detect_and_draw( image );
                        c = cvWaitKey(0);
                        if( c == 27 || c == 'q' || c == 'Q' )
                            break;
                        cvReleaseImage( &image );
                    }
                }
                fclose(f);
            }
        }
    }
    
    cvDestroyWindow("result");

    return 0;
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
    // IplImage *face_itself;
    IplImage** faces_themselves = (IplImage**) malloc(10 * sizeof(IplImage*));
    int i, j;
    bool flag = false;
    int num_detected;
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

            // if ( (r -> height) && (r -> width) )
            // {   
            //     flag = true;
            //     cvSetImageROI(img, cvRect(r->x, r->y, (r->x + r->width) * scale, (r->y + r->height) * scale));
            //     face_itself = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
            //     cvCopy(img, face_itself, NULL);
            //     cvResetImageROI(img);
            // }
                
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);


            if ( (r -> height) && (r -> width) )
            {   
                flag = true;
                num_detected = i + 1;
                // cvSetImageROI(img, cvRect(r->x, r->y, (r->x + r->width) * scale, (r->y + r->height) * scale));
                cvSetImageROI(img,
                             cvRect( center.x - radius,
                                     center.y - radius,
                                     2 * radius,
                                     2 * radius));
                faces_themselves[i] = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
                cvCopy(img, faces_themselves[i], NULL);
                cvResetImageROI(img);
            }


            cvCircle( img, center, radius, color, 3, 8, 0 );


            if( !nested_cascade )
                continue;
            cvGetSubRect( small_img, &small_img_roi, *r );
            nested_objects = cvHaarDetectObjects( &small_img_roi, nested_cascade, storage,
                                        1.1, 2, 0
                                        //|CV_HAAR_FIND_BIGGEST_OBJECT
                                        //|CV_HAAR_DO_ROUGH_SEARCH
                                        //|CV_HAAR_DO_CANNY_PRUNING
                                        //|CV_HAAR_SCALE_IMAGE
                                        ,
                                        cvSize(0, 0) );
            for( j = 0; j < (nested_objects ? nested_objects->total : 0); j++ )
            {
                CvRect* nr = (CvRect*)cvGetSeqElem( nested_objects, j );
                center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
                center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
                radius = cvRound((nr->width + nr->height)*0.25*scale);
                cvCircle( img, center, radius, color, 3, 8, 0 );
            }
        }
    }

    cvShowImage( "result", img );
    // if(flag) cvShowImage( "face", face_itself );
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

    // if(flag)
    // {
    //     cvNamedWindow( "face", CV_WINDOW_AUTOSIZE );
    //     cvShowImage( "face", faces_themselves[0] );
    // }

    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
    // cvReleaseImage( &face_itself );
}
