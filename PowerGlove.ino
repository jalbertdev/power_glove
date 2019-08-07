#include<Wire.h>

const int MPU_addr=0x68; int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; int maxVal=402;

double x; double y; double z;
double rightTiltMin = 20;
double rightTiltMax = 170;
double leftTiltMin = 190;
double leftTiltMax = 345;
const double slideMin = 12;
const double slideMax = 27;


void setup(){ 
  Serial.begin(9600);
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
   
} 
void loop(){ 
  
  //Slide Pot Section
  float array[4]; int i;
  for(i=0; i<4; i++) {
     array[i]=(analogRead(i) * 0.05);
  }
  if(array[0]>slideMin-2.2 && array[0]<slideMax){
    Serial.println("Slide1:"); 
  }
  if(array[1]>slideMin && array[1]<slideMax){
    Serial.println("Slide2:"); 
  }
  if(array[2]>slideMin && array[2]<slideMax){
    Serial.println("Slide3:"); 
  }
  if(array[3]>slideMin && array[3]<slideMax){
    Serial.println("Slide4:"); 
  }
  delay(100); 
  
  //Gyro Section
  z=gyroData();
  //Serial.print("\nAngleZ= "); Serial.println(z); 
  if(z>rightTiltMin && z<rightTiltMax){
    Serial.println("Right:");
  }
  else if(z>leftTiltMin && z<leftTiltMax){
    Serial.println("Left:");
  }
  else if(z>leftTiltMax || z<rightTiltMin){
    Serial.println("Flat:");
  }
  else{
    Serial.println("Out of bounds");
  }
  //Serial.println("-----------------------------------------"); 
  
  delay(100); 
}

double gyroData(){
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  return z;
}
