#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
//#include <Ethernet.h>
//#include <BlynkSimpleEthernet.h>

#define echoPin1 15 //Echo Pin
#define trigPin1 13 //Trigger Pin // NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO
#define BLYNK_PRINT Serial


WidgetLCD lcd(V1);
Servo myserv1, myserv2;

long dur1, dist1; //waktu untuk kalkulasi jarak
int kond = 0, n_bibit = 0;
int bb = 5, ba = 12;//batas dia detect lubang
char auth[]="86p3cYxEv5hBawX3QtokOeDJMMmbuHeh";
char ssid[]="LUNAG55"; //nama wifi
char pass[]=""; //password wifi


void setup() {
  Serial.begin (9600); //inisialiasasi komunikasi serial
  //deklarasi pin
  myserv1.attach(14);
  myserv2.attach(12);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  Blynk.begin(auth,ssid,pass);
}

void loop() {
  Blynk.run();
  lcd.clear();
  char n[]="jml bibit";
  Blynk.virtualWrite(V1, n);
  lcd.print(0,0,n);
  Blynk.virtualWrite(V1,n_bibit);
  lcd.print(0,1,n_bibit);
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  dur1 = pulseIn(echoPin1, HIGH);

  dist1 = dur1 / 58.2;//1 cm dibutuhkan waktu 58 µs
  Serial.print(dist1);
  Serial.print("  ");
  Serial.print(n_bibit);
  Serial.print("  ");
  Serial.println(kond);
  
  if (dist1 >= bb && kond == 1) {
    myserv1.write(180);
    myserv2.write(180);
    delay(1000);
    myserv1.write(0);
    myserv2.write(0);
    n_bibit += 1;
    kond = 0;
    delay(1000);
    
  }
  if (dist1 <= ba) {
    kond = 1;
  }
  delay(100);
}
