//Motor
const int port = 3;
const int maxForward = 254;
const int neutral = 190; //187 to 190
const int maxBackward = 155;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(port, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {    
    int value = Serial.parseInt();
    analogWrite(port, value);
  }
}
