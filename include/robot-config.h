#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

//initialize robot subsystems
#include "pidcontrol.h"


using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor RgtArm;
extern motor LftArm;
extern motor swivel;
extern motor RgtRoller;
extern motor LftRoller;
extern motor RgtDrive;
extern motor LftDrive;
extern motor MidDrive;
extern pot arm_pot;
extern gyro roboGyro;
extern encoder rgtEnc;
extern encoder lftEnc;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );