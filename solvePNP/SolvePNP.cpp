//
// Created by will-zhu on 10/17/20.
//

#include "SolvePNP.h"

double SolvePNP::cameraCali()
{
    int count= 0;
    cameraMatrix.ptr<float>(0)[0] = 1;
    cameraMatrix.ptr<float>(1)[1] = 1;


    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30,0.001);
    int numCornersHor = 9;                                     //numbers of the horizon corners
    int numCornersVer = 6;                                     //numbers of the vertical corners
    int numSquares = 17;                                       //length of the square on the chess board
    Size s(1280,720);                           //resolution of the image

    vector<Point3f> obj;
    for (int i = 0; i < numCornersHor;i++)
    {
        for (int j = 0; j < numCornersVer;j++)
        {
            obj.push_back(Point3f((float)j * numSquares, (float)i * numSquares,0));
        }
    }

    for (int i = 0;i < files.size();i++)
    {
        printf("image file : %s \n", files[i].c_str());
        Mat image = imread(files[i]);
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        vector<Point2f> corners;
        findChessboardCorners(gray, Size(6, 9), corners);
        cornerSubPix(gray,corners,Size(5,5),Size(-1,-1),TermCriteria(TermCriteria::COUNT,30,0.01));
        imagePoints.push_back(corners);
        objectPoints.push_back(obj);
    }

    calibrateCamera(objectPoints, imagePoints, s, cameraMatrix, distCoeffs, rvecs, tvecs);
}

void SolvePNP::PNP() {
//cout<<imagePoints.size()<<endl;
//cout<<objectPoints.size()<<endl;
//cout<<cameraMatrix<<endl;
//cout<<distCoeffs<<endl;
cout<<"objectPoints.size = " <<objectPoints.size()<<endl;
//cout<<"imagePoints.size = " << imagePoints.size()<<endl;
    for(int i = 0;i<files.size();i++) {
        rvecs_PNP.push_back(Mat());
        tvecs_PNP.push_back(Mat());
        solvePnP(objectPoints[i], imagePoints[i], cameraMatrix, distCoeffs, rvecs_PNP[i], tvecs_PNP[i]);
        Rodrigues(rvecs_PNP[i],rvecs_PNP[i]);
    }

}

 void SolvePNP::displayPNP(){
    fstream output;
    output.open("/home/will-zhu/Documents/OpenCVTuturials/second week/solvePNP/Pnp.txt");
    for(int i = 0;i<rvecs_PNP.size();i++)
    {
        output<<"image number: " << i<<endl;
        output<<"rvecs_PNP"<<rvecs_PNP[i]<<endl;
        output<<"tvecs_PNP"<<tvecs_PNP[i]<<endl;
        output<<"\n";

    }
    output.close();
}

vector<Point2f> SolvePNP::p2c(vector<Point2f> &p) {
    vector<Point2f> tmp;
    undistortPoints(p,tmp,cameraMatrix,distCoeffs);
    return tmp;
}

void SolvePNP::get3d() {
    Mat T1, T2;
    hconcat(rvecs_PNP[0],tvecs_PNP[0],T1);
    hconcat(rvecs_PNP[1],tvecs_PNP[1],T2);
    Mat Points;
    triangulatePoints(T1,T2,p2c(imagePoints[0]),p2c(imagePoints[1]),Points);
    for (int i = 0; i < Points.cols;i++)   //
    {
        Points.col(i) /= Points.at<float>(3,i);
    }
    transpose(Points,Points);
    fstream file;
    file.open("/home/will-zhu/Documents/OpenCVTuturials/second week/solvePNP/triangulation.txt");
    double error;
    for (int i = 0; i < Points.rows;i++)
    {
        file<<"Point["<<i<<"]:"<<Points.row(i);
        file<<"  real Point: "<< objectPoints[0][i];
    }
}