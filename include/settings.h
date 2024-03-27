
#define no_alarm false

#define i60k 60000
#define i100k 100000
#define i200k 200000

unsigned long previousMillis = 0;  // will store the last time the LED was updated
unsigned long interval = 0;  // interval at which to blink (initialized to 0 for first run)
unsigned long buzzerPreviousMillis = 0;
unsigned long buzzerInterval = 0;

#define full_step 1000  //number of full cylinder steps
#define LED 15
#define buzzerPin 26

#define i_button 5
#define boot_button 0

#define alarm_1 35
#define alarm_2 34
#define alarm_3 39
#define alarm_4 36
#define alarm_5 17
#define alarm_6 16

#define CON_PUL_1 21
#define CON_DIR_1 19

#define CON_PUL_2 32
#define CON_DIR_2 33

#define CON_PUL_3 25
#define CON_DIR_3 27

#define CON_PUL_4 12
#define CON_DIR_4 14

#define CON_PUL_5 2
#define CON_DIR_5 13

#define CON_PUL_6 18
#define CON_DIR_6 4

const uint32_t PWM_Pins[]   = { CON_PUL_1, CON_PUL_2, CON_PUL_3, CON_PUL_4, CON_PUL_5, CON_PUL_6 };
const uint32_t DIR_Pins[]   = { CON_DIR_1, CON_DIR_2, CON_DIR_3, CON_DIR_4, CON_DIR_5, CON_DIR_6 };

const int yaw_max_frequency = 20000; //30khz ==> max rpm for yaw
const int pr_max_frequency = i200k; //100khz ==> max rpm for PRs
const int accelMax = yaw_max_frequency; //accel /decel

long oldangle_yaw[7];// =   { 0, 0, 0, 0 }; //oldangle = 0.0f
float phase_a_ct, oldphase_a_ct, phase_b_ct, oldphase_b_ct, phase_c_ct, oldphase_c_ct, phase_d_ct, phase_e_ct, phase_f_ct = 0.00f;

int zero_movement[7];
int zero_movement_old[7];
bool errorflag = true; //start with error flag on and reset automatically after initialization
bool force = true;