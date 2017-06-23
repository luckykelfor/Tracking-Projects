This C++ code is an implementation of the visual tracking method proposed in [1]. The implementation is based on the Matlab code provided by the authors of the paper.
The implementation in C++ using openCV was done by Mostafa Izz.

Instructions:
The code is not provided as executable, you need to compile. It was created for integration with openCV.
There are two interfaces provided in the code in class "color_tracker"
1) cv::Rect track_frame(cv::Mat &current_frame)
Provided to track frame by frame
So, the parameters needed to be passed to the constructor are used for intializing the bounding box only.
2) void track_video(double start_second = 0, double end_second = 0)
Provided to track video
In the second case the video path should be provided in the parameters passed to the constructor.

There are examples on both interfaces in the file "source.cpp"
There is a simple example in the file "static.cpp" for usage with the VOT challenge.

The code was tested under two environments:

1- Windows 7 using visual studio 2013 with openCV 2.4.9
2- Ubuntu 14.04 with GCC 4.8.2 with openCV 2.4.9

-------------------------------
To test the code under ubuntu you need g++ and OpenCV installed:
to install g++ simply run:

sudo apt-get install g++

then to install opencv you can run the script in the following link:
https://github.com/jayrambhia/Install-OpenCV/blob/master/Ubuntu/2.4/opencv2_4_9.sh
it shall install opencv 2.4.9 for you (you can browse the repository https://github.com/jayrambhia/Install-OpenCV/blob/master/ if you need different version or different distribution)

then compile the sources for the Color Tracker code using the following command:
g++ -std=c++11 `pkg-config --cflags opencv` -O2 -o tracker_tester source.cpp color_tracker.cpp color_tracker_parameters.cpp `pkg-config --libs opencv`

This will give you binary file named "tracker_tester". Then, you can run it directly if you cloned the git repository:
./tracker_tester
And it will run four experiments (you need to press any key at the end of each experiment)

you can also test using vot_toolkit by compiling the Color Tracker Code using the following command:
g++ -std=c++11 `pkg-config --cflags opencv` -O2 -o vot_tester static.cpp color_tracker.cpp color_tracker_parameters.cpp `pkg-config --libs opencv`

This will give you binary file named "vot_tester".

Then you can follow the instructions in the VOT challenge website:
http://www.votchallenge.net/howto/perfeval.html

And in step 2:
- The tracker is binary executable and you need to provide the full path
example:
tracker_command = fullfile('/home/mostafaizz/ColorTracker/vot_tester');
- set variable tracker_trax to false

then you should be able to run the experiments from matlab/octave normally

-----------------------------------
Contact (for the c++ code):
Mostafa Izz
izz.mostafa@gmail.com

One should contact the paper authors in [1] if you need clarifications about the algorithm itself.

----
References:
[1] Martin Danelljan, Fahad Shahbaz Khan, Michael Felsberg and Joost van de Weijer.
    "Adaptive Color Attributes for Real-Time Visual Tracking".
    Proceedings of IEEE Conference on Computer Vision and Pattern Recognition (CVPR), 2014.
