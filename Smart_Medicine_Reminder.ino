#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int buzzerPin = 10;

// Set reminder time here..
const int reminderHour = 13;
const int reminderMinute =43;
const int reminderSecond =0;
bool reminderDone = false;
bool reminderActive = false;

unsigned long previousMillis = 0;
bool buzzerState = false;

void setup()
{
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  if (!rtc.begin())
  {
    Serial.println("RTC NOT FOUND");
    while (1);
  }

  Serial.println("Medicine Reminder Started");
}

void loop()
{
  DateTime now = rtc.now();

  Serial.print("Time : ");
  if(now.hour()<10) Serial.print("0");
  Serial.print(now.hour());
  Serial.print(":");
  if(now.minute()<10) Serial.print("0");
  Serial.print(now.minute());
  Serial.print(":");
  if(now.second()<10) Serial.print("0");
  Serial.println(now.second());

  // Reset every midnight
  if(now.hour()==0 && now.minute()==0 && now.second()==0)
  {
    reminderDone = false;
  }

  // Start reminder
  if(now.hour()==reminderHour &&
     now.minute()==reminderMinute &&
     now.second()==reminderSecond &&
     !reminderDone)
  {
    reminderActive = true;
    reminderDone = true;

    Serial.println("***** TAKE MEDICINE *****");
  }

  // Buzzer ON/OFF
  if(reminderActive)
  {
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= 500)
    {
      previousMillis = currentMillis;

      buzzerState = !buzzerState;

      digitalWrite(buzzerPin, buzzerState);
    }
  }

  delay(500);
}