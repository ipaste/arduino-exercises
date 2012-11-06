
String[] lines;
float[] amXReads;
float[] amYReads;
float[] amZReads;
int[] amPeriods;
int amCount;

float xStats[] = new float[4]; // max X, min X, max dX, min dX
float yStats[] = new float[4]; // max Y, min Y, max dY, min dY
float zStats[] = new float[4]; // max Z, min Z, max dZ, min dZ

float readScale = 100;
float dReadScale = 50;

float maxSqrtDiff = -500; // to detect the max Square Root Difference
float minSqrtDiff = 500; // to detect the min Square Root Difference
float[] sqrtDiffs;

/* two inflection points makes a step */

void setup() {
  loadAMReads();
  
  size(800, 600);
  // section x(20, 420) y(0, 200) is for X stats
  // section x(20, 420) y(200, 400) is for Y stats
  // section x(20, 420) y(420, 600) is for z stats
  noLoop();
}

void draw() {
  background(0);
  drawSectionSeparator();
  drawLines(amXReads, 10, 0, xStats);
  drawLines(amYReads, 10, 200, yStats);
  drawLines(amZReads, 10, 400, zStats);
  printStats();
}

void drawSectionSeparator() {
  stroke(128, 255, 128, 86);
  line(0, 200, 420, 200);
  line(0, 400, 420, 400);
  line(420, 0, 420, 600);
}

void printStats() {
  fill(255);
  text("Max Sqrt Diff: " + maxSqrtDiff, 430, 15);
  text("Min Sqrt Diff: " + minSqrtDiff, 430, 30);
  
  // look for inflection counts
  int unitN = 3;
  int inflectCnt = 0;
  for(int i = unitN; i < amCount - 1; i+=unitN) {
    if( (amXReads[i+unitN] - amXReads[i])*(amXReads[i] - amXReads[i-unitN]) < 0  
        && sqrtDiffs[i] > 5) {
      inflectCnt++;
      println("inflection found at " + i);
    }
  }
  text("Inflection Counts: " + inflectCnt, 430, 45);
}

void drawLines(float[] reads, int x, int y, float[] stats) {
  int axisY = 100; // the place of the axis
  // initial limits
  float maxRead = -500; 
  float minRead = 500;
  float maxdRead = -500;
  float mindRead = 500;
  
  stroke(255);
  line(x, y+axisY, x+400, y+axisY);
  for(int i = 1; i < amCount; i++) {
    float read1 = map(reads[i-1], -1*readScale, readScale, -80, 80);
    float read2 = map(reads[i], -1*readScale, readScale, -80, 80);
    
    // raw line
    stroke(255, 68, 51);
    strokeWeight(2);
    line(x + i-1, y + axisY - read1, x + i, y + axisY - read2);
    maxRead = max(reads[i-1], reads[i], maxRead);
    minRead = min(reads[i], reads[i], minRead);
    
    // delta line
    stroke(68, 51, 255);
    if(i > 1) {
      float dRead1 = map(reads[i-1]-reads[i-2], -1*dReadScale, dReadScale, -80, 80);
      float dRead2 = map(reads[i]-reads[i-1], -1*dReadScale, dReadScale, -80, 80);
      line(x + i-1, y + axisY - dRead1, x + i, y + axisY - dRead2); 
    }
    maxdRead = max(reads[i] - reads[i-1], maxdRead);
    mindRead = min(reads[i] - reads[i-1], mindRead);
    
    
    // sqrt difference bar of the vector
    sqrtDiffs[i-1] = squareDifference(i, i-1);
    stroke(255,255,128, 128);
    strokeWeight(1);
    line(x + i-1, y + axisY - map(sqrtDiffs[i-1], 0, 100, 0, 80), x + i, y + axisY);
    maxSqrtDiff = max(maxSqrtDiff, sqrtDiffs[i]);
    minSqrtDiff = min(minSqrtDiff, sqrtDiffs[i]);
  }
  
  fill(255);
  text("Max : " + maxRead, x + 260, y + 15);
  text("Min : " + minRead, x + 260, y + 30);
  text("Max Delta: " + maxdRead, x + 260, y + 45);
  text("Min Delta: " + mindRead, x + 260, y + 60);
}

float squareDifference(int i, int j) {
  float dX = amXReads[i] - amXReads[j];
  float dY = amYReads[i] - amYReads[j];
  float dZ = amZReads[i] - amZReads[j];
  
  return sqrt(pow(dX, 2) + pow(dY, 2) + pow(dZ, 2));
}

void loadAMReads() {
  lines = loadStrings("/home/tux/test_am_data.txt");
  amXReads = new float[lines.length];
  amYReads = new float[lines.length];
  amZReads = new float[lines.length];
  amPeriods = new int[lines.length];
  sqrtDiffs = new float[lines.length];
  
  amCount = 0;
  for(String s: lines) {
    try {
      if(s.length() > 1 && s.startsWith("{")) {
        String[] reads = s.substring(s.indexOf("{") + 1, 
          s.indexOf("}")).split(",");
        amXReads[amCount] = float(reads[0]);
        amYReads[amCount] = float(reads[1]);
        amZReads[amCount] = float(reads[2]);
        amPeriods[amCount] = int(reads[3]);
        
        amCount++;
      } else {
        println("Unrecognized line: " + s);
      }
    } catch(Exception e) {
      println("Error in string: " + s);
      e.printStackTrace();
    }
  }
}



