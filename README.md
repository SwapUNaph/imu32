# IMU 32
IMU 32 is a project to simplify working with MPU9250 imu sensors and STM32 ARM M1 microprocessors.

## MPU9250.h and MPU9250.c 
MPU9250.h provides interface which uses the HAL functionality of STM32 and helps in developing applications to interact with imu data.

### MPU9250_Writebytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t size);
  Write _size_ number of bytes to the register starting at _reg_ .
  
### MPU9250_Readbytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t size);
### MPU9250_Writebit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t bit);
### MPU9250_Readbit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit);
### MPU9250_SetGyroFullScale(I2C_HandleTypeDef* mpu_i2c_p, GYRO_FS_t gyro_fs);
### MPU9250_SetAccFullScale(I2C_HandleTypeDef* mpu_i2c_p, ACC_FS_t acc_fs);
### MPU9250_SetGyroOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* gyroOffsets);
### MPU9250_SetAccOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* accelOffsets);
### MPU9250_ConfigGyroDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, GYRO_DLPF_t gyro_dlpf);
### MPU9250_ConfigAccelDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, ACCEL_DLPF_t accel_dlpf);

## EKF.h (TBD) and EKF.c (TBD)
EKF.h provides the interface to implement the Extended Kalman filter algorithm which enables estimation of the orientation of the sensor with extreme accuracy.
