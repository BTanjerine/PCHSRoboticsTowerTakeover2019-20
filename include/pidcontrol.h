class PID{
  public:
  float Kp;
  float Ki;
  float Kd;

  float _p = 0.0;
  float _i = 0.0;
  float _d = 0.0;
  float PctPower = 0.0;
  float pastError = 0.0;


  PID(float kp, float ki, float kd){
    Kp = kp;
    Ki = ki;
    Kd = kd;
  }

  //get PID constant values (debugging)
  float getKp(){
    return Kp;
  }
  float getKi(){
    return Ki;
  }
  float getKd(){
    return Kd;
  }

  void changePID(float newKp, float newKi, float newKd){
    //change values 
    Kp = newKp;
    Ki = newKi;
    Kd = newKd;
  }

  float getError(float curVal, float desVal){
    //find error
    return desVal - curVal;
  }

  float getP(float error){
    _p = error*Kp;  //find power based on proportioned value
    if(_p > 100){_p = 100;}
    if(_p < -100){_p = -100;}
    return _p;
  }

  float getI(float error){
    _i = (_i +error)*Ki;  //find power based on accumalated error
    if(error == 0){_i = 0;}
    return _i;
  }

  float getD(float error, float pastError){
    _d = (error - pastError)*Kd;
    return _d;
  }

  void wait(int milliseconds){
    //wait for time
    vex::this_thread::sleep_for(milliseconds);
  }

  int getOutputPower(int pctPower, float error){

    //add up all pid values
    PctPower = getP(error) + getI(error) + getD(error, pastError);
    if(PctPower > pctPower){PctPower = pctPower;}
    if(PctPower < -pctPower){PctPower = -pctPower;}
    pastError = error;
    return PctPower; 
  }


};