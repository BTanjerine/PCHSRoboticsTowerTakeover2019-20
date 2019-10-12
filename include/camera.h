using namespace vex;
using namespace std;

/***********************
Camera Subsystem
***********************/
class EYE{
  public:
  //object position detection
  enum ObjPos {OG = 0, CNT = 1};
  //object color detection
  enum ObjColr {RED = 1, BLU = 2};

  enum Cam {V1 = 0, V2 = 1};
  
  bool VisionState;   //tracking state (on/off)
  int ObjColor;       //color of the obj detecting(red/blue)

  bool detectMode;

  bool mode;

  EYE(int vis){
    mode = vis;
  }

  bool isExisting(){
    if(mode == V1){
      return Vision.largestObject.exists;
    }
    else if(mode == V2){
      return Vision2.largestObject.exists;
    }
  }
  
  //get objects X position
  int getObjectX(int objID, int Pos){
    int point = 0;
    if(mode==V1){
      if(Pos == OG){  //detect from conrner position
        point = Vision.objects[objID].originX;
      }
      else if(Pos == CNT){ //detect from center position
        point = Vision.objects[objID].centerX;
      }
    }
    else if(mode == V2){
      if(Pos == OG){  //detect from conrner position
        point = Vision2.objects[objID].originX;
      }
      else if(Pos == CNT){ //detect from center position
        point = Vision2.objects[objID].centerX;
      }
    }
    return point;
  }
  
  //get objects Y position
  int getObjectY(int objID, int Pos){
    int point = 0;

    if(mode==V1){
      if(Pos == OG){  //detect from conrner position
        point = Vision.objects[objID].originY;
      }
      else if(Pos == CNT){ //detect from center position
        point = Vision.objects[objID].centerY;
      }
    }
    else if(mode == V2){
      if(Pos == OG){  //detect from conrner position
        point = Vision2.objects[objID].originY;
      }
      else if(Pos == CNT){ //detect from center position
        point = Vision2.objects[objID].centerY;
      }
    }
    return point;
  }
  
  //get height of object 
  int getObjectH(int objID){
    int h;
    if(mode == V1){
      h = Vision.objects[objID].height;
    }
    else if(mode == V2){
      h = Vision2.objects[objID].height;
    }
    return h;
  }
  
  //get width of object
  int getObjectW(int objID){    
    int w;
    if(mode == V1){
      w = Vision.objects[objID].width;
    }
    else if(mode == V2){
      w = Vision2.objects[objID].width;
    }
    return w;
  }
  
  //get area of object
  int getObjectA(int objID){
    int Area = getObjectW(objID) * getObjectH(objID);
    return Area;
  }
};