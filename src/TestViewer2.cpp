#include "CamGigEProsilica.h"			//camera implementation

using namespace camera;

int main(int argc, char**argv)
{
    //init frame
    //width = 640 ; height = 360; color depth = 8 Bit; Color Mode = RGB
    Frame frame(640,360,8,MODE_RGB);
 
    //set interface to Prosilica GigE
    CamGigEProsilica prosilica_gige;
    CamInterface &camera = prosilica_gige;
    try
    {
        //open a camera by name
        std::cout << "open camera GE1900C \n";
        camera.open2("GE1900C",Master);
	
	//configure the camera to match the frame settings;
        camera.setFrameSettings(frame);

	//grab and retrieve a single frame
	camera >> frame;	
    }
    catch (std::runtime_error e)
    {
        std::cout <<  e.what() << std::endl << std::endl;
    }
    //close camera
    camera.close();
    return 0;
}
