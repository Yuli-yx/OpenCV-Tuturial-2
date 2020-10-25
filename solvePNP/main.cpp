#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "SolvePNP.h"
using namespace std;
using namespace cv;

int main() {
    vector<string> files;
    glob("/home/will-zhu/Documents/OpenCVTuturials/second week/chess", files);

    SolvePNP c(files);
    c.cameraCali();
    c.PNP();
    c.displayPNP();
    c.get3d();
}
