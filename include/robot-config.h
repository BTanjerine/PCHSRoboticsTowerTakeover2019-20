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
extern encoder bckEnc;
extern controller Controller1;
extern signature Vision__SIG_1;
extern signature Vision__SIG_2;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern signature Vision2__SIG_1;
extern signature Vision2__SIG_2;
extern signature Vision2__SIG_3;
extern signature Vision2__SIG_4;
extern signature Vision2__SIG_5;
extern signature Vision2__SIG_6;
extern signature Vision2__SIG_7;
extern vision Vision2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );