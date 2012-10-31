import processing.serial.*;

Serial myPort;
int lf = 10; // linefeed
int failCnt = 0;
int successCnt = 0;

void setup() {
  setupTestGraphics();
  setupTestDevices(); // setup serial
}

void setupTestDevices() {
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600); 
}

void setupTestGraphics() {
  size(640, 480, P3D);
  lights();
  frameRate(12); 
  camera(150,150,150, 0, 0, 0, 0, 0, -1);
}

void draw() {
  PVector v = readVectorFromSerial();
  if(v != null) {
    background(0);
    drawAxisGrid();
    
    pushMatrix();
    translate(v.x, v.y, v.z);
    noStroke();
    box(10);
    popMatrix();
    stroke(204, 102, 2);
    strokeWeight(5);
    line(0, 0, 0, v.x, v.y, v.z);
  }
}


void drawAxisGrid() {
  stroke(0, 255, 25, 68);
  strokeWeight(1);
  for(int i = -120; i <= 120; i+=10) {
    for(int j = -120; j <= 120; j+=10) {
      line(i, j, 0, 120, j, 0);
      line(i, j, 0, i, 120, 0);
      line(0, i, j, 0, 120, j);
      line(0, i, j, 0, i, 120);
      line(i, 0, j, 120, 0, j);
      line(i, 0, j, i, 0, 120);
    }
  }
  color(255);
  sphere(25);
}

PVector readVectorFromSerial() {
  // read three floats from serial and form a vector to return
  // *line format from Serial: "{float1, float2, float3}"
  int bytes = myPort.available();
  if(bytes > 0) {
    String readString = myPort.readStringUntil(lf);
    try {
      println("readString != null ? " + (readString != null));
      if(readString != null && readString.length() > 2) {
        String[] values = readString.substring(readString.indexOf("{") + 1, 
          readString.indexOf("}")).split(",");
          
        float fX = float(values[0]);
        float fY = float(values[1]);
        float fZ = float(values[2]);
        println("Accelerometer readings: " + fX + ", " + fY + ", " + fZ
          + " magnitude: " + sqrt(fX*fX + fY*fY + fZ*fZ));
        successCnt++;
        
        return new PVector(fX, fY, fZ);
      }
    } catch(Exception e) {
      println("parse string error with: " + readString);
      increaseFailCount();
      e.printStackTrace();        
    }
  }
  return null; 
}


float readFloat(Serial port) {
  String s = myPort.readStringUntil(lf);
  return float(s);
}

void increaseFailCount() {
  failCnt++;
  println("failed count: " + failCnt + " Successful Count: " + successCnt);
}

