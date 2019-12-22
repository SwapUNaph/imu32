
#include "MPU9250.h"


//void MPU9250_Init()
//{ 
//	   I2C_InitTypeDef I2C_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;

//    /* Enable I2C and GPIO clocks */
//    RCC_APB1PeriphClockCmd(MPU6050_I2C_RCC_Periph, ENABLE);
//    RCC_APB2PeriphClockCmd(MPU6050_I2C_RCC_Port, ENABLE);

//    /* Configure I2C pins: SCL and SDA */
//    GPIO_InitStructure.GPIO_Pin = MPU6050_I2C_SCL_Pin | MPU6050_I2C_SDA_Pin;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//    GPIO_Init(MPU6050_I2C_Port, &GPIO_InitStructure);

//    /* I2C configuration */
//    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
//    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
//    I2C_InitStructure.I2C_OwnAddress1 = MPU6050_DEFAULT_ADDRESS; // MPU6050 7-bit adress = 0x68, 8-bit adress = 0xD0;
//    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
//    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//    I2C_InitStructure.I2C_ClockSpeed = MPU6050_I2C_Speed;

//    /* Apply I2C configuration after enabling it */
//    I2C_Init(MPU6050_I2C, &I2C_InitStructure);
//    /* I2C Peripheral Enable */
//    I2C_Cmd(MPU6050_I2C, ENABLE);
//}



void MPU9250_Writebytes(I2C_HandleTypeDef* mpu_i2c_p,  uint8_t reg, uint8_t* data, uint8_t size)
{
		HAL_I2C_Mem_Write(mpu_i2c_p, MPU9250_ADD , reg, I2C_MEMADD_SIZE_8BIT, data, size, 50);
}

void MPU9250_Readbytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t size)
{
		HAL_I2C_Mem_Read(mpu_i2c_p, MPU9250_ADD , reg, I2C_MEMADD_SIZE_8BIT, data, size, 50);
}

void MPU9250_Writebit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit)
{
		uint8_t tmp;
		MPU9250_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp = (*data != 0 ) ? (tmp | (1 << bit) ) : ( tmp & ~( 1 << bit ));
		MPU9250_Writebytes(mpu_i2c_p, reg, &tmp, 1);
}

void MPU9250_Readbit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit)
{
		uint8_t tmp;
		MPU9250_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp &= (1 << bit);
		*data = tmp;	
}


void MPU9250_SetGyroFullScale(I2C_HandleTypeDef* mpu_i2c_p, GYRO_FS gyro_fs)
{
	uint8_t FS0, FS1;
	switch(gyro_fs)
	{
		case GYRO_FS_250dps:
			FS1 = 0; FS0 = 0;
			break;
		case GYRO_FS_500dps:
			FS1 = 0; FS0 = 1; 
			break;
		case GYRO_FS_1000dps:
			FS1 = 1; FS0 = 0; 
			break;
		case GYRO_FS_2000dps:
			FS1 = 1; FS0 = 1; 
			break;
		default:
			break;
	}
		
	MPU9250_Writebit( mpu_i2c_p, MPU9250_GYRO_CONFIG, &FS0, GYRO_FS_SEL_0 );
	MPU9250_Writebit(mpu_i2c_p, MPU9250_GYRO_CONFIG,  &FS1, GYRO_FS_SEL_1 );
}


void MPU9250_SetAccFullScale(I2C_HandleTypeDef* mpu_i2c_p, ACC_FS acc_fs)
{
	uint8_t FS0, FS1;
	switch(acc_fs)
	{
		case ACC_FS_2g:
			FS1 = 0; FS0 = 0;
			break;
		case ACC_FS_4g:
			FS1 = 0; FS0 = 1; 
			break;
		case ACC_FS_8g:
			FS1 = 1; FS0 = 0; 
			break;
		case ACC_FS_16g:
			FS1 = 1; FS0 = 1; 
			break;
		default:
			break;
	}
		
	MPU9250_Writebit( mpu_i2c_p, MPU9250_ACCEL_CONFIG, &FS0, ACCEL_FS_SEL_0 );
	MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG,  &FS1, ACCEL_FS_SEL_1 );
}


void MPU9250_SetGyroOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* gyroOffsets)
{
	for(int i=0; i<3; i++)
	{
		uint8_t OFF_H = (gyroOffsets[i] >> 8);
		uint8_t OFF_L = (gyroOffsets[i] & 0xFF);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XG_OFFSET_H+ 2*i, &OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XG_OFFSET_H+ 2*i + 1, &OFF_L, 1);
	}
}



void MPU9250_SetAccOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* accelOffsets)
{
	
//	MPU9250_Writebytes(mpu_i2c_p, MPU9250_XA_OFFSET_H, (uint8_t*)accelOffsets, 6);
	for(uint8_t i=0; i<3; i++)
	{
		uint8_t OFF_H = (accelOffsets[i] & 0xFF00);
		uint8_t OFF_L = (accelOffsets[i] & 0x00FF);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XA_OFFSET_H + 2*i, &OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XA_OFFSET_H + 2*i + 1, &OFF_L, 1);
	}
}










