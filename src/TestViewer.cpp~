
#include <iostream>
#include <highgui.h>
#include <cv.h>
#include "CamGigEProsilica.h"
#include "camera_interface/CamInfoUtils.h"

using namespace camera;

int main(int argc, char**argv)
{
    //init frame
    Frame frame;
    frame_size_t size(640,480);
    frame.init(size.width,size.height,8,MODE_RGB,false);

    //init camera
    CamGigEProsilica mycamera;
    CamInterface &camera = mycamera;

    //find and display all cameras
    std::vector<CamInfo> cam_infos;
    camera.listCameras(cam_infos);
    showCamInfos(cam_infos);

   
    try
    {
        //opens a specific camera
        std::cout << "open camera GE1900C \n";
        camera.open2("GE1900C",Master);
        //configure the camera to match the frame;

  //      camera.setFrameSettings(frame);
   //     camera.setAttrib(double_attrib::FrameRate,10);
   //     camera.setAttrib(enum_attrib::FrameStartTriggerModeToFixedRate);

        //start capturing (buffer size is set to 10 frames)
        camera.grab(Continuously,10);

        //display 100 frames
        int i=0;
        while(i<100)
        {
            if (camera.isFrameAvailable())
            {
                camera >> frame;
                cv::imshow("image",frame.convertToCvMat());
                cv::waitKey(2);
                i++;
            }
            else
               usleep(1000);
        }
    }
    catch(std::runtime_error e)
    { std::cout <<  e.what() << std::endl << std::endl;}

    //close camera
    camera.close();

    return 0;
}


