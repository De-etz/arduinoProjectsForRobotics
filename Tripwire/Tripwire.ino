//Ultrasonic
int trigPin = 4; //Send
int echoPin = 5; //Receive
const double C_DIGIT = 148.571428; //Conversion digit

//Wire
const int D_DIGIT = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
}

void loop() {
  //Check the tripwire
  double dist = getInches();
  Serial.println(dist);
  if (D_DIGIT-dist < 2) {
    //Keep waiting
  } else {
    //Make them regret being born
    Serial.println("^TRIGGERED");
  }
  delay(500);
}

double getInches() {
  //Ping sensor
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);

  //Waiting for response
  while (digitalRead(echoPin) != HIGH);
  
  double startTime = micros();
  while (digitalRead(echoPin) != LOW);
  double endTime = micros(); 
  double pingTime = endTime-startTime;
  return pingTime/C_DIGIT;
}

