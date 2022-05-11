              //Code by Marcin Jankowski and Kacper Wierciński


#include <QTRSensors.h>



// Parametry czujników odbiciowych
const uint8_t Num_sensors = 6; // Liczba czujników
uint16_t sensorValues[Num_sensors]; // Wartości czujników

QTRSensors qtr;

// Parametry regulatora PD
double kp = 0.5;
double kd = 1;
double pv = 0;
double error = 0;
double lastError = 0;

// Parametry sterowania silnikami
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9;
int BluetoothData;  
int follower_speed = 100;


// Motor 2
int dir1PinB = 5;
int dir2PinB = 4;
int speedPinB = 10;

int d6 = 6;
int d7 = 7;


void setup() {
  
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, Num_sensors);
  qtr.setEmitterPin(12);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);

for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
  
  
  Serial.begin(9600);  
                   

 for (uint8_t i = 0; i < Num_sensors; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t i = 0; i < Num_sensors; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
  
}

void loop() {
uint16_t position = qtr.readLineBlack(sensorValues);

for (uint8_t i = 0; i < Num_sensors; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print("|");
  }
  Serial.println(position);

  delay(250);


             
    
   BluetoothData=Serial.read();             //przypisz zmiennej BluetoothData odczytane dane z modułu
   
   if(BluetoothData=='1')                      //jeżeli odebrane dane to 1
      {  
       forward();
      }
   
   if(BluetoothData=='0')                      //jeżeli odebrane dane to 0
      {                  
       stop1();      
      }
if(BluetoothData=='2')                      //jeżeli odebrane dane to 2
      {                  
       backward();      
      }
    if(BluetoothData=='3')                      //jeżeli odebrane dane to 3
      {                  
       turnleft();      
      }
       if(BluetoothData=='4')                      //jeżeli odebrane dane to 4
      {                  
       turnright();      
      }
  }






void forward(){
  analogWrite(speedPinA, follower_speed);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  analogWrite(speedPinB, follower_speed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void backward(){
  analogWrite(speedPinA, follower_speed);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
  analogWrite(speedPinB, follower_speed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

}

void stop1(){
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
void turnleft() {
  analogWrite(speedPinA, follower_speed);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  analogWrite(speedPinB, follower_speed);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
}
void turnright() {
  analogWrite(speedPinB, follower_speed);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
  analogWrite(speedPinA, follower_speed);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

}



















      
