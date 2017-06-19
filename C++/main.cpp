/*
    @Author: Maik Basso <maik@maikbasso.com.br> 

    To compile and run program:
    g++ -std=c++11 pld-video.cpp -o pld-video `pkg-config --cflags --libs opencv` && ./pld-video

*/

//Include file for every supported OpenCV function
#include <opencv2/opencv.hpp>
#include <iostream>
//my libraries
#include "line.h"
#include "pld.h"
#include "line-follower.h"

using namespace cv;
using namespace std;

void video(){
    Mat frame;
    // create a capture object
    VideoCapture cap;
    //from camera capture
    //cap.open(0);
    //from video file
    cap.open("../../videos/video-lines.mp4");

    if(!cap.isOpened()){
        cout << "Cannot open the capture or video file." << endl;
        return;
    }

    //create the line detection object
    PlantLineDetection *ld = new PlantLineDetection();

    //read frame per frame
    while(cap.read(frame)){
    	//resize image for input
    	Mat tempImage;
    	resize(frame, tempImage, Size(320,240) );

        //set image
        ld->setImage(tempImage);

        //detect
        ld->detect();

        //show results
        ld->showResults();

        //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
        if(waitKey(30) == 27) {
            break;
        }
    }
}

void photo(){

    // create the mat
    Mat image;

    // open a image file
    image = imread("../../photos/test1.png");

    // Check for invalid input
    if(!image.data){
        cout <<  "Could not open or find the image." << endl;
        return;
    }
    
    // create the line detection object
    PlantLineDetection *ld = new PlantLineDetection();

    //create the follow line object
    LineFollower *fl = new LineFollower();
        
    //resize image for input
    Mat tempImage;
    resize(image, tempImage, Size(320,240) );

    //set image
    ld->setImage(tempImage);

    // detect
    ld->detect();

    // show results
    ld->showResults();

    vector <Line*> lines = ld->getDetectedLines();
    cout << "List of lines:" << endl;
    for(int i = 0; i< lines.size(); i++){

        cout  << i << ":\tp1(" << lines[i]->p1.x << ", " << lines[i]->p1.y << ")\tp2(" << lines[i]->p2.x << ", " << lines[i]->p2.y << ")" << endl;

    }

    fl->setSize(320,240);
    fl->setLines(lines);

    cout << "Followed Line: " << endl;

    Line* followedLine = fl->getFollowedLine();

    cout  << "\tp1(" << followedLine->p1.x << ", " << followedLine->p1.y << ")\tp2(" << followedLine->p2.x << ", " << followedLine->p2.y << ")" << endl;

    //wait key to finish
    waitKey(0);
}

int main(){

    int op = -1;

    do{
        // ask user for use video or photo data
        cout << "Select the input data:" << endl;
        cout << "[0] exit" << endl;
        cout << "[1] video" << endl;
        cout << "[2] photo" << endl;
        cout << ">> ";
        //cin >> op;
        //fixed for build it in sublime cout << "2" << endl;
        op = 2; cout << "2" << endl;

        if(op == 1){
            cout << "Video input selected!" << endl;
            video();
            op = 0;
        }
        else if(op == 2){
            cout << "Photo input selected!" << endl;
            photo();
            op = 0;
        }
        else if(op == 0){
            cout << "Bye Bye!" << endl;
        }
        else{
            cout << "Error: Select the correct data type!" << endl;
            op == -1;
        }

    }while(op != 0);

    // end the program without errors
    return 0;    
}