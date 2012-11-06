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
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lambda/bind.hpp>
#include "flandmark/data/cpp/flandmark_detector.h"
#include "detect_and_draw.cpp"




void detect_and_draw( IplImage* image, double scale, CvMemStorage* storage,
                    CvHaarClassifierCascade* cascade, bool show );

void analyse( char* dirname, int output_num );

const char* cascade_name = "haarcascade_frontalface_alt.xml";

int main(int argc, char const *argv[])
{

  char dirname[256];
  int dir_num;
  for (dir_num = 1; dir_num <= 4; ++dir_num)
  {
    sprintf(dirname, "dataset/%d", dir_num);
    analyse( dirname, dir_num );
  }


  return 0;
}


void analyse( char* dirname, int output_num )
{

  int num_of_files;
  // using namespace boost::filesystem;
  // using namespace boost::lambda;
  // path the_path( dirname );
  // num_of_files = std::count_if( directory_iterator(the_path),
  //                               directory_iterator(),
  //                               bind( static_cast<bool(*)(const path&)>(is_regular_file), 
  //                               bind( &directory_entry::path, _1 ) ) );



  CvMemStorage* storage = 0;
  CvHaarClassifierCascade* cascade = 0;
  IplImage* image = NULL;
  cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

  char buf[256];
  char img_name[256];
  char full_img_name[256];
  float * landmarks;
  sprintf(buf, "output/smile.csv");
  FILE* out_smile = fopen(buf, "a");
  sprintf(buf, "output/not_smile.csv");
  FILE* out_not_smile = fopen(buf, "a");
  num_of_files = 700;



  for (int i = 1 + (output_num - 1) * num_of_files / 14; i <= output_num * num_of_files / 14; ++i)
  {
    for (int j = 11; j < 13; ++j)
    {
      sprintf(full_img_name, "%s/%d-%d.jpg", dirname, i, j);
      sprintf(img_name, "%d-%d.jpg", i, j);
      storage = cvCreateMemStorage(0);
      image = cvLoadImage( full_img_name, 1 );
      landmarks = (float*) malloc( 16 * sizeof(float));
      detect_and_draw( image, 1, storage, cascade, false, landmarks );
      if (j == 11) fprintf(out_not_smile, "%s,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                                          img_name,
                                          landmarks[0], landmarks[1],
                                          landmarks[2], landmarks[3],
                                          landmarks[4], landmarks[5],
                                          landmarks[6], landmarks[7],
                                          landmarks[8], landmarks[9],
                                          landmarks[10], landmarks[11],
                                          landmarks[12], landmarks[13],
                                          landmarks[14], landmarks[15]);

      else if (j == 12) fprintf(out_smile, "%s,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                                          img_name,
                                          landmarks[0], landmarks[1],
                                          landmarks[2], landmarks[3],
                                          landmarks[4], landmarks[5],
                                          landmarks[6], landmarks[7],
                                          landmarks[8], landmarks[9],
                                          landmarks[10], landmarks[11],
                                          landmarks[12], landmarks[13],
                                          landmarks[14], landmarks[15]);

      cvReleaseImage( &image );
      free(landmarks);
    }

  }
  
  fclose(out_smile);
  fclose(out_not_smile);
}