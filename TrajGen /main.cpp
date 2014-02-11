/* 
 * File:   main.cpp
 * Author: shiwangi
 *
 * Created on 23 January, 2014, 6:23 PM
 */

#include <cstdlib>

using namespace std;

#include "Clothoid.hpp"
#include "State.h"
#include <time.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/core/core.hpp"
#include "opencv2/core/mat.hpp"

using namespace std;

class Poses {
public:
    State a, b;

    Poses(State a_, State b_) {
        a= a_;
        b = b_;
    }
};

double inRange(double theta) {
    if (theta > 2 * PI) {
        while (theta > 2 * PI) {
            theta -= 2 * PI;
        }
    }

    if (theta < 0) {
        while (theta < 0) {
            theta += 2 * PI;
        }
    }

    return theta;

}



void plotPath(State start, State end, vector<State> pathToPlot,cv::Mat &img) {

    
    cout << pathToPlot.size() << endl;
    cv::circle(img, cvPoint(start.x, HEIGHT - start.y), 5, cvScalarAll(255));
    cv::circle(img, cvPoint(end.x, HEIGHT - end.y), 5, cvScalarAll(255));
    cv::line(img, cvPoint(start.x, HEIGHT - start.y), cvPoint(end.x, HEIGHT - end.y), cvScalar(255));
    for (int i = 0; i + 1 < pathToPlot.size(); i++) {
        cv::line(img, cvPoint(pathToPlot[i].x, HEIGHT - pathToPlot[i].y), cvPoint(pathToPlot[i + 1].x, HEIGHT - pathToPlot[i + 1].y), cvScalar(255, 255, 255));
    }

    cv::imshow("PATH", img);

    cvWaitKey(0);


}
void Trajgen(State& a,State& b){
        Clothoid curve;
        cv::Mat img = cv::Mat(cvSize(800, 800), CV_8UC3, cvScalarAll(0));
        double totLength=0;
        cout << "**************beginner Alert*****************************" << endl;
        curve.getPath(a, b);
        if (curve.solution == 0)
            cout << "The points are too close !" << endl;
        else{
            
            for(int j=0;j<curve.paths.size();j++){
                totLength+=curve.paths[j].lengthOfPath;
                plotPath(a, b, curve.paths[j].path,img);
            }
            cout<<"The total length : "<<totLength<<endl;
            cvWaitKey(0);
        }

}

int main(int argc, char** argv) {
    double angle1, angle2;
    /*TODO: SUBSCRIBER */
    Subscriber sub = it.subscribe("pose/target", 2, &Trajgen);
    ros::Rate loop_rate(LOOP_RATE);
    ROS_INFO("TRAJ GEN_THREAD STARTED");
    while(ros::ok()) {
       ros::spinOnce();
       loop_rate.sleep();
    }
    ROS_INFO("TRAJECTORY code exiting");
    
  
    return 0;
}

