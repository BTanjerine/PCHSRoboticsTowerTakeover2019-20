/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature SIG_1 = vex::vision::signature (1, -3019, -2683, -2851, 9577, 10327, 9952, 11, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, 4117, 4969, 4544, -479, -117, -298, 5.3, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision = vex::vision (vex::PORT10, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/