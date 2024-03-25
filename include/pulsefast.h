#include "FastAccelStepper.h"

//const int yaw_dirPin  =  DIR_Pins[0];
//const int yaw_stepPin =  PWM_Pins[0];

const int pr1_dirPin  =  DIR_Pins[0];
const int pr1_stepPin =  PWM_Pins[0];

const int pr2_dirPin  =  DIR_Pins[1];
const int pr2_stepPin =  PWM_Pins[1];

const int pr3_dirPin  =  DIR_Pins[2];
const int pr3_stepPin =  PWM_Pins[2];

const int pr4_dirPin  =  DIR_Pins[3];
const int pr4_stepPin =  PWM_Pins[3];

const int pr5_dirPin  =  DIR_Pins[4];
const int pr5_stepPin =  PWM_Pins[4];

const int pr6_dirPin  =  DIR_Pins[5];
const int pr6_stepPin =  PWM_Pins[5];

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *yaw = NULL;

FastAccelStepper *pr1 = NULL;

FastAccelStepper *pr2 = NULL;

FastAccelStepper *pr3 = NULL;

FastAccelStepper *pr4 = NULL;

FastAccelStepper *pr5 = NULL;

FastAccelStepper *pr6 = NULL;

void pulse_setup() {
   engine.init(1);
   
   pr1 = engine.stepperConnectToPin(pr1_stepPin);
   if (pr1) {
      pr1->setDirectionPin(pr1_dirPin);
      pr1->setAutoEnable(true);
    
      pr1->setSpeedInHz(pr_max_frequency);       
      pr1->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr2 = engine.stepperConnectToPin(pr2_stepPin);
   if (pr2) {
      pr2->setDirectionPin(pr2_dirPin);
      pr2->setAutoEnable(true);
    
      pr2->setSpeedInHz(pr_max_frequency);      
      pr2->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr3 = engine.stepperConnectToPin(pr3_stepPin);
   if (pr3) {
      pr3->setDirectionPin(pr3_dirPin);
      pr3->setAutoEnable(true);
    
      pr3->setSpeedInHz(pr_max_frequency);       
      pr3->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr4 = engine.stepperConnectToPin(pr4_stepPin);
   if (pr4) {
      pr4->setDirectionPin(pr4_dirPin);
      pr4->setAutoEnable(true);
    
      pr4->setSpeedInHz(pr_max_frequency);       
      pr4->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr5 = engine.stepperConnectToPin(pr5_stepPin);
   if (pr5) {
      pr5->setDirectionPin(pr5_dirPin);
      pr5->setAutoEnable(true);
    
      pr5->setSpeedInHz(pr_max_frequency);       
      pr5->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }

   pr6 = engine.stepperConnectToPin(pr6_stepPin);
   if (pr6) {
      pr6->setDirectionPin(pr6_dirPin);
      pr6->setAutoEnable(true);
    
      pr6->setSpeedInHz(pr_max_frequency);       
      pr6->setAcceleration(pr_max_frequency);    // 10000 steps/s²
   }
}

bool check_error(int pr){
    //active low alarm
    if(pr == 1){        
        if(digitalRead(alarm_1) == LOW){
            pr1->isRunning()? pr1->forceStop() : NP();
            errorflag = true;
            return true;
        }
        errorflag = false;
        return false;
    }
    else if(pr == 2){
        if(digitalRead(alarm_2) == LOW){
            pr2->isRunning()? pr2->forceStop() : NP();
            errorflag = true;
            return true;
        }
        errorflag = false;
        return false;
    }
    else if(pr == 3){
        if(digitalRead(alarm_3) == LOW){
            pr3->isRunning()? pr3->forceStop() : NP();
            errorflag = true;
            return true;
        }
        errorflag = false;
        return false;
    }
    else if(pr == 4){
        if(digitalRead(alarm_4) == LOW){
            pr4->isRunning()? pr4->forceStop() : NP();
            errorflag = true;
            return true;
        }
        errorflag = false;
        return false;
    }
    else if(pr == 5){
        if(digitalRead(alarm_5) == LOW){
            pr5->isRunning()? pr5->forceStop() : NP();
            errorflag = true;
            return true;
        }
        errorflag = false;
        return false;
    }
    else if(pr == 6){
        if(digitalRead(alarm_6) == LOW){
            pr6->isRunning()? pr6->forceStop() : NP();   
            errorflag = true;       
            return true;
        }
        errorflag = false;
        return false;
    }
    PRINTLINE("invalid channel error");
    errorflag = true;
    return true;
}

void pr1x()
{    
    long angle = pr1->getCurrentPosition();
    if(angle != oldangle_yaw[1]){
        PRINTLINE("Cylinder 1 step: " + String(angle));
        oldangle_yaw[1] = angle;
    }
    phase_a_ct = angle; 
    zero_movement[1] = check_error(1)?1:0;
    if(zero_movement[1] != zero_movement_old[1]){
        PRINT("Cylinder 1: ");
        PRINTLINE(zero_movement[1]?"Error":"Ok");
        zero_movement_old[1] = zero_movement[1];
    }
    
}
void pr2x()
{    
    long angle = pr2->getCurrentPosition();
    if(angle != oldangle_yaw[2]){
        PRINTLINE("Cylinder 2 step: " + String(angle));
        oldangle_yaw[2] = angle;
    }
    phase_b_ct = angle;  
    zero_movement[2] = check_error(2)?1:0;
    if(zero_movement[2] != zero_movement_old[2]){
        PRINT("Cylinder 2: ");
        PRINTLINE(zero_movement[2]?"Error":"Ok");
        zero_movement_old[2] = zero_movement[2];
    }
}
void pr3x()
{    
    long angle = pr3->getCurrentPosition();
    if(angle != oldangle_yaw[3]){
        PRINTLINE("Cylider 3 step: " + String(angle));
        oldangle_yaw[3] = angle;
    }
    phase_c_ct = angle;
    zero_movement[3] = check_error(3)?1:0;
    if(zero_movement[3] != zero_movement_old[3]){
        PRINT("Cylinder 3: ");
        PRINTLINE(zero_movement[3]?"Error":"Ok");
        zero_movement_old[3] = zero_movement[3];
    }
}
void pr4x()
{    
    long angle = pr4->getCurrentPosition();
    if(angle != oldangle_yaw[4]){
        PRINTLINE("Cylinder 4 step: " + String(angle));
        oldangle_yaw[4] = angle;
    }
    phase_d_ct = angle;
    zero_movement[4] = check_error(4)?1:0;
    if(zero_movement[4] != zero_movement_old[4]){
        PRINT("Cylinder 4: ");
        PRINTLINE(zero_movement[4]?"Error":"Ok");
        zero_movement_old[4] = zero_movement[4];
    }
}
void pr5x()
{    
    long angle = pr5->getCurrentPosition();
    if(angle != oldangle_yaw[5]){
        PRINTLINE("Cylinder 5 step: " + String(angle));
        oldangle_yaw[5] = angle;
    }
    phase_e_ct = angle;
    zero_movement[5] = check_error(5)?1:0;
    if(zero_movement[5] != zero_movement_old[5]){
        PRINT("Cylinder 5: ");
        PRINTLINE(zero_movement[4]?"Error":"Ok");
        zero_movement_old[5] = zero_movement[5];
    }
}
void pr6x()
{    
    long angle = pr6->getCurrentPosition();
    if(angle != oldangle_yaw[6]){
        PRINTLINE("Cylinder 6 step: " + String(angle));
        oldangle_yaw[6] = angle;
    }
    phase_f_ct = angle;
    zero_movement[6] = check_error(6)?1:0;
    if(zero_movement[6] != zero_movement_old[6]){
        PRINT("Cylinder 6: ");
        PRINTLINE(zero_movement[6]?"Error":"Ok");
        zero_movement_old[6] = zero_movement[6];
    }
}


void pulse_refresh(){
    pr1x();
    pr2x();
    pr3x();
    pr4x();
    pr5x();
    pr6x();
}


bool rotateMotorbyStep(int motor, int steps){    
    PRINTLINE("Stepping Servo " + String(motor) + " to " + String(steps));
    //int pulse_hz = map(speed, 0, 100, 0, yaw_max_frequency);
    if(motor == 1){
        if(check_error(1))
            return false;
        pr1->move(steps);
        return true;
    }
    else if(motor == 2){
        if(check_error(2))
            return false;
        pr2->moveTo(steps);
        return true;
    }
    else if(motor == 3){
        if(check_error(3))
            return false;
        pr3->moveTo(steps);
        return true;
    }
    else if(motor == 4){
        if(check_error(4))
            return false;
        pr4->moveTo(steps);
        return true;
    } 
    else if(motor == 5){
        if(check_error(5))
            return false;
        pr5->moveTo(steps);
        return true;
    } 
    else if(motor == 6){
        if(check_error(6))
            return false;
        pr6->moveTo(steps);
        return true;
    } 
    else{
        PRINTLINE("Motor not exist");
        return false;
    }     
}

/// @brief 
/// @param motor 
/// @param speed 
/// @param force : force motor movement/ignore error
void turn_MotorUp(int motor, int speed, bool force){    
    if(motor == 1){
        if(check_error(1))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr1->setSpeedInHz(pulse_hz);
	    pr1->runForward();
    }
    else if(motor == 2){
        if(check_error(2))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr2->setSpeedInHz(pulse_hz);
	    pr2->runForward();
    }
    else if(motor == 3){
        if(check_error(3))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr3->setSpeedInHz(pulse_hz);
	    pr3->runForward();
    }
    else if(motor == 4){
        if(check_error(4))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr4->setSpeedInHz(pulse_hz);
	    pr4->runForward();
    }
    else if(motor == 5){
        if(check_error(5))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr5->setSpeedInHz(pulse_hz);
	    pr5->runForward();
    }
    else if(motor == 6){
        if(check_error(6))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr6->setSpeedInHz(pulse_hz);
	    pr6->runForward();
    }
}

/// @brief 
/// @param motor 
/// @param speed 
/// @param force : force motor movement/ignore error
void turn_MotorDown(int motor, int speed,  bool force){
    if(motor == 1){
        if(check_error(1))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr1->setSpeedInHz(pulse_hz);
	    pr1->runBackward();
    }
    else if(motor == 2){
        if(check_error(2))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr2->setSpeedInHz(pulse_hz);
	    pr2->runBackward();
    }
    else if(motor == 3){
        if(check_error(3))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr3->setSpeedInHz(pulse_hz);
	    pr3->runBackward();
    }
    else if(motor == 4){
        if(check_error(4))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr4->setSpeedInHz(pulse_hz);
	    pr4->runBackward();
    }
    else if(motor == 5){
        if(check_error(5))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr5->setSpeedInHz(pulse_hz);
	    pr5->runBackward();
    }
    else if(motor == 6){
        if(check_error(6))
        {
            if(!force){
                return;
            }
        }
        int pulse_hz = map(speed, 0, 100, 0, pr_max_frequency);
        pr6->setSpeedInHz(pulse_hz);
	    pr6->runBackward();
    }
}

void stopMotor(int motor){
    if(motor == 1){  
        pr1->setSpeedInHz(0);
        pr1->applySpeedAcceleration();
        pr1->forceStop();
    }
    else if(motor == 2){
        pr2->setSpeedInHz(0);
        pr2->applySpeedAcceleration();
        pr2->forceStop();
    }
    else if(motor == 3){
        pr3->setSpeedInHz(0);
        pr3->applySpeedAcceleration();
        pr3->forceStop();
    }
    else if(motor == 4){
        pr4->setSpeedInHz(0);
        pr4->applySpeedAcceleration();
        pr4->forceStop();
    }
    else if(motor == 5){
        pr5->setSpeedInHz(0);
        pr5->applySpeedAcceleration();
        pr5->forceStop();
    }
    else if(motor == 6){
        pr6->setSpeedInHz(0);
        pr6->applySpeedAcceleration();
        pr6->forceStop();
    }
}


/// @brief 
void home_return(){
  if(errorflag){
    //stop all movement
    for(int i = 1; i<7; i++){
        stopMotor(i);
    }

    delay(2000);

    //return home
    for(int i = 1; i<7; i++){
        turn_MotorDown(i, 50, force);
    }

    delay(4000); //?check how long it takes to return all motors to base

    //check and initialize all errors
    bool err;
    for(int i = 1; i<7; i++){
        err += check_error(i);
    }
    PRINTLINE(err?("Motor Reset Error: ") : ("No Error: Reset Success"));
  }
}