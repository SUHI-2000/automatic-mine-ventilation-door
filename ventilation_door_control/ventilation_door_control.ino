float sensor = A0;  //define PIR sensor 1
float sensor2 = A1;
float sensor3 = A5;
float sensor4 = A3;
float sensor5 = A4;

int ir1 = 7;  //define IR sensor 2
int ir2 = 8;

int relay1 = 13;  //define relay module 1
int relay2 = 12;              

int buzzer = 4; //define buzzer

float sum = 0;  
float val, val2, val3, val4, val5 = 0;  // variable to store the PIR sensor status (value)
int val6, val7 = 1; // variable to store the IR sensor status (value)

void setup() {
  pinMode(sensor, INPUT);     // initialize PIR sensor 1 as an input
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);

  pinMode(ir1, INPUT);     // initialize IR sensor 1 as an input
  pinMode(ir2, INPUT);
  
  pinMode(relay1, OUTPUT);    // initialize IR sensor 1 as an input
  pinMode(relay2, OUTPUT);

  pinMode(4, OUTPUT);   // initialize buzzer

  Serial.begin(9600);        // initialize serial

  digitalWrite(relay1, LOW);    //Door initial state close
  digitalWrite(relay2, LOW);    //Initiallly Red Bulb will be in on status
}

void loop(){

  val = analogRead(sensor);   // read PIR sensor 1 value
  val2 = analogRead(sensor2);
  val3 = analogRead(sensor3);   
  val4 = analogRead(sensor4);
  val5 = analogRead(sensor5);   
  
  val6 = digitalRead(ir1);   // read IR sensor 1 value
  val7 = digitalRead(ir2);

  float voltage = val * (5.0 / 1023.0);   //calculate the voltage input from PIR sensor 1
  float voltage2 = val2 * (5.0 / 1023.0);
  float voltage3 = val3 * (5.0 / 1023.0);
  float voltage4 = val4 * (5.0 / 1023.0);
  float voltage5 = val5 * (5.0 / 1023.0);
  float sum = (voltage + voltage2 + voltage3 + voltage4 + voltage5);  //calculate total voltage from all PIR sensors
  
  Serial.print(voltage);    //check PIR sensor 1 status in serial monitor
  Serial.print("      ");
  Serial.print(voltage2);
  Serial.print("      ");
  Serial.print(voltage3);
  Serial.print("      ");
  Serial.print(voltage4);
  Serial.print("      ");
  Serial.print(voltage5);
  Serial.print("      ");
  Serial.println(sum);

  if (val6 == LOW || val7 == LOW){      // If any obstacles are found under the door, door will open and buzzer will be alarmed
    digitalWrite(relay1, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
  }
  else if (sum > 1){            // If any pir of the sensor dtects motion
    digitalWrite(relay1, HIGH);   // Door will open
    delay(4000);   // After 15s (Time preiod for fully open the door) 
    digitalWrite(relay2, HIGH);     // Green Bulb Signal will turn on
    delay(50);
  }
  else{                             //Otherwise
    digitalWrite(relay1, LOW);      //Door will close
    digitalWrite(relay2, LOW);      //Red Bulb signal will turn on
    delay(1000);
    digitalWrite(buzzer, LOW);      //Buzzer will turn off
    delay(500);
  }
}