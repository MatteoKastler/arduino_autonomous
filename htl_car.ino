/*Creator: Matteo Kastler
 * code for HTlCar(motorControl, smooth curves)
 * speed < 60 --> motor stops
 * 
 */
#define LPIN1 2
#define LPIN2 3
#define RPIN1 4
#define RPIN2 5
#define CUTOFF 70
double i;
void setup() {
  Serial.begin(9600);
  pinMode(LPIN1, OUTPUT);
  pinMode(LPIN2, OUTPUT);
  pinMode(RPIN1, OUTPUT);
  pinMode(RPIN2, OUTPUT);

  //curve(0.4, 200);

}

void loop() {
  i = (millis()/10000.0);
  Serial.println(i);
  curve(i, 255);

}

void motorR(int speed){
  speed = abs(speed)>70?speed:(speed<0?-70:70);
  digitalWrite(LPIN1, speed<0?LOW:HIGH);
  analogWrite(LPIN2, speed<0?abs(speed):255-speed);
}
void motorL(int speed){
   speed = abs(speed)>70?speed:(speed<0?-70:70);
  digitalWrite(RPIN1, speed<0?LOW:HIGH);
  analogWrite(RPIN2, speed<0?abs(speed):255-speed);
}

//factor -1 - 1, determines rate of curve
void curve(double factor, int speed){
  factor = abs(factor)>1?(factor<0?-1:1):factor;
  int calcSpeed = (int)(1-(abs(2*sqrt(factor))))*speed);
  calcSpeed = calcSpeed<CUTOFF? speed : calcSpeed;
  motorL(factor<0?calcSpeed : speed);
  motorR(factor<0?speed :calcSpeed);
}

void stop(){
  digitalWrite(LPIN1, LOW);
  digitalWrite(LPIN2, LOW);
  digitalWrite(RPIN1, LOW);
  digitalWrite(RPIN2, LOW);
}
