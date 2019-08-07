import processing.serial.*;
import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import javax.swing.KeyStroke;
Serial MyPort;                                
String KeyString = "";
void setup()
{
  size(700, 500);
  MyPort = new Serial(this, "COM7", 9600);// My Arduino is on COM3. Enter the COM on which your Arduino is on.
  MyPort.bufferUntil('\n');
  delay(1000);
}
void draw(){//Not really necessary
  background(0, 0, 0);
  fill(255, 0, 0);
  text("Press any key", 100, 175);
}
void serialEvent(Serial MyPort)throws Exception {
  try{
   KeyString = MyPort.readStringUntil('\n');
   KeyString = KeyString.substring(0, KeyString.indexOf(':'));//The string is split. the whole string leaving the colon is taken
   System.out.println(KeyString);//prints the serial string for debugging purpose
   Robot Arduino = new Robot();//Constructor of robot class
   switch(KeyString){
     case "Left" :
       Arduino.keyPress(KeyEvent.VK_A);//presses up key.
       Arduino.delay(100);
       Arduino.keyRelease(KeyEvent.VK_A);//releases up key
       break;     
     case "Right" :
       Arduino.keyPress(KeyEvent.VK_D);
       Arduino.delay(100);
       Arduino.keyRelease(KeyEvent.VK_D);      
       break;
     case "Flat" :
       break;
     case "Slide1" : //spacebar
       Arduino.keyPress(KeyEvent.VK_SPACE);
       Arduino.delay(50);
       Arduino.keyRelease(KeyEvent.VK_SPACE);      
       break;
     case "Slide2" : //e
       Arduino.keyPress(KeyEvent.VK_E);
       Arduino.delay(50);
       Arduino.keyRelease(KeyEvent.VK_E);      
       break;
     case "Slide3" : //r
       Arduino.keyPress(KeyEvent.VK_R);
       Arduino.delay(50);
       Arduino.keyRelease(KeyEvent.VK_R);      
       break;
     case "Slide4" : //t
       Arduino.keyPress(KeyEvent.VK_T);
       Arduino.delay(50);
       Arduino.keyRelease(KeyEvent.VK_T);      
       break;
     
   }
  }
  catch(Exception e){
    
  }
}
