#include "cpp/flandmark_detector.h"
#include "highgui.h"

int main(int argc, char * argv[])
{
  FLANDMARK_Model * model = flandmark_init("flandmark_model.dat");

  IplImage *img = cvLoadImage("face.jpg");

  IplImage *img_grayscale = cvCreateImage(cvSize(img->width, img->height), 8, 1);
  cvCvtColor(img, img_grayscale, CV_BGR2GRAY);

  int bbox[] = {72, 72, 183, 183};

  float * landmarks = (float*)malloc(2*model->data.options.M*sizeof(float));
  flandmark_detect(img_grayscale, bbox, model, landmarks);

  for (int i = 0; i < 2*model->data.options.M; ++i)
  {
    printf("%lf\n", landmarks[i]);
  }

  return (0);
}
