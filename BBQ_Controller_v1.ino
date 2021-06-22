#define BLYNK_PRINT Serial

#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <math.h>
#include <PID_v1.h>
#include <analogWrite.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <esp_task_wdt.h> //Load Watchdog-Library

//Arrays for adc and temp
int* adc = new int[4];
double* temp = new double[4];

//NOTIFICATION Variables
 int meat1, meat2, meat3;
 int NOTIFY_SWITCH = 1;

//FAN & PID Variables
int FAN_SWITCH = 1, FAN_PIN = 5, fanspeed = 100;
double Setpoint = 100, Input, Output;
double Kp = 30, Ki = 240, Kd = 60;

//ADC
Adafruit_ADS1115 ads;
//PID
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//BLYNK timer
BlynkTimer timer;

//BLYNK

// TODO: Auth Token Blynk App
char auth[] = "";

// TODO: WiFi credentials
char ssid[] = "";
char pass[] = "";

//Sync with server
BLYNK_CONNECTED(){
  Blynk.syncAll();
}

void readSensor(){
  //read adc values
 adc[0] = ads.readADC_SingleEnded(0);
 adc[1] = ads.readADC_SingleEnded(1);
 adc[2] = ads.readADC_SingleEnded(2);
 adc[3] = ads.readADC_SingleEnded(3);

 //exclude limit values
 if (adc[0] > 32766 || adc[0] < 100) {adc[0] = -1;}
 if (adc[1] > 32766 || adc[1] < 100) {adc[1] = -1;}
 if (adc[2] > 32766 || adc[2] < 100) {adc[2] = -1;}
 if (adc[3] > 32766 || adc[3] < 100) {adc[3] = -1;}
 
}

void calcTemp(){
  for (int i = 0; i < 4; i++){
  if (adc[i] == -1){
    //temp 0 if out of bounds
    temp[i] = 0;} 
  else {
    
//TODDO: create formula by measured values
    temp[i] = 0.00000000000000000000000886822075290642*pow(adc[i],6) - 
          0.000000000000000000909539932982674*pow(adc[i],5) + 
          0.0000000000000365670948671432*pow(adc[i],4) - 
          0.000000000734223654859665*pow(adc[i],3) + 
          0.00000781811709378097*pow(adc[i],2) - 
          0.0463996976605886*adc[i] + 
          208.889234914568;
  }
 }
}

void controlPID(){
  Input = temp[3];
  //control pid
  myPID.Compute();
  //control fan -> FAN_SWITCH 1 or 0 to start or stop head control with button
  analogWrite(FAN_PIN, Output*4*FAN_SWITCH);
}

void readSensorTimerEvent(){

  readSensor();
  calcTemp();
  controlPID();

 //SENT VALUES TO BLYNK
 //Temp Values
 Blynk.virtualWrite(V5, temp[3]);
 Blynk.virtualWrite(V6, temp[2]); 
 Blynk.virtualWrite(V7, temp[1]); 
 Blynk.virtualWrite(V8, temp[0]); 
 //Fan Speed
 Blynk.virtualWrite(V1, Output/10.2);
 //ADC values
 Blynk.virtualWrite(V10, adc[0]);
 Blynk.virtualWrite(V11, adc[1]);
 Blynk.virtualWrite(V12, adc[2]);
 Blynk.virtualWrite(V13, adc[3]);
}

void sendNotification(){
  //push notification
  if (NOTIFY_SWITCH == 1){
    if (temp[3] >= Setpoint + 15 && Setpoint > 0) {Blynk.notify("PIT is on fire!");}
    if (temp[2] >= meat1 && meat1 > 0) {Blynk.notify("Meat 1 is ready!");}
    if (temp[1] >= meat2 && meat2 > 0) {Blynk.notify("Meat 2 is ready!");}
    if (temp[0] >= meat3 && meat3 > 0) {Blynk.notify("Meat 3 is ready!");}
  }
}

  //GET VALUES FROM BLYNK
  //Setpoint
  BLYNK_WRITE(V9){
    Setpoint = param.asDouble();
    Blynk.virtualWrite(V9, Setpoint);
  }
  //FAN SWITCH
  BLYNK_WRITE(V0){FAN_SWITCH = param.asInt();}
  //NOTIFY SWITCH
  BLYNK_WRITE(V2){NOTIFY_SWITCH = param.asInt();}
  // meat temp for notifivation
  BLYNK_WRITE(V14){meat1 = param.asInt();}
  BLYNK_WRITE(V15){meat2 = param.asInt();}
  BLYNK_WRITE(V16){meat3 = param.asInt();}
  

void setup() {
 Serial.begin(9600);
 Wire.begin();
 
 // ads.setGain(GAIN_TWOTHIRDS);// 2/3x +/- 6.144V 1bit = 0.1875mV //default
 ads.setGain(GAIN_ONE); // 1x +/- 4.096V 1bit = 0.125mV
 // ads.setGain(GAIN_TWO); // 2x +/- 2.048V 1bit = 0.0625mV
 // ads.setGain(GAIN_FOUR); // 4x +/- 1.024V 1bit = 0.03125mV
 // ads.setGain(GAIN_EIGHT); // 8x +/- 0.512V 1bit = 0.015625mV
 // ads.setGain(GAIN_SIXTEEN); // 16x +/- 0.256V 1bit = 0.0078125mV
 
  ads.begin(0x49);

  //BLYNK
  Blynk.begin(auth, ssid, pass);
  //Controlled by timer instead of loop()
  timer.setInterval(1000L, readSensorTimerEvent);
  timer.setInterval(60000L, sendNotification);

  //PID
  myPID.SetTunings(Kp, Ki, Kd); 
  myPID.SetOutputLimits(0, fanspeed*10.2);
  myPID.SetMode(AUTOMATIC);

  //Watchdog 8sec
  esp_task_wdt_init(4,true); //Init Watchdog with sec timeout and panicmode
  esp_task_wdt_add(NULL); //No special task needed
}
void loop() {

 Blynk.run();
 timer.run();
 esp_task_wdt_reset(); // Reset watchdog
}
