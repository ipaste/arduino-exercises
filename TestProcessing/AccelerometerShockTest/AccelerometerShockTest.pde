import processing.serial.*;

Serial myPort;
int lf = 10; // linefeed

// Serial communication globals
int successCnt = 0; 
int failCnt = 0; 

// AM Analysis globals
Accelerometer a = new Accelerometer();

void setup() {
  setupTestGraphics();
  setupTestDevices(); // setup serial
}

void setupTestDevices() {
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600); 
}

void setupTestGraphics() {
  size(840, 480);
  lights();
  frameRate(12); 
}

void draw() {
  PVector v = readVectorFromSerial();
  
  if(v!= null) {
    a.addVector(v);  
  }
  
  if(v!= null && a.pvList.size() > 1) {
    
    background(0);
    
    a.drawDiagram();
    
    fill(255,255,0);
    text("Accelerometer: (" + v.x + ", " + v.y + ", " + v.z + ")", 15, 20);
    text("AM Period:" + a.amPeriod + "ms", 15, 35);
    text("Sqrt Diff: " + a.sqrtDiff, 15, 50);
    text("Step Start: " + a.stepStart, 15, 65);
    text("Shock Count: " + a.shockCount, 15, 80);
  } 
  
}

int DataLineLimit = 400;
String[] lines = new String[DataLineLimit]; 
int lineCnt = 0;

/* Serial Communication Methods */
PVector readVectorFromSerial() {
  // read three floats from serial and form a vector to return
  // *line format from Serial: "{float1, float2, float3}"
  int bytes = myPort.available();
  if(bytes > 0) {
    String readString = myPort.readStringUntil(lf);
    
    
    try {
      if(readString != null && readString.length() > 2) {
        String[] values = readString.substring(readString.indexOf("{") + 1, 
          readString.indexOf("}")).split(",");
          
        // save test data
        if(lineCnt < DataLineLimit) 
          lines[lineCnt] = readString.replace("\n", "");
        else if(lineCnt == DataLineLimit) {
          println("Test data file saved!");
          saveStrings("/home/tux/test_am_data.txt", lines);
        }
        lineCnt++;  
          
          
        float fX = float(values[0]);
        float fY = float(values[1]);
        float fZ = float(values[2]);
        a.amPeriod = int(values[3]); // global variable
        println("Accelerometer readings: " + fX + ", " + fY + ", " + fZ
          + " " + a.amPeriod+ " magnitude: " + sqrt(fX*fX + fY*fY + fZ*fZ));
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
