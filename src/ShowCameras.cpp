#include "CamGigEProsilica.h"
#include <camera_interface/CamInfoUtils.h>
#include <iostream>

int main(int argc, char** argv)
{
    using namespace camera;
    CamGigEProsilica prosilica;

    std::vector<CamInfo> camInfos;
    prosilica.listCameras(camInfos);

    showCamInfos(camInfos);

    return 0;
}
