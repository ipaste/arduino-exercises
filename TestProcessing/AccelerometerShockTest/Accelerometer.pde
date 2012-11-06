

// class for accelerometer monitor
class Accelerometer {

  // AM Analysis globals
  public ArrayList pvList = new ArrayList();
  public int amPeriod = 0; // period between am readings
  public float SHOCK_Threshold = 5;
  public float sqrtDiff = 0;
  public boolean stepStart = false;
  public int shockCount = 0;
  public int listLimit = 30;
  public int unitN = 3; // count every N unit, under list limit 
  
  Accelerometer() {
    
  }
  
  void addVector(PVector p) {
    pvList.add(p);
    if(pvList.size() > listLimit) {
      pvList.remove(0);
    } 
    
    
    float sqrtDiff = a.getLastDeltaDistance();
    if(sqrtDiff > a.SHOCK_Threshold) {
      if(a.stepStart) a.shockCount++;
      a.stepStart = !a.stepStart;
    }
  }
  
  PVector getCurrentV() {
    return (PVector)pvList.get(pvList.size() - 1);
  }
  
  float getDeltaDistance(int i, int j) {
    if(pvList.size() > unitN) {
      PVector v1 = (PVector)pvList.get(i);
      PVector v2 = (PVector)pvList.get(i - unitN + 1);
      return sqrt(pow(v2.x-v1.x, 2) + pow(v2.y-v1.y, 2) + pow(v2.z-v1.z, 2));
    } else {
      return 0;
    }
  }
  
  float getLastDeltaDistance() {
    return getDeltaDistance(pvList.size() - 1, pvList.size() - 2);
  }
  
  void drawDiagram() {
    int linePosY = 140;
    int barBottomY = 130;
    int barWidth = 30;
    int barMargin = 10;
    
    // separator
    stroke(255, 255, 255);
    line(20, linePosY, 420, linePosY);
    line(20, 160+linePosY, 420, 160+linePosY);
    line(20, 320+linePosY, 420, 320+linePosY);
    
    // raw force value
    noStroke();
    fill(0, 128, 25);
    int columns = pvList.size();
    for(int i = pvList.size() - 1; i > unitN - 1 ; i-=unitN) {
      PVector v2 = (PVector)pvList.get(i);
      PVector v1 = (PVector)pvList.get(i-unitN);
      
      float x = map(v2.x - v1.x, -50, 50, 0, 120);
      float y = map(v2.y - v1.y, -50, 50, 0, 120);
      float z = map(v2.z - v1.z, -50, 50, 0, 120);
      int bottomLeftX = 420 - (barWidth + barMargin)*(columns - i)/unitN;
      rect(bottomLeftX, barBottomY - x, barWidth, x);
      rect(bottomLeftX, 160+barBottomY - y, barWidth, y);
      rect(bottomLeftX, 320+barBottomY - z, barWidth, z);
      
    }    
    
  }
  
}
