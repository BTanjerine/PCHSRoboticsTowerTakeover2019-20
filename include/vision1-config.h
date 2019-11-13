/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature SIG1 = vex::vision::signature (1, -2795, -2333, -2564, 7549, 9203, 8376, 7.4, 0);
vex::vision::signature SIG2 = vex::vision::signature (2, 4059, 6997, 5528, -713, -179, -446, 2.7, 0);
vex::vision::signature SIG3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision2 = vex::vision (vex::PORT2, 50, SIG1, SIG2, SIG3, SIG4, SIG5, SIG6, SIG7);
/*vex-vision-config:end*/