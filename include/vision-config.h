/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature SIG_1 = vex::vision::signature (1, -5243, -3121, -4182, -2717, -1561, -2139, 3.2, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, 6169, 7573, 6871, -2645, -2103, -2374, 2.9, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT5, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/