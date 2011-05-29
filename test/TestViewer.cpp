
#include <iostream>
#include <highgui.h>				//opencv header
#include <cv.h>					//opencv header
#include "CamGigEProsilica.h"			//camera implementation
#include "camera_interface/CamInfoUtils.h"	//helper for displaying camera infos

using namespace camera;

int main(int argc, char**argv)
{
    //init frame
    //width = 640 ; height = 360; color depth = 8 Bit; Color Mode = RGB
    Frame frame(640,360,8,MODE_RGB);
 
    //set interface to Prosilica GigE
    CamGigEProsilica prosilica_gige;
    CamInterface &camera = prosilica_gige;

    //find and display all available cameras
    std::vector<CamInfo> cam_infos;
    camera.listCameras(cam_infos);
    showCamInfos(cam_infos);

    try
    {
        //opens a specific camera
        std::cout << "open camera GE1900C \n";
        camera.open2("GE1900C",Master);
	
	//configure the camera to match the frame settings;
        camera.setFrameSettings(frame);

        //set binning to 3
        camera.setAttrib(int_attrib::BinningX,3);
        camera.setAttrib(int_attrib::BinningY,3);

	//set frame rate to 10 and use fixed trigger mode
        camera.setAttrib(double_attrib::FrameRate,10);
        camera.setAttrib(enum_attrib::FrameStartTriggerModeToFixedRate);

        //start capturing (buffer size is set to 4 frames)
        camera.grab(Continuously,4);
	
        //display 100 frames
        int i=0;
        while (i<100)
        {
            
	    if (camera.isFrameAvailable())
            {
              //retrieve frame  
	      camera >> frame;	
              //display frame if frame is valid
	      if (frame.getStatus() != STATUS_INVALID)
		 cv::imshow("image",frame.convertToCvMat());
	      else
                std::cout << "invalid\n";
	      cv::waitKey(2);
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


