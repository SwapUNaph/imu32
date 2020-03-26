# IMU 32
IMU 32 is a project to simplify working with MPU9250 imu sensors and STM32 ARM M1 microprocessors.

## MPU9250.h and MPU9250.c 
MPU9250.h provides interface which uses the HAL functionality of STM32 and helps in developing applications to interact with imu data.
### MPU9250 Abstraction Layer
#### MPU9250_Writebytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t size)
  Write _size_ number of bytes to the register starting at _reg_.
  //
  
#### MPU9250_Readbytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t size)
  Read _size_ number of bytes from the register starting at _reg_.
  
  
#### MPU9250_Writebit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t bit)
 Write a bit to the register _reg_.
 
 
#### MPU9250_Readbit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit)
  Read a bit from the register _reg_.
  
  
#### MPU9250_SetGyroFullScale(I2C_HandleTypeDef* mpu_i2c_p, GYRO_FS_t gyro_fs)
Set Gyro Full Scale Range: \\
Available ranges (_gyro_fs_):
  GYRO_FS_250dps: 250 deg/sec \\
	GYRO_FS_500dps: 500 deg/sec \\
	GYRO_FS_1000dps: 1000 deg/sec \\
	GYRO_FS_2000dps: 2000 deg/sec \\
  
  
#### MPU9250_SetAccFullScale(I2C_HandleTypeDef* mpu_i2c_p, ACC_FS_t acc_fs)
Set Accelerometer Full Scale Range:
Available ranges (_acc_fs_):
	ACC_FS_2g: 2 g ~ 20 m/s2
	ACC_FS_4g: 4 g ~ 40 m/s2
	ACC_FS_8g: 8 g ~ 80 m/s2
	ACC_FS_16g: 16 g ~ 160 m/s2
  
  
#### MPU9250_SetGyroOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* gyroOffsets)
Set gyro offsets to _gyroOffsets[3]_.


#### MPU9250_SetAccOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* accelOffsets)
Set accelrometer offsets to _accelOffsets[3]_.


#### MPU9250_ConfigGyroDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, GYRO_DLPF_t gyro_dlpf)
Configure Gyro Digital Low Pass Filter (DLPF).
Available options (_gyro_dlpf_):
	GYRO_DLPF_BW_8800Hz: 8800 Hz bandwidth with 32 kHz of sampling frequency
	GYRO_DLPF_BW_3600Hz_Fs_32kHz: 3600 Hz bandwidth with 32 kHz of sampling frequency
	GYRO_DLPF_BW_250Hz: 250 Hz bandwidth with 8 kHz of sampling frequency
	GYRO_DLPF_BW_184Hz: 184 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_92Hz: 92 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_41Hz: 41 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_20Hz: 20 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_10Hz: 10 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_5Hz: 5 Hz bandwidth with 1 kHz of sampling frequency
	GYRO_DLPF_BW_3600Hz_Fs_8kHz: 3600 Hz bandwidth with 8 kHz of sampling frequency


#### MPU9250_ConfigAccelDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, ACCEL_DLPF_t accel_dlpf)
Configure Accelerometer Digital Low Pass Filter (DLPF).
Available options (accel_dlpf):
	ACCEL_DLPF_BW_1046Hz: 1046 Hz bandwidth
  ACCEL_DLPF_BW_420Hz: 420 Hz bandwidth
	ACCEL_DLPF_BW_218Hz: 218 Hz bandwidth
	ACCEL_DLPF_BW_99Hz: 99 Hz bandwidth
	ACCEL_DLPF_BW_44Hz: 44 Hz bandwidth
	ACCEL_DLPF_BW_21Hz: 21 Hz bandwidth
	ACCEL_DLPF_BW_10Hz: 10 Hz bandwidth
	ACCEL_DLPF_BW_5Hz: 5 Hz bandwidth




## EKF.h (TBD) and EKF.c (TBD)
EKF.h provides the interface to implement the Extended Kalman filter algorithm which enables estimation of the orientation of the sensor with extreme accuracy.
