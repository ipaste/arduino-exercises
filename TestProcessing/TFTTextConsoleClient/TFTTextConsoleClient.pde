import processing.serial.*;

Serial port;
String output="";
String input="";

void setup() {
  background(0);
  size(500, 150);
  textFont(createFont("FixedSys", 14));
  loadSerial();
}

void draw() {
  background(0);
  noStroke();
  text("Type a line of text to send to the serial port:", 10, 20);
  fill(255, 255, 255);
  rect(10, 70, 480, 5);
  text(output, 10, 60);  
  text(input, 10, 85);
}

void loadSerial() {
  println(Serial.list()); 
  // Create object from Serial class(it depends on what device you have on your machine)
  port = new Serial(this, Serial.list()[6], 9600); 
//  port = new Serial(this, "/dev/tty.usbmodem1411", 9600);

  // Fire a serialEvent() when when a linefeed comes in to the serial port.
  port.bufferUntil('\n');
  port.write('\n');
}

// Process a line of text from the serial port.
void serialEvent(Serial p) {
  input = (port.readString());
  print("received: " + input);
}

/* 
 * Buffer a string until a linefeed is encountered 
 * then send it to the serial port.
 */
void keyPressed() {
  if (key < 255) {
    output += str(key);
    // for linefeed to end and send the output string to serial
    if (key == '\n') {
      print("sending: " + output);
      port.write(output);
      output = "";
    // for backspace to remove a character
    } else if (key == BACKSPACE && output.length() > 0) {
      if(output.length() == 1)
        output = "";
      else
        output = output.substring(0, output.length() - 2);
    }
  }
}

/*
 * For mouse left click: read content from a file and write to the screen
 * For mouse right click: clear the screen
 */ 
void mousePressed() {
  if(mouseButton == RIGHT) {
    port.write('`');
  } else {
    String fn = loadFile();
    if(fn != null){
      String lines[] = loadStrings(fn);
      for(String l: lines) {
        port.write(l+'\n');
        println("sending: " + l);
      }
    }
  }
}
  
String loadFile() {
  String loadPath = selectInput();  // Opens file chooser
  if (loadPath == null) {
    // If a file was not selected
    println("No file was selected...");
    return null;
  } else {
    // If a file was selected, print path to file
    println(loadPath);
    return loadPath;
  }
}


