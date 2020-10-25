
#include <iostream>
#include <string>
#include "Trackers.cpp"

using namespace std;
using namespace cv;

void reset(Ptr<TrackerKCF> &T, Rect2d &roi, Mat frame);
void reset(Ptr<TrackerCSRT> &T, Rect2d &roi, Mat frame);
void reset(Ptr<TrackerMOSSE> &T, Rect2d &roi, Mat frame);
int main() {

    Mat frame;
    VideoCapture capture;
    capture.open("../single.mp4");
    if (!capture.isOpened()){
        printf("can not open video ");
        return -1;
    }
    namedWindow("output",WINDOW_AUTOSIZE);


 //   Ptr<TrackerKCF>tracker = TrackerKCF::create();
 //   Ptr<TrackerMOSSE> tracker  = TrackerMOSSE::create();
      Ptr<TrackerCSRT>   tracker = TrackerCSRT::create();




    capture.read(frame);
    VideoWriter writer("CSRT.avi",VideoWriter::fourcc('M','J','P','G'),25.0,Size(frame.cols,frame.rows));
    Rect2d roi;
    roi = selectROI("output",frame);

    tracker->init(frame,roi);
    int count = 1;
    while (capture.read(frame)){
        if (count % 700 != 0){
            if (frame.empty()) return -1;

            tracker->update(frame,roi);
            rectangle(frame,roi,Scalar(255,0,0),2,8,0);
            imshow("output",frame);
            writer<<frame;
            char c = waitKey(1);
            if (c==27)
            {
                break;
            }
        }
        else{
            reset(tracker,roi,frame);
        }
        count++;
    }
    capture.release();
    writer.release();
    destroyAllWindows();
    return 0;
}
void reset(Ptr<TrackerCSRT> &T, Rect2d &roi, Mat frame){
    roi = selectROI("output",frame);
    T = TrackerCSRT::create();
    T->init(frame,roi);
}
void reset(Ptr<TrackerKCF> &T, Rect2d &roi, Mat frame){
    roi = selectROI("output",frame);
    T = TrackerKCF::create();
    T->init(frame,roi);
}
void reset(Ptr<TrackerMOSSE> &T, Rect2d &roi, Mat frame){
    roi = selectROI("output",frame);
    T = TrackerMOSSE::create();
    T->init(frame,roi);
}