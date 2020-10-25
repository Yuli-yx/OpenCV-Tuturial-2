//
// Created by will-zhu on 10/17/20.
//
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "fstream"
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;
#ifndef SOLVEPNP_SOLVEPNP_H
#define SOLVEPNP_SOLVEPNP_H


class SolvePNP {



    vector<string> files;
    vector<Mat> rvecs_PNP;
    vector<Mat> tvecs_PNP;


public:
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    SolvePNP(vector<string> file){
        files = file;
    }
    vector<vector<Point2f>> imagePoints;
    vector<vector<Point3f>> objectPoints;
    Mat cameraMatrix = Mat(3, 3, CV_32FC1);
    Mat distCoeffs ;
    double cameraCali();
    void PNP();
    void displayPNP();
    vector<Point2f> p2c(vector<Point2f>& p);
    void get3d();

};


#endif //SOLVEPNP_SOLVEPNP_H
