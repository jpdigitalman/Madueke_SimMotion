

/**
 * @brief 
 * 
 */
void ledFlash();
void buzzBeep();

void initPins(){
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);

    pinMode(i_button, INPUT_PULLUP); //check
    pinMode(boot_button, INPUT_PULLUP); //check

    //Alarm input means no movement allowed
    //Low Active
    pinMode(alarm_1, INPUT);
    pinMode(alarm_2, INPUT);
    pinMode(alarm_3, INPUT);
    pinMode(alarm_4, INPUT);
    pinMode(alarm_5, INPUT);
    pinMode(alarm_6, INPUT);

    pinMode(CON_PUL_1, INPUT);
    pinMode(CON_PUL_2, INPUT);
    pinMode(CON_PUL_3, INPUT);
    pinMode(CON_PUL_4, INPUT);
    pinMode(CON_PUL_5, INPUT);
    pinMode(CON_PUL_6, INPUT);

    pinMode(CON_DIR_1, INPUT);
    pinMode(CON_DIR_2, INPUT);
    pinMode(CON_DIR_3, INPUT);
    pinMode(CON_DIR_4, INPUT);
    pinMode(CON_DIR_5, INPUT);
    pinMode(CON_DIR_6, INPUT);
}

void initSerial(){
    Serial.begin(115200);  
    delay(250);
    Serial.println("SimMotion Startup..");
}

void ledFlash() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    interval = random(500, 2000);
    digitalWrite(LED, !digitalRead(LED));
  }
}

void buzzBeep(){
  unsigned long currentMillis = millis();
  if (currentMillis - buzzerPreviousMillis >= buzzerInterval) {
    buzzerPreviousMillis = currentMillis;
    buzzerInterval = random(500, 5000);  // 

    // Activate the buzzer for a short duration
    digitalWrite(buzzerPin, HIGH);
    delay((int)buzzerInterval);  //
    digitalWrite(buzzerPin, LOW);
  }
}

void NP(){

}
