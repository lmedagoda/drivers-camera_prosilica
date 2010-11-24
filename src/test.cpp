
#define _LINUX
#define _x86

#include "CamGigEProsilica.h"
#include "camera_interface/CamInfoUtils.h"
using namespace camera;

#include <iostream>
#include <vector>
using namespace std;

int main () {
  try {
    CamGigEProsilica prosilica;
    CamInterface &cam = prosilica;
    vector<CamInfo> cam_infos;
    cout << cam.listCameras(cam_infos) << endl;
    cam_infos.pop_back();
    showCamInfos(cam_infos);
    if (cam_infos.size() > 0) {
      cam.open(cam_infos[0],Master);
      if (cam.isOpen()) cout << "camera open" << endl;
      cam.close();
    }
  }
  catch(std::runtime_error &e) {
    cout << e.what() << endl;
  }
  catch(std::exception &e) {
    cout << e.what() << endl;
  }
  catch(...) {
    cout << "wtf?" << endl;
  }

  return 0;
}

