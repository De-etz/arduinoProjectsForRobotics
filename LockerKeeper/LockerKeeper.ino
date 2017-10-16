//Ultrasonic
int trigPin = 4; //Send
int echoPin = 5; //Receive
const double C_DIGIT = 148.571428; //Conversion digit

//Wire
const int D_DIGIT = 80;

//Motor
const int port = 3;
const int maxForward = 254;
const int neutral = 190; //187 to 190
const int maxBackward = 155;
const int SLOW = 190;
const int FAST = 195;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //Trig
  pinMode(echoPin, INPUT); //Echo
  pinMode(port, OUTPUT); //Motor
}

void loop() {
  //Check the tripwire
  double dist = getInches();
  Serial.println(dist);
  if (D_DIGIT-dist < 2) {
    //Keep waiting
    analogWrite(port, SLOW);
  } else {
    //Make them regret being born
    analogWrite(port, FAST);
    Serial.println("^TRIGGERED");
    delay(2000);
  }
}

double getDistance() {
  HashMap<Double, Integer> readings = new HashMap<Double, Integer>(); //Distance, count
  
  
  Timer timer = new Timer(.1);
  //Build HashMap
  while (!timer.isDone()) {
    double distance = ((int)(sensor1.getRangeInches()*100)/100.0);
    if (readings.containsKey(distance)) {
      readings.replace(distance, readings.get(distance)+1);
    } else {
      readings.put(distance, 1);
    }
  }
  double defDistance = 0;
  int maxOccurences = 0;
  for (Double distance : readings.keySet()) {
    if (readings.get(distance) > maxOccurences) {
      defDistance = distance;
      maxOccurences = readings.get(distance);
    }
  }
  if (defDistance > 150) {
    return -1;
  }
  return defDistance;
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

