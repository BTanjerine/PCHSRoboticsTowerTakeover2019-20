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

  enum Cam {FLAG = 0, Int = 1};
  
  bool VisionState;   //tracking state (on/off)
  int ObjColor;       //color of the obj detecting(red/blue)

  bool detectMode;

  int mode;

  bool isExisting(){
    if(mode == Int){
      return Vision.largestObject.exists;
    }
  }
  
  //get objects X position
  int getObjectX(int objID, int Pos){
    int point = 0;
    if(Pos == OG){  //detect from conrner position
      point = Vision.objects[objID].originX;
    }
    else if(Pos == CNT){ //detect from center position
      point = Vision.objects[objID].centerX;
    }
    return point;
  }
  
  //get objects Y position
  int getObjectY(int objID, int Pos){
    int point = 0;
    if(Pos == OG){ //detect from conrner position
      point = Vision.objects[objID].originY;
    }
    else if(Pos == CNT){ //detect from center position
      point = Vision.objects[objID].centerY;
    }
    return point;
  }
  
  //get height of object 
  int getObjectH(int objID){
    return Vision.objects[objID].height;
  }
  
  //get width of object
  int getObjectW(int objID){    
    return Vision.objects[objID].width;
  }
  
  //get area of object
  int getObjectA(int objID){
    int Area = getObjectW(objID) * getObjectH(objID);
    return Area;
  }
};