# Ball Tracking with OpenCV

![Language](https://img.shields.io/badge/language-c++-blue?style=flat-square) 
![Opencv](https://img.shields.io/badge/required-opencv-brightgreen?style=flat-square&logo=opencv)
![GitHub](https://img.shields.io/github/license/sonmezerekrem/ball-tracking-opencv-cpp?style=flat-square) 

This project contains ball tracking samples written in C++ with OpenCV.

## Run

This codes were executed at Windows 10 machine in Visual Studio 2019. Webcam capture was used as video source. OpenCV binaries should be added to project before execution.
Detailed explanation could be found at:
> https://medium.com/@subwaymatch/opencv-410-with-vs-2019-3d0bc0c81d96



### With Color

This technique uses HSV color space to track balls.

Resources used:
> https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/


### With Hough Circles

This technique uses OpenCV HoughCircles method to track balls.

Resources used:
> https://www.pyimagesearch.com/2014/07/21/detecting-circles-images-using-opencv-hough-circles/
> 
> https://www.geeksforgeeks.org/circle-detection-using-opencv-python/
>
> https://docs.opencv.org/master/dd/d1a/group__imgproc__feature.html#ga47849c3be0d0406ad3ca45db65a25d2d


## Sample Screenshot

![sample](/sample.png "sample")


## License

MIT License