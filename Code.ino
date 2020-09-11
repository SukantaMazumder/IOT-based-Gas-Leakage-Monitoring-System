#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "*****"; //from blynk app
char ssid[] = "*****"; //your wifi ssid
char pass[] = "*****"; //your wifi password


int buzzer = D2;
int smokeA0 = A0;
int led_r1 = D4;
int led_r2 = D5;
int led_r3 = D6;
int led_g = D7;
int Gas_Valve = D8;
int count = 0;
SimpleTimer timer;

int sensorThres = 700;

void setup() {
  
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(Gas_Valve, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSensorData);
  Serial.begin(9600);
}

void loop() {
  timer.run();
  Blynk.run();

}

void getSensorData()
{
  int analogSensor = analogRead(smokeA0);
  Blynk.virtualWrite(V9, analogSensor);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  if (analogSensor > sensorThres)
  {
    count++;
    int x = count;
    if (x >= 1 && x <= 2)
    {
      digitalWrite(led_r1, HIGH);
      digitalWrite(led_r2, LOW);
      digitalWrite(led_r3, LOW);
      digitalWrite(led_g,  LOW);
      digitalWrite(Gas_Valve, LOW);

    }

    else if (x > 2)
    {
      digitalWrite(led_r1, HIGH);
      digitalWrite(led_r2, HIGH);
      digitalWrite(led_r3, HIGH);
      digitalWrite(led_g,  LOW);
      digitalWrite(Gas_Valve, HIGH);
      tone(buzzer, 1000, 300);
      Blynk.notify("Gas Leakage Detected");
    }
  }
  else
  {
 
    digitalWrite(led_r1, LOW);
    digitalWrite(led_r2, LOW);
    digitalWrite(led_r3, LOW);
    digitalWrite(led_g,  HIGH);
    noTone(buzzer);
    digitalWrite(Gas_Valve, LOW);

  }
  delay(100);
}
