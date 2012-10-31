

//Analog read pins
const unsigned char xPin = 0;
const unsigned char yPin = 1;
const unsigned char zPin = 2;

float xRead = 0;
float yRead = 0;
float zRead = 0;
//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
float xminVal = 204;
float xmaxVal = 305;
float yminVal = 204;
float ymaxVal = 305;
float zminVal = 207;
float zmaxVal = 311;

float xAng = 0;
float yAng = 0;
float zAng = 0;
 
float FTX=0;
float FTY=0;
float FTZ=0;
float a=0.3;
 
//to hold the caculated values
double x;
double y;
double z;
 
void valueprint()
{
  Serial.print(xRead);
  Serial.print('\t');
  Serial.print(yRead);
  Serial.print('\t');
  Serial.println(zRead);
}
 
float map_new(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
} 
 
void outputdata()
{
  Serial.print("xAng: ");
  Serial.print(xAng);
  Serial.print(" | yAng: ");
  Serial.print(yAng);
  Serial.print(" | zAng: ");
  Serial.println(zAng);
}

void writeAcceloData() {
  Serial.print("{");
  Serial.print(xRead);
  Serial.print(",");
  Serial.print(yRead);
  Serial.print(",");
  Serial.print(zRead);
  Serial.println("}");
  Serial.flush();
}

void writeForceData()
{
  Serial.print("{");
  Serial.print(xAng);
  Serial.print(",");
  Serial.print(yAng);
  Serial.print(",");
  Serial.print(zAng);
  Serial.println("}");
  Serial.flush();
}

void write3DData(float x, float y, float z)
{
  Serial.print("{");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println("}");
  Serial.flush();
}

void setup()
{
  Serial.begin(9600);
  FTX=analogRead(xPin);
  FTY=analogRead(yPin); 
  FTZ=analogRead(zPin);
}
 
void loop(){
 
  //read the analog values from the accelerometer
  xRead = analogRead(xPin);
  yRead = analogRead(yPin);
  zRead = analogRead(zPin);
 
  xRead=a*xRead+(1-a)*FTX;
  yRead=a*yRead+(1-a)*FTY;
  zRead=a*zRead+(1-a)*FTZ;
  FTX=xRead;
  FTY=yRead;
  FTZ=zRead;
 
  //convert read values to degrees -90 to 90 - Needed for atan2
  xAng = map_new(xRead, xminVal, xmaxVal, -90, 90);
  yAng = map_new(yRead, yminVal, ymaxVal, -90, 90);
  zAng = map_new(zRead, zminVal, zmaxVal, -90, 90);
 
  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -π to π (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  //Output the caculations
  writeForceData(); // write to receiver
//  outputdata();
  //valueprint();
 
  delay(100);//just here to slow down the serial output - Easier to read
}
