
#include "CamGigEProsilica.h"
using namespace camera;

#include <iostream>
#include <stdlib.h>
using namespace std;

int main (int argc, char** argv) {
  try {
    // todo: adapt if you want to use another default camera
    char *_uid = "105984";
    if (argc > 1) {
      _uid = argv[1];
    }
    unsigned long uid = atoi(_uid);
    if (uid == 0) {
      cerr << "error! bad uid: '" << _uid << "' interpreted as " << uid << endl;
      return -1;
    }
    
    CamGigEProsilica prosilica;
    CamInterface &cam = prosilica;
    if (!prosilica.open2(uid)) {
      cerr << "could not open camera with uid " << uid << endl;
      return -1;
    }
    else {
      cerr << "camera with uid " << uid << " successfully opened" << endl;
      cam.close();
      return 0;
    }

  }
  catch(std::runtime_error &e) {
    cerr << e.what() << endl;
  }
  catch(std::exception &e) {
    cerr << e.what() << endl;
  }
  catch(...) {
    cerr << "wtf?" << endl;
  }
  
  return -1;
}

