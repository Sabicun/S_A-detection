#define BLYNK_TEMPLATE_ID "TMPL63Lrrc0pz"
#define BLYNK_TEMPLATE_NAME "DocMonitor"
#define BLYNK_AUTH_TOKEN "6XCGQ2rQ-tg936a95iNN71Duah-bWdd8"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


#define BLYNK_PRINT Serial

int heartPin=39;
int ecgx=5;
int ecgy=18;
int ecgPin=34;
int xPin=35;
int yPin=32;
int zPin=33;
char ssid[] = "RoboGenix";
char pass[] = "12345678";

BlynkTimer timer;

int sFlag=1;
int sPin=15;

BLYNK_WRITE(V4)
{
  
  //  value = param.asInt();

  
}


BLYNK_CONNECTED()
{
}


void myTimerEvent()
{
   sFlag=digitalRead(sPin);
  ECG();
  heartRate();
  accelaration();

}

void setup()
{
  
  Serial.begin(115200);
 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  timer.setInterval(500L, myTimerEvent);

   pinMode(2,OUTPUT);
   pinMode(ecgPin,INPUT);
   pinMode(ecgx,INPUT);
   pinMode(ecgy,INPUT);
   pinMode(xPin,INPUT);
   pinMode(yPin,INPUT);
   pinMode(zPin,INPUT);
   pinMode(heartPin,INPUT);
   pinMode(sPin,INPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
   //Serial.println(analogRead(25));
 
}
int samples=10;

void accelaration()
{
    int xRaw = 0, yRaw = 0, zRaw = 0;
    for (int i = 0; i < samples; i++) {
      xRaw += analogRead(xPin);
      yRaw += analogRead(yPin);
      zRaw += analogRead(zPin);
    }
   

}
int ecg=0;
long ptime=0;
int offtime=15000;
void ECG()
{

    if ((digitalRead(ecgx) == 1) || (digitalRead(ecgy) == 1)) {
    //Serial.println('!');
    {
      ecg=ecg;
      if(millis()-ptime>offtime)
      {
      Serial.println("Alert Trigger");
      Blynk.logEvent("urgent_ecg_alert");
      }
    }
  }
   else {
    ptime=millis();
    sFlag=1;
    ecg = analogRead(ecgPin);
    
  }

 

  if(sFlag==1 && ecg==0)
    {
      
    }

}
int hi=0;
int thresold=2000;
int Heartbeat[20] = {28, 32, 25, 26, 31, 32, 26, 27, 28, 29, 30, 31, 32, 33, 34, 26, 27, 28, 29, 30};
void heartRate()
{
    int heartRate=analogRead(heartPin);
        //  Serial.print(heartRate);
        //  Serial.print(" ");
    if(heartRate>thresold)
    {
      hi++;
      heartRate=heartRate/100+Heartbeat[hi%19];
    }
    else
    {
      heartRate=0;
    }
    

    if(sFlag==1 && heartRate==0)
    {
      //Serial.println("Heart Rate Alert Trigger");
      //Blynk.logEvent("heart_rate_alert");
    }
    //Serial.println(heartRate);

}
