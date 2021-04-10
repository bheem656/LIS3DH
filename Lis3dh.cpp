#include "Lis3dh.h"
//#include <Wire.h>


bool Lis3dh :: begin(uint8_t i2caddr,uint8_t nWAI)
{

  _i2caddr = i2caddr;
  _wai = nWAI;
  // Start I2C Communication as Master
  Wire.begin();   //// join i2c bus (address optional for master)
  REG_write(LIS3DH_REG_CTRL1, 0b01111111); // low power 400 hz ctl1 table 10
//  setRange(LIS3DH_RANGE_8_G);
//  setDataRate(LIS3DH_DATARATE_100_HZ);

  uint8_t _data_temp;
  _data_temp = getDeviceId();
  
  if(_data_temp != _wai)  return false;  
  else  return true;

}

uint8_t Lis3dh :: getDeviceId()
{
Wire.beginTransmission(_i2caddr);
  Wire.write(Wai_Address);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, 1); // request 1 bytes from slave device #2
  uint8_t _data_temp;
  if(Wire.available() == 1)
    {   
      _data_temp = Wire.read();    
    }

return _data_temp;

}
  //******************************* SET RANGE *******************************//  
void Lis3dh::setRange(Lis3dh_range_t range)
{
uint8_t range_set = 0;
range_set |= (range << 4);
//range_set = 0xFF;
Wire.beginTransmission(_i2caddr);
Wire.write(LIS3DH_REG_CTRL4);
Wire.write(range_set);
Wire.endTransmission();

}
  //******************************* GET RANGE *******************************//  
Lis3dh_range_t Lis3dh::getRange(void)
{
uint8_t range_get ;
range_get = REG_read(LIS3DH_REG_CTRL4);
_response = range_get; 
range_get = range_get>>4;
return (Lis3dh_range_t)range_get;
}
  //******************************* SET RANGE *******************************//  
void Lis3dh::setDataRate(lis3dh_dataRate_t dataRate)
{
  uint8_t rate_set;
  rate_set |= (dataRate << 4);
  // read reg value
  getDataRate();
  // OR operation with value
  _response |= rate_set;  
  REG_write(LIS3DH_REG_CTRL1,_response);

}
  //******************************* GET DATA RATE *******************************//   
uint8_t Lis3dh::getDataRate(void)
{
  int8_t rate_get ;
  rate_get = REG_read(LIS3DH_REG_CTRL1);
  _response = rate_get;
  rate_get = rate_get >> 4;     
  return (uint8_t)rate_get;
}

// Read Data

void Lis3dh::read(void)
{
  uint8_t buffers[6];

    for(int i = 0; i < 6; i++)
    {
      buffers[i] = REG_read((40 + i));       
    }
    
    x = buffers[0];
    x |= ((uint16_t)buffers[1]) << 8;
    y = buffers[2];
    y |= ((uint16_t)buffers[3]) << 8;
    z = buffers[4];
    z |= ((uint16_t)buffers[5]) << 8;



}

int16_t Lis3dh::read_G(void)
{
  uint8_t temp,range;
     temp =  getMode();
    range = getRange();

  if (range == LIS3DH_RANGE_2_G)
  {
         if (temp == LIS3DH_NORMAL_MODE_10_BIT )  
                {            
                    shift = 6;
                    senstivity = 4;
                  }
            else if (temp == LIS3DH_HIGH_RESOLUTION_MODE_12_BIT )
                {            
                    shift = 4;
                    senstivity = 1;
                  }
            else if (temp == LIS3DH_LOW_POWER_MODE_8_BIT ) 
                {            
                    shift = 8;
                    senstivity = 16;
                  }
   
    } 
       
  else if (range == LIS3DH_RANGE_4_G) 
  {
         if (temp == LIS3DH_NORMAL_MODE_10_BIT )  
                {            
                    shift = 6;
                    senstivity = 8;
                  }
            else if (temp == LIS3DH_HIGH_RESOLUTION_MODE_12_BIT )
                {            
                    shift = 4;
                    senstivity = 2;
                  }
            else if (temp == LIS3DH_LOW_POWER_MODE_8_BIT ) 
                {            
                    shift = 8;
                    senstivity = 32;
                  }
 
    
    }
    
  else if (range == LIS3DH_RANGE_8_G)
  {
         if (temp == LIS3DH_NORMAL_MODE_10_BIT )  
                {            
                    shift = 6;
                    senstivity = 16;
                  }
            else if (temp == LIS3DH_HIGH_RESOLUTION_MODE_12_BIT )
                {            
                    shift = 4;
                    senstivity = 4;
                  }
            else if (temp == LIS3DH_LOW_POWER_MODE_8_BIT ) 
                {            
                    shift = 8;
                    senstivity = 64;
                  }
  
    }
    
  else if (range == LIS3DH_RANGE_16_G)
  {
         if (temp == LIS3DH_NORMAL_MODE_10_BIT )  
                {            
                    shift = 6;
                    senstivity = 48;
                  }
            else if (temp == LIS3DH_HIGH_RESOLUTION_MODE_12_BIT )
                {            
                    shift = 4;
                    senstivity = 12;
                  }
            else if (temp == LIS3DH_LOW_POWER_MODE_8_BIT ) 
                {            
                    shift = 8;
                    senstivity = 192;
                  } 
    
    }
//  Serial.print("shift :"); Serial.println(shift); 
//  Serial.print("senstivity :"); Serial.println(senstivity); 
 
    x_g = x >> shift;
    y_g = y >> shift;
    z_g = z >> shift;
    
    x_g = x_g * senstivity;
    y_g = y_g * senstivity;
    z_g = z_g * senstivity;
  
  }


uint8_t Lis3dh::REG_read(uint8_t REG)
{
  
    uint8_t inByte = 0;    
      // Start I2C Transmission
    Wire.beginTransmission(_i2caddr);
    // Select data register
    Wire.write(REG);
    // Stop I2C Transmission
    Wire.endTransmission();
    Wire.requestFrom(_i2caddr,1);    
    if(Wire.available()==1)
    {
       inByte = Wire.read();
    }
   return inByte;
}

void Lis3dh::REG_write(uint8_t reg, uint8_t value)
{

Wire.beginTransmission(_i2caddr);
// Select control register 1
Wire.write(reg);
// Enable X, Y, Z axis, power on mode, data rate selection = 10Hz
Wire.write(value);  //HR / Normal / Low-power mode (10 Hz)
  // Stop I2C Transmission
Wire.endTransmission();

}

uint8_t Lis3dh::getMode(void)
{
  uint8_t reg1,reg4;
  reg1 = REG_read(LIS3DH_REG_CTRL1);
  reg4 = REG_read(LIS3DH_REG_CTRL4);  
  reg1 = reg1 & (0x08);
  reg1 = reg1 >> 2;
  reg4 = reg4 & (0x08);
  reg4 = reg4 >> 3;  
  reg1 = reg1 | reg4;  
 return reg1;

}

void Lis3dh::setMode(uint8_t value)
{
  uint8_t reg1=0,reg4=0;
  reg1 = value & (0b10);
  //reg1 = value >> 1;
  reg1 |= reg1 << 2;  
  reg4 =  value & (0x01);
  reg4 = reg4 << 3;
  reg1 = reg1 | ((REG_read(LIS3DH_REG_CTRL1))&(0b11110111));
  reg4 = reg4 | ((REG_read(LIS3DH_REG_CTRL4)) &(0b11110111));
  REG_write(LIS3DH_REG_CTRL1,reg1);
  REG_write(LIS3DH_REG_CTRL4,reg4);
}
