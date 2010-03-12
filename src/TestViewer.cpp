
#include <iostream>
#include <highgui.h>
#include <cv.h>
#include "CamGigEProsilica.h"
#include "camera_interface/CamInfoUtils.h"

using namespace camera;

#include <stdio.h>

int main(int argc, char**argv)
{
    //init frame
    Frame frame;
    Frame frame2;
    frame_size_t size(640,480);
    frame.init(size.width,size.height,8,MODE_BAYER_GBRG,false);
    frame2.init(size.width,size.height,8,MODE_RGB,false);
    cv::Mat image (480, 640, CV_8UC3);

    //init camera
    CamGigEProsilica mycamera;
    CamInterface &camera = mycamera;

    //find and display all cameras
    // std::vector<CamInfo> cam_infos;
    // camera.listCameras(cam_infos);
    // showCamInfos(cam_infos);

    try
    {
        //opens a specific camera
        std::cout << "open camera GE1900C \n";
        camera.open2("GE1900C",Monitor);

        //sets binning to 1 otherwise high resolution can not be set
        //camera.setAttrib(int_attrib::BinningX,1);
        //camera.setAttrib(int_attrib::BinningY,1);

        //camera.setAttrib(double_attrib::FrameRate,10);
        //camera.setAttrib(enum_attrib::FrameStartTriggerModeToFixedRate);

        camera.setFrameToCameraFrameSettings(frame);
        //configure the camera to match the frame;

        //start capturing (buffer size is set to 10 frames)
        camera.grab(Continuously,10);


        //display 100 frames
        int i=0;
        cv::namedWindow("image",CV_WINDOW_AUTOSIZE);
        while (i<100)
        {
            if (camera.isFrameAvailable())
            {
                camera >> frame;
                //	cv::cvtColor(frame.convertToCvMat(), image, CV_BayerGR2RGB,3 );
                //	cv::imshow("image",image);
                Helper::convertColor(frame, frame2);
                cv::imshow("image",frame2.convertToCvMat());
                cv::waitKey(2);
                if (frame.getStatus() == STATUS_INVALID)
                    std::cout << "invalid\n";
                i++;
            }
            else
                usleep(100);
        }
    }
    catch (std::runtime_error e)
    {
        std::cout <<  e.what() << std::endl << std::endl;
    }

    //close camera
    camera.close();

    return 0;
}


