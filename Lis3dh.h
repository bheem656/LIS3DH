/*
* Designed specifically to work with the  LIS3DH Triple-Axis Accelerometer
* (+-2g/4g/8g/16g)
*  
*
*/


#include <Arduino.h>
#ifndef Lis3dh_h
#define Lis3dh_h


#include <Wire.h>

#define LIS3DH_Default_Address  (0x19)
#define LIS3DH_REG_CTRL1 (0x20)
#define LIS3DH_REG_CTRL2 (0x21)
#define LIS3DH_REG_CTRL3 (0x22)
#define LIS3DH_REG_CTRL4 (0x23) // to set range
#define LIS3DH_REG_CTRL5 (0x24)

#define Wai_Address (0x0F)
#define LIS3DH_LSB16_TO_KILO_LSB10  64000

#define LIS3DH_REG_STATUS2 0x27
#define LIS3DH_REG_OUT_X_L 0x28 /**< X-axis acceleration data. Low value */
#define LIS3DH_REG_OUT_X_H 0x29 /**< X-axis acceleration data. High value */
#define LIS3DH_REG_OUT_Y_L 0x2A /**< Y-axis acceleration data. Low value */
#define LIS3DH_REG_OUT_Y_H 0x2B /**< Y-axis acceleration data. High value */
#define LIS3DH_REG_OUT_Z_L 0x2C /**< Z-axis acceleration data. Low value */
#define LIS3DH_REG_OUT_Z_H 0x2D /**< Z-axis acceleration data. High value */

//** mode **//
typedef enum{
  LIS3DH_NORMAL_MODE_10_BIT = 0b00,
  LIS3DH_HIGH_RESOLUTION_MODE_12_BIT = 0b01,
  LIS3DH_LOW_POWER_MODE_8_BIT = 0b10,
  LIS3DH_NOT_ALLOWED = 0b11
  }Lis3dh_rmode_t;

//** A structureto represent scales **//
typedef enum{
LIS3DH_RANGE_16_G = 0b11, //+/_ 16G
LIS3DH_RANGE_8_G = 0b10,    //+/_ 8G
LIS3DH_RANGE_4_G = 0b01,    //+/_ 4G
LIS3DH_RANGE_2_G = 0b00     //+/_ 2G
}Lis3dh_range_t;
/** Used with register 0x2A (LIS3DH_REG_CTRL_REG1) to set bandwidth **/
typedef enum {
  LIS3DH_DATARATE_400_HZ = 0b0111, //  400Hz
  LIS3DH_DATARATE_200_HZ = 0b0110, //  200Hz
  LIS3DH_DATARATE_100_HZ = 0b0101, //  100Hz
  LIS3DH_DATARATE_50_HZ = 0b0100,  //   50Hz
  LIS3DH_DATARATE_25_HZ = 0b0011,  //   25Hz
  LIS3DH_DATARATE_10_HZ = 0b0010,  // 10 Hz
  LIS3DH_DATARATE_1_HZ = 0b0001,   // 1 Hz
  LIS3DH_DATARATE_POWERDOWN = 0,
  LIS3DH_DATARATE_LOWPOWER_1K6HZ = 0b1000,
  LIS3DH_DATARATE_LOWPOWER_5KHZ = 0b1001,

} lis3dh_dataRate_t;

// ACCELEROMETER  CLASS
class Lis3dh
{

public :

// CONSTRUCTER 
 Lis3dh(void){};

//****************** LIS3DH INITIALIZATION *************************//
bool begin(uint8_t addr = LIS3DH_Default_Address, uint8_t nWAI = 0x33 ); // Table 21. Register address map
uint8_t getDeviceId(void);

//****************** RANGE SETINGS *************************//
void setRange(Lis3dh_range_t range);
Lis3dh_range_t getRange(void);

//****************** DATA RATE SETINGS *************************//
void setDataRate(lis3dh_dataRate_t dataRate);
uint8_t getDataRate(void);

//****************** REG READ/WRITE SETINGS *************************//
void REG_write(uint8_t reg, uint8_t value);
uint8_t REG_read(uint8_t REG);

//****************** CONVERT DATA IN G *************************//
void read(void);
int16_t read_G(void);

//****************** MODE GET *************************//
uint8_t getMode(void);
void setMode(uint8_t value);

//****************** PUBLIC VARIABLES *************************//

//uint8_t buffers[6];
int16_t x; /**< x axis value */
int16_t y; /**< y axis value */
int16_t z; /**< z axis value */

float x_g; /**< x_g axis value (calculated by selected range) */
float y_g; /**< y_g axis value (calculated by selected range) */
float z_g; /**< z_g axis value (calculated by selected scale) */


private :
uint8_t _i2caddr;
uint8_t _wai; // Device Address who am i

uint8_t shift;
uint8_t senstivity;
uint8_t _response;



};

#endif
