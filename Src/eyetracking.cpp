
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <opencv2/tracking/tracker.hpp>
#include <opencv2/tracking/tldDataset.hpp>

using namespace cv;
using namespace std;
int flag=0;
int t1,t2,t3,t4;
int main(int argc, char* argv[])
{

	Mat frame;
	int i,j;
	std::vector<Rect> eyes;
	bool status = false;
	char str[100];
	char str1[100];
	int flag=0;
	Ptr<TrackerKCF> tracker = TrackerKCF::create();
	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;
	eye_cascade.load("haarcascade_eye_tree_eyeglasses.xml" );
	VideoCapture cap; // Declare cap for videocapture
	if(argc > 1)
	{
		cap.open(argv[1]);
	}
	else
	{
		cap.open(0);
		if (!cap.isOpened())  // if not success, exit program
		{
			cout << "Cannot open the video cam" << endl;
			return -1;
		}
	}
	while (1)
	{
	bool bSuccess = cap.read(frame); // read a new frame from video
	
		if(flag==1)
		{
		 	Rect2d bbox(t1,t2,t3,t4);
       		tracker->update(frame,bbox);
        	rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
		}
		eye_cascade.detectMultiScale( frame, eyes, 1.4, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
      	
		for( i = 0; i < eyes.size(); i++ )
		{
			Rect2d bbox(eyes[i].x,eyes[i].y,eyes[i].width,eyes[i].height);
			t1=eyes[i].x;t2=eyes[i].y;t3=eyes[i].width;t4=eyes[i].height;
			tracker->init(frame, bbox);
    		//rectangle( frame, bbox, Scalar( 0, 255, 0 ), 4, 8, 0 );
		flag=1;
		}
		//putText(frame, str, Point(30,30),FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0,255,0), 1, AA);
		namedWindow("MyVideo",WINDOW_AUTOSIZE); //create a window called "MyVideo"
		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

