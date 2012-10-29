from cv import *
from cv2 import *
from sys import *
from Tkinter import Tk
from tkFileDialog import askopenfilename


class UnknownOptionError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class CannotLoadClassifierError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)



def detect_and_draw( img ):
    """function detecting faces on a given image"""
    colors = [ (0, 0, 255, 0), (0, 128, 255, 0), (0, 255, 255, 0), (0, 255, 0, 0), (255, 128, 0, 0),
               (255, 255, 0, 0), (255, 0, 0, 0), (255, 0, 255, 0) ]

    gray = None
    small_img = None
    copy = None
    faces_themselves = [0] * 10
    flag = False
    num_detected = 0

    gray = CreateImage( (img.width, img.height), 8, 1 )
    small_img = CreateImage( ( Round (img.width / scale), Round (img.height / scale)), 8, 1 )

    CvtColor( img, gray, CV_BGR2GRAY )
    Resize( gray, small_img, CV_INTER_LINEAR )
    EqualizeHist( small_img, small_img )

    if cascade:
        t = GetTickCount()
        faces = HaarDetectObjects( small_img, cascade, storage,
                                             1.1, 2, 0
                                             #|CV_HAAR_FIND_BIGGEST_OBJECT
                                             #|CV_HAAR_DO_ROUGH_SEARCH
                                             |CV_HAAR_DO_CANNY_PRUNING
                                             #|CV_HAAR_SCALE_IMAGE
                                             ,
                                             (30, 30) );
        t = GetTickCount() - t
        det_time = 'detection time = %sms' % str(t / (GetTickFrequency()*1000.0))
        print det_time

        for i in range(len(faces) if faces else 0):
            # r = GetSeqElem( faces, i )
            r = faces[i]
            small_img_roi = None
            nested_objects = None
            color = colors[i % 8]
            center_x = Round((r[0][0] + r[0][2] * 0.5) * scale)
            center_y = Round((r[0][1] + r[0][3] * 0.5) * scale)
            radius = Round((r[0][2] + r[0][3]) * 0.25 * scale)

            if ( r[0][2] and r[0][3] ):
                flag = True
                num_detected = i + 1
                SetImageROI(img, ( center_x - radius, center_y - radius, 2 * radius, 2 * radius))
                faces_themselves[i] = CreateImage(GetSize(img), img.depth, img.nChannels)
                Copy(img, faces_themselves[i])
                ResetImageROI(img)

            Circle( img, (center_x, center_y), radius, color, 3, 8, 0 )

    ShowImage( "result", img )

    if flag:
        for i in range(num_detected):
            win_name = "face_%s" % str(i)
            NamedWindow( win_name, CV_WINDOW_AUTOSIZE )
            ShowImage( win_name, faces_themselves[i] )

        for i in range(num_detected):
            win_name = "face_%s" % str(i)
            DestroyWindow("win_name")







def main():
    """reading input files or webcam stream and invoking detect_and_draw"""

    cascade_name = "haarcascade_frontalface_alt.xml"


    global scale
    scale = 1

    g_slider_position = 0
    g_capture         = None

    def onTrackbarSlide(pos):
    	SetCaptureProperty(
            g_capture,
            CV_CAP_PROP_POS_FRAMES,
            pos
        )

    capture = None
    global cascade
    cascade = None
    frame = None
    frame_copy = None
    image = None
    scale_opt = "--scale="
    scale_opt_len = len(scale_opt)
    cam_opt = "--cam="
    cam_opt_len = len(cam_opt)
    input_name = None



    for i in xrange(1, len(argv)):
    	if argv[i][:-1] == scale_opt:
    		scale = int(argv[i][-1])
    	elif argv[i][:-1] == cam_opt:
    		input_name = argv[i][-1]
    	elif argv[i][0] == '-':
    		raise UnknownOptionError(argv[i])

    if not input_name:
    	Tk().withdraw() 
    	input_name = askopenfilename()

    cascade = Load( cascade_name )

    if not cascade:
    	raise CannotLoadClassifierError(cascade_name)


    global storage
    storage = CreateMemStorage(0)

    if input_name.isdigit():
    	capture = CaptureFromCAM( int(input_name) if input_name else 0 )
    elif input_name:
    	try:
    		image = LoadImage( input_name, 1 )
    	except IOError:
    		g_capture = CreateFileCapture( input_name )


    NamedWindow( "result", CV_WINDOW_AUTOSIZE )




    if g_capture:
        foo = QueryFrame( g_capture)
        frames = int (GetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT))

        CreateTrackbar("Position", "result", g_slider_position, frames, onTrackbarSlide)
        frames = 0

        while True:
            frame = QueryFrame( g_capture )
            if not frame: break
            frames = int (GetCaptureProperty( g_capture, CV_CAP_PROP_POS_FRAMES))
            SetTrackbarPos("Position", "result", frames)
            # ShowImage( "result", frame )
            detect_and_draw( frame );
            c = WaitKey(10)
            if c == 112:
                while True:
                    pause = WaitKey(10)
                    if pause == 112: break

        cvReleaseCapture( g_capture )
        cvDestroyWindow( "result" )


    elif capture:
        while True:
            frame = QueryFrame( capture )
            if not frame: break
            # ShowImage( "result", frame )
            detect_and_draw( frame );
            c = WaitKey(10)
            if c == 112:
                while True:
                    pause = WaitKey(10)
                    if pause == 112: break

        cvReleaseCapture( capture )
        cvDestroyWindow( "result" )

    elif image:
        # ShowImage( "result", image )
        detect_and_draw( image )
        WaitKey(0)
        cvReleaseImage( image )
        cvDestroyWindow( "result" )



if __name__ == '__main__':
    main()