/* EKREM SONMEZER - 2021 */

#include <opencv2/opencv.hpp> 
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


// https://stackoverflow.com/a/46200638/11388217
int getMaxAreaContourId(vector <vector<cv::Point>> contours) {
   double maxArea = 0;
   int maxAreaContourId = -1;
   for (int j = 0; j < contours.size(); j++) {
       double newArea = cv::contourArea(contours.at(j));
       if (newArea > maxArea) {
           maxArea = newArea;
           maxAreaContourId = j;
       }
   }
   return maxAreaContourId;
}

int main() {

   deque <Point2f> trackPoints;

   VideoCapture cap(0);

   if (!cap.open(0))
   {
       return -1;
   }

   //lower and upper color values of tracked color -> set to blue default
   int colorLower[] = { 104,146,102 };
   int colorUpper[] = { 179,255,255 };

   //trackbars to change values of lower and upper 
   namedWindow("Trackbars");
   createTrackbar("ColorLower[0]", "Trackbars", &colorLower[0], 255);
   createTrackbar("ColorLower[1]", "Trackbars", &colorLower[1], 255);
   createTrackbar("ColorLower[2]", "Trackbars", &colorLower[2], 255);
   createTrackbar("ColorUpper[0]", "Trackbars", &colorUpper[0], 255);
   createTrackbar("ColorUpper[1]", "Trackbars", &colorUpper[1], 255);
   createTrackbar("ColorUpper[2]", "Trackbars", &colorUpper[2], 255);

   while (true)
   {
       Mat frame, blurred, hsv, mask, eroded, dilated;

       //get frame from capture
       cap >> frame;

       //blur it with gaussian blur
       GaussianBlur(frame, blurred, Size(11, 11), 0);

       //change color space to hsv
       cvtColor(blurred, hsv, COLOR_BGR2HSV);

       //create a mask for blue
       inRange(hsv, Scalar(colorLower[0], colorLower[1], colorLower[2]), Scalar(colorUpper[0], colorUpper[1], colorUpper[2]), mask);

       //delete small noises with erode and dilate
       erode(mask, eroded, Mat(), Point(-1, -1), 2);
       dilate(eroded, dilated, Mat(), Point(-1, -1), 2);

       // find contours of circle in dilated img
       vector<vector<Point>> contours;
       vector<Vec4i> hierarchy;
       findContours(dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

       if (contours.size() > 0) {
           //find max contour, calculate center and radius
           vector<Point> maxContour = contours.at(getMaxAreaContourId(contours));
           Point2f center;
           float radius;
           minEnclosingCircle(maxContour, center, radius);
           Moments M = moments(maxContour);

           //if radius higher than 5 draw it on frame
           if (radius > 5) {
               circle(frame, center, radius, Scalar(0, 255, 0), 2, LINE_8, 0);
           }
           // add point to tacked points
           trackPoints.push_front(center);

           // max size is 16
           if (trackPoints.size() > 16) {
               trackPoints.pop_back();
           }

           // draw tacked points into frame
           for (int i = 1; i < trackPoints.size(); i++) {
               if ((trackPoints[(int)(i - 1)].x == 0 && trackPoints[(int)(i - 1)].y == 0)|| (trackPoints[i].x == 0 && trackPoints[i].y == 0))
                  continue;
               int thickness = (int) sqrt(20 / (i + 1)) * 2.5;
               line(frame, trackPoints[(int)(i - 1)], trackPoints[i], Scalar(0, 0, 255), thickness);
           }
       }
       else {
           // if ball out of frame clear dequeue
           trackPoints.clear();
       }


       if (waitKey(30) == 27 || frame.empty())
           break;

       imshow("Webcam", frame);

       //other images for testing purposes
       //imshow("Blurred", blurred);
       //imshow("HSV", hsv);
       //imshow("Mask", mask);
       //imshow("Eroded", eroded);
       //imshow("Dilated", dilated);
   }
   return 0;
}