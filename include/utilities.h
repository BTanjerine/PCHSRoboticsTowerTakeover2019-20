#include <cmath>
void wait(int milliseconds) {
  // wait for time
  vex::this_thread::sleep_for(milliseconds);
}

int PIDCalculator(int limitPower, float input1, float input2, float desPoint,
                  float kp, float ki, float kd) {
  float error;
  float past_error = 0; // error from the past

  float input; // input value(sensor)
  int output;  // output value (motor power)

  float P_ = 0; // porportional output
  float I_ = 0; // integral output
  float D_ = 0; // derivative output

  input = (input1 + input2) / 2; // average of input 1 and 2
  error = desPoint - input;      // value between current and desired point

  P_ = error * kp;        // shrink error down to low number using porportions
  I_ = (I_ + error) * ki; // use integrals to make swings smoother
  D_ = (error - past_error) *
       kd; // use error rate of change to make smooth transitions

  if (error == 0) {
    I_ = 0;
  } // when there is no error reset integral out

  output = P_ + I_ + D_; // combine Outputs to make one output power

  if (output > limitPower) {
    output = limitPower;
  } // limit power to limitPower
  else if (output < -limitPower) {
    output = -limitPower;
  }

  past_error = error; // record past error

  return output; // output output power
}

int PIDCalcError(int limitPower, float error, float kp, float ki, float kd) {
  float past_error; // error from the past

  int output; // output value (motor power)

  float P_ = 0; // porportional output
  float I_ = 0; // integral output
  float D_ = 0; // derivative output

  P_ = error * kp;        // shrink error down to low number using porportions
  I_ = (I_ + error) * ki; // use integrals to make swings smoother
  D_ = (error - past_error) *
       kd; // use error rate of change to make smooth transitions

  if (error == 0) {
    I_ = 0;
  } // when there is no error reset integral out

  output = P_ + I_ + D_; // combine Outputs to make one output power

  if (output > limitPower) {
    output = limitPower;
  } // limit power to limitPower
  else if (output < -limitPower) {
    output = -limitPower;
  }

  past_error = error; // record past error

  return output; // output output power
}

// position and angle
typedef struct Pos {
  float x;
  float y;
  float Ang;
} _pos;

// polar coord
typedef struct Polar {
  float Ang;
  float radius;
} _polar;

// 2d vector
typedef struct vector {
  float x;
  float y;
} _vector;

// 2d line
typedef struct Line {
  _vector p1;
  _vector p2;
} _line;

//set polar coord to cartesian
void polarTovectors(_polar pol, _vector vec) {
  vec.x = pol.radius * cos(pol.Ang);
  vec.y = pol.radius * sin(pol.Ang);
}

//set cartesian to polar coords
void vectorTopolar(_vector vec, _polar pol) {
  pol.Ang = atan2f(vec.y, vec.x);
  pol.radius = sqrtf(vec.x * vec.x + vec.y * vec.y);
}

//find angle of line
float lineAngle(_line lin) {
  float difY = (lin.p2.y - lin.p1.y);
  float difX = (lin.p2.x - lin.p1.x);
  return atan2(difX, difY);
}

//find length of line
float lineLength(_line lin) {
  float difY = (lin.p2.y - lin.p1.y);
  float difX = (lin.p2.x - lin.p1.x);
  return sqrtf((difX * difX) + (difY * difY));
}

//find angle nearest to angle 
float nearAngle(float angle, float reference) {
  return ((reference - angle) / (2 * M_PI)) * (2 * M_PI) + angle;
}

float radToDeg(float rad) { return (rad * 180) / M_PI; }  //radians to degrees
float degToRad(float deg) { return (deg * M_PI) / 180; }  //degrees to radians
