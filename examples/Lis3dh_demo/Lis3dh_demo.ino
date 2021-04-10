
 /*   =================================================================================
 *         Operating mode                       ||   CTRL_REG1[3]     ||  CTRL_REG4[3]
 *                                              ||    (LPen bit)      ||  (HR bit)
 *   ==================================================================================
 *   Low-power mode(8-bit data output)          ||   1                ||  0
 *   Normal mode(10-bit data output)            ||   0                ||  0
 *   High-resolution mode(12-bit data output)   ||   0                ||  1
 *     Not allowed                              ||   1                ||  1
 *   =================================================================================
 */
 

#include <Lis3dh.h>

Lis3dh Accel;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bool state = Accel.begin(0x19);
  if(!state)  Serial.print("Failure! Device Id not matched ");    
  else Serial.println("Accelorometer Successfuly Connected");


  
  //******************************* dEVICE ID *******************************// 
  uint8_t temp = Accel.REG_read(Wai_Address);
  Serial.print("Accelerometer Address : 0x"); 
  Serial.println(temp,HEX); 
  //******************************* SET RANGE *******************************//  
  Accel.setRange(LIS3DH_RANGE_2_G);
  uint8_t range = Accel.getRange();
  if (range == LIS3DH_RANGE_2_G)  Serial.println("LIS3DH_RANGE_2_G"); //lsb_value = 4;      
  else if (range == LIS3DH_RANGE_4_G) Serial.println("LIS3DH_RANGE_4_G");//lsb_value = 8;            //8*(x/64000) // 8,000 MilliGs / 65,535 = 0.122
  else if (range == LIS3DH_RANGE_8_G) Serial.println("LIS3DH_RANGE_8_G");//lsb_value = 16;
  else if (range == LIS3DH_RANGE_16_G)  Serial.println("LIS3DH_RANGE_16_G");//lsb_value = 48;
  
  //******************************* SET Operating MODE / Table. 10  *******************************//  

  Accel.setMode(LIS3DH_NORMAL_MODE_10_BIT);
  temp = Accel.getMode();
  //Serial.println(temp,BIN); 
  if (temp == LIS3DH_NORMAL_MODE_10_BIT )  Serial.println("LIS3DH_NORMAL_MODE_10_BIT");
  else if (temp == LIS3DH_HIGH_RESOLUTION_MODE_12_BIT )  Serial.println("LIS3DH_HIGH_RESOLUTION_MODE_12_BIT"); 
  else if (temp == LIS3DH_LOW_POWER_MODE_8_BIT )  Serial.println("LIS3DH_LOW_POWER_MODE_8_BIT"); 
  else if (temp == LIS3DH_NOT_ALLOWED )  Serial.println("LIS3DH_NOT_ALLOWED"); 

  
  
  //******************************* SET DATA RATE *******************************//  
  Accel.setDataRate(LIS3DH_DATARATE_200_HZ); // LIS3DH_DATARATE_50_HZ = 0b0100, 
  temp = Accel.getDataRate();
  if (temp == LIS3DH_DATARATE_400_HZ )  Serial.println("LIS3DH_DATARATE_400_HZ");
  else if (temp == LIS3DH_DATARATE_200_HZ )  Serial.println("LIS3DH_DATARATE_200_HZ");
  else if (temp == LIS3DH_DATARATE_100_HZ )  Serial.println("LIS3DH_DATARATE_100_HZ");
  else if (temp == LIS3DH_DATARATE_50_HZ )  Serial.println("LIS3DH_DATARATE_50_HZ");
  else if (temp == LIS3DH_DATARATE_25_HZ )  Serial.println("LIS3DH_DATARATE_25_HZ");
  else if (temp == LIS3DH_DATARATE_10_HZ )  Serial.println("LIS3DH_DATARATE_10_HZ");
  else if (temp == LIS3DH_DATARATE_1_HZ )  Serial.println("LIS3DH_DATARATE_1_HZ");
  else if (temp == LIS3DH_DATARATE_POWERDOWN )  Serial.println("LIS3DH_DATARATE_POWERDOWN");
  else if (temp == LIS3DH_DATARATE_LOWPOWER_1K6HZ )  Serial.println("LIS3DH_DATARATE_LOWPOWER_1K6HZ");
  else if (temp == LIS3DH_DATARATE_LOWPOWER_5KHZ )  Serial.println("LIS3DH_DATARATE_LOWPOWER_5KHZ");
  else  Serial.println("no data rate found");
  
  
  //******************************* Table 10 / 30. Operating mode selection *******************************//

  
  //******************************* read control register *******************************//
    temp = Accel.REG_read(LIS3DH_REG_CTRL1);
    Serial.println(temp,BIN);
//    temp = Accel.REG_read(LIS3DH_REG_CTRL2);
//    Serial.println(temp,BIN);
//    temp = Accel.REG_read(LIS3DH_REG_CTRL3);
//    Serial.println(temp,BIN);
//    temp = Accel.REG_read(LIS3DH_REG_CTRL4);
//    Serial.println(temp,BIN);
}

void loop() {

  Accel.read();

  Serial.print(Accel.x);
  Serial.print(" : ");
  Serial.print(Accel.y);
  Serial.print(" : ");
  Serial.print(Accel.z);
  Serial.print(" : ");
  Serial.println();
  Accel.read_G();
    Serial.print(Accel.x_g/1000);
  Serial.print(" : ");
  Serial.print(Accel.y_g/1000);
  Serial.print(" : ");
  Serial.print(Accel.z_g/1000);
  Serial.print(" : ");
  Serial.println();
//
//  Serial.println(Accel.x_g);
//  Serial.println(Accel.y_g);
//  Serial.println(Accel.z_g);
  
  // put your main code here, to run repeatedly:
  //Serial.println("temp");    
//uint8_t temp = Accel.LIS3DH_read(Wai_Address);
// Serial.println(temp,HEX); 

 delay(1000);
}
