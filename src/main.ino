#define PIRpin 7
#define ULTRASONIC_SENSOR_TRIGGER 3
#define ULTRASONIC_SENSOR_ANALOG_IN A0

int fsrreading;
#define fsrpin A1
const int state = LOW;
const int val = LOW;
const int t = 500;
#define led1 8
#define led2 9
#define led3 10
#define led4 11
#define led5 12
#define led6 13

void setup(){
  Serial.begin(9600);
  initUSsensor();
  initPIRsensor();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  Serial.println("init completed");
}

void loop(){
  testUSsensor();
  testPIRsensor();
  forcescanner();
}
void initUSsensor(){
  pinMode(ULTRASONIC_SENSOR_TRIGGER, OUTPUT);
    pinMode(ULTRASONIC_SENSOR_ANALOG_IN, INPUT);
  
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, HIGH);
    delayMicroseconds(5);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, LOW);
}
void testUSsensor(){
    int randint;
    long distanceThreshold = 50;
  	long cm, duration;
  
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_SENSOR_TRIGGER, LOW);
    
    //duration=analogRead(ULTRASONIC_SENSOR_ANALOG_IN);
    duration=pulseIn(ULTRASONIC_SENSOR_ANALOG_IN, HIGH);
    //debug
    //Serial.print(" pulseIn:");
    //Serial.print(duration);
    //Serial.println();
  
  cm=conversion(duration);  
  //debug 
    Serial.print(" Distance: ");
    Serial.print(cm);
    Serial.print("cm ");
    Serial.println();
  /*
    Serial.print(" randint = ");
    Serial.print(randint);
    Serial.println();
  */
    if (cm<distanceThreshold){
        Serial.print(" USsensor: THRESHOLD! ");
    }else{
        delayMicroseconds(10);
    }
  //delay(500);
}
long conversion(long duration){
  duration=(duration*0.034)/2;
  return(duration); //sound is 340m/s = 34ms/cm and two way trip so we half
}

void initPIRsensor(){
  pinMode(PIRpin, INPUT);
}

void testPIRsensor(){
  while (digitalRead(PIRpin)== HIGH){
  Serial.println("PIR: TRIGGERED!");
  }
}

void forcescanner(){
	fsrreading = analogRead(fsrpin);
  Serial.print("Force reading: ");
  Serial.println(fsrreading);
  
  if (fsrreading > 200) {
    digitalWrite(led1, HIGH);
  }
  else digitalWrite(led1, LOW);
  if (fsrreading > 450) {
    digitalWrite(led2, HIGH);
  }
  else digitalWrite(led2, LOW);
  if (fsrreading > 550) {
    digitalWrite(led3, HIGH);
  }
  else digitalWrite(led3, LOW);
  if (fsrreading > 650) {
    digitalWrite(led4, HIGH);
  }
  else digitalWrite(led4, LOW);
  if (fsrreading > 800) {
    digitalWrite(led5, HIGH);
  }
  else digitalWrite(led5, LOW);
  if (fsrreading > 900) {
    digitalWrite(led6, HIGH);
  }
  else digitalWrite(led6, LOW);
}
