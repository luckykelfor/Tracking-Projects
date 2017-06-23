#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"

//#include <dirent.h>

using namespace std;
using namespace cv;
Rect box; // tracking object
bool drawing_box = false;
bool gotBB = false;	// got tracking box or not
bool fromfile = true;


void readBB(char* file)	// get tracking box from file
{
	ifstream tb_file(file);
	string line;
	getline(tb_file, line);
	istringstream linestream(line);
	string x1, y1, w1, h1;
	getline(linestream, x1, ',');
	getline(linestream, y1, ',');
	getline(linestream, w1, ',');
	getline(linestream, h1, ',');
	int x = atoi(x1.c_str());
	int y = atoi(y1.c_str());
	int w = atoi(w1.c_str());
	int h = atoi(h1.c_str());
	box = Rect(x, y, w, h);
}

// tracking box mouse callback
void mouseHandler(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0)
		{
			box.y += box.height;
			box.height *= -1;
		}
		gotBB = true;
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[]){

	if (argc > 5) return -1;

	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

	for(int i = 0; i < argc; i++){
		if ( strcmp (argv[i], "hog") == 0 )
			HOG = true;
		if ( strcmp (argv[i], "fixed_window") == 0 )
			FIXEDWINDOW = true;
		if ( strcmp (argv[i], "singlescale") == 0 )
			MULTISCALE = false;
		if ( strcmp (argv[i], "show") == 0 )
			SILENT = false;
		if ( strcmp (argv[i], "lab") == 0 ){
			LAB = true;
			HOG = true;
		}
		if ( strcmp (argv[i], "gray") == 0 )
			HOG = false;
	}
	
	// Create KCFTracker object
	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);

	// Frame readed
	Mat frame;

	// Tracker results
	Rect result;

	// Path to list.txt
	ifstream listFile;
	string fileName = "images.txt";
  	listFile.open(fileName);

  	// Read groundtruth for the 1st frame
  	ifstream groundtruthFile;
	string groundtruth = "region.txt";
  	groundtruthFile.open(groundtruth);
  	string firstLine;
  	getline(groundtruthFile, firstLine);
	groundtruthFile.close();
  	
  	istringstream ss(firstLine);

  	// Read groundtruth like a dumb
  	float x1, y1, x2, y2, x3, y3, x4, y4;
  	char ch;
	ss >> x1;
	ss >> ch;
	ss >> y1;
	ss >> ch;
	ss >> x2;
	ss >> ch;
	ss >> y2;
	//ss >> ch;
	//ss >> x3;
	//ss >> ch;
	//ss >> y3;
	//ss >> ch;
	//ss >> x4;
	//ss >> ch;
	//ss >> y4; 

	//// Using min and max of X and Y for groundtruth rectangle
	//float xMin =  min(x1, min(x2, min(x3, x4)));
	//float yMin =  min(y1, min(y2, min(y3, y4)));
	//float width = max(x1, max(x2, max(x3, x4))) - xMin;
	//float height = max(y1, max(y2, max(y3, y4))) - yMin;

	//
	float xMin = x1;
	float yMin = y1;
	float width = x2;
	float height = y2;
	
	// Read Images
	ifstream listFramesFile;
	string listFrames = "images.txt";
	listFramesFile.open(listFrames);
	string frameName;


	// Write Results
	ofstream resultsFile;
	string resultsPath = "d:/output.txt";
	resultsFile.open(resultsPath);

	// Frame counter
	int nFrames = 0;
	VideoCapture vcap;
	vcap.open("G:/QQfiles/804194469/FileRecv/CMT/CMT/£¡£¡£¡IMG_Fa21.avi");
	if (SILENT){
		namedWindow("KCF");//imshow("Image", frame);
		//waitKey(1);
	}
	setMouseCallback("KCF", mouseHandler, NULL);
	vcap.read(frame);
	Mat temp = frame.clone();
	while (!gotBB)
	{
		//
		 
		rectangle(frame, box, Scalar(0, 0, 255));
		imshow("KCF", frame);
		temp.copyTo(frame);
		if (cvWaitKey(33) == 'q') { return 0; }
	}

	tracker.init(box, frame);
	//rectangle( frame, Point( xMin, yMin ), Point( xMin+width, yMin+height), Scalar( 0, 255, 255 ), 1, 8 );
	resultsFile << xMin << "," << yMin << "," << width << "," << height << endl;

	while (vcap.isOpened()){// getline(listFramesFile, frameName) ){
		//frameName = frameName;

		// Read each frame from the list

		// First frame, give the groundtruth to the tracker
		 vcap.read(frame);// = imread(frameName, CV_LOAD_IMAGE_COLOR);

		// Update
	 
			result = tracker.update(frame);
			rectangle(frame, Point(result.x, result.y), Point(result.x + result.width, result.y + result.height), Scalar(0, 255, 255), 1, 8);
			resultsFile << result.x << "," << result.y << "," << result.width << "," << result.height << endl;
	 


		nFrames++;

		if (SILENT){
			imshow("KCF",frame);//imshow("Image", frame);
			waitKey(1);
		}
		
	}
	vcap.release();
	resultsFile.close();
	
}
	//

	//listFile.close();


 
