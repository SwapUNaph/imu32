
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



void MPU9250_Writebytes(I2C_HandleTypeDef* mpu_i2c_p,  uint8_t reg, uint8_t data, uint8_t size)
{
	uint8_t tmp = data;
	HAL_I2C_Mem_Write(mpu_i2c_p, MPU9250_ADD , reg, I2C_MEMADD_SIZE_8BIT, &tmp, size, 50);
	HAL_Delay(1);
}

void MPU9250_Readbytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t size)
{
		HAL_I2C_Mem_Read(mpu_i2c_p, MPU9250_ADD , reg, I2C_MEMADD_SIZE_8BIT, data, size, 50);
		HAL_Delay(1);
}

void MPU9250_Writebit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t bit)
{
		uint8_t tmp;
		MPU9250_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp = (data != 0 ) ? (tmp | (1 << bit) ) : ( tmp & ~( 1 << bit ));
		MPU9250_Writebytes(mpu_i2c_p, reg, tmp, 1);
}

void MPU9250_Readbit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit)
{
		uint8_t tmp;
		MPU9250_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp &= (1 << bit);
		*data = tmp;	
}

void AK8963_Writebytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t size)
{
	uint8_t tmp = data;
	HAL_I2C_Mem_Write(mpu_i2c_p, AK8963_ADD , reg, I2C_MEMADD_SIZE_8BIT, &tmp, size, 50);
	HAL_Delay(1);
}

void AK8963_Readbytes(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t size)
{
		HAL_I2C_Mem_Read(mpu_i2c_p, AK8963_ADD , reg, I2C_MEMADD_SIZE_8BIT, data, size, 50);
		HAL_Delay(1);
}

void AK8963_Writebit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t data, uint8_t bit)
{
		uint8_t tmp;
		AK8963_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp = (data != 0 ) ? (tmp | (1 << bit) ) : ( tmp & ~( 1 << bit ));
		AK8963_Writebytes(mpu_i2c_p, reg, tmp, 1);
}

void AK8963_Readbit(I2C_HandleTypeDef* mpu_i2c_p, uint8_t reg, uint8_t* data, uint8_t bit)
{
		uint8_t tmp;
		AK8963_Readbytes(mpu_i2c_p, reg, &tmp, 1);
		tmp &= (1 << bit);
		*data = tmp;
}


void MPU9250_SetGyroFullScale(I2C_HandleTypeDef* mpu_i2c_p, GYRO_FS_t gyro_fs)
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
		
	MPU9250_Writebit( mpu_i2c_p, MPU9250_GYRO_CONFIG, FS0, GYRO_FS_SEL_0 );
	MPU9250_Writebit(mpu_i2c_p, MPU9250_GYRO_CONFIG,  FS1, GYRO_FS_SEL_1 );
}


void MPU9250_SetAccFullScale(I2C_HandleTypeDef* mpu_i2c_p, ACC_FS_t acc_fs)
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
		
	MPU9250_Writebit( mpu_i2c_p, MPU9250_ACCEL_CONFIG, FS0, ACCEL_FS_SEL_0 );
	MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG,  FS1, ACCEL_FS_SEL_1 );
}


void MPU9250_SetGyroOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* gyroOffsets)
{
		uint8_t OFF_H = gyroOffsets[0] >> 8;
		uint8_t OFF_L = (uint8_t)(gyroOffsets[0] & 0xFF);
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XG_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XG_OFFSET_L, OFF_L, 1);

		OFF_H = gyroOffsets[1] >> 8;
		OFF_L = (uint8_t)(gyroOffsets[1] & 0xFF);
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_YG_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_YG_OFFSET_L, OFF_L, 1);
	
		OFF_H = gyroOffsets[2] >> 8;
		OFF_L = (uint8_t)(gyroOffsets[2] & 0xFF);
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_ZG_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_ZG_OFFSET_L, OFF_L, 1);
		
}



void MPU9250_SetAccOffset(I2C_HandleTypeDef* mpu_i2c_p, int16_t* accelOffsets)
{
		int16_t Xoff = ( accelOffsets[0] << 1 );
		uint8_t OFF_H = (uint8_t)(Xoff >> 8);
		uint8_t OFF_L = (uint8_t)( Xoff & 0xFF );
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XA_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_XA_OFFSET_L, OFF_L, 1);

		int16_t Yoff = ( accelOffsets[1] << 1 );
		OFF_H = (uint8_t)(Yoff >> 8);
		OFF_L = (uint8_t)( Yoff & 0xFF );
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_YA_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_YA_OFFSET_L, OFF_L, 1);
	
		int16_t Zoff = ( accelOffsets[2] << 1 );
		OFF_H = (uint8_t)(Zoff >> 8);
		OFF_L = (uint8_t)( Zoff& 0xFF);
	
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_ZA_OFFSET_H, OFF_H, 1);
		MPU9250_Writebytes(mpu_i2c_p, MPU9250_ZA_OFFSET_L, OFF_L, 1);
		
}


void MPU9250_ConfigGyroDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, GYRO_DLPF_t gyro_dlpf)
{
		uint8_t fchoice_b0, fchoice_b1, dlpf_cfg0, dlpf_cfg1, dlpf_cfg2;
		switch( gyro_dlpf )
		{
			case GYRO_DLPF_BW_8800Hz:
				fchoice_b1 = 1; fchoice_b0 = 1;
				dlpf_cfg2=0; dlpf_cfg1=0; dlpf_cfg0=0;
			break;
			
			case GYRO_DLPF_BW_3600Hz_Fs_32kHz:
				fchoice_b1 = 1; fchoice_b0 = 0;
				dlpf_cfg2=0; dlpf_cfg1=0; dlpf_cfg0=0;
			break;
			
			case GYRO_DLPF_BW_250Hz :
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=0; dlpf_cfg1=0; dlpf_cfg0=0;
			break;
			
			case GYRO_DLPF_BW_184Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=0; dlpf_cfg1=0; dlpf_cfg0=1;
			break;
			
			case GYRO_DLPF_BW_92Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=0; dlpf_cfg1=1; dlpf_cfg0=0;
			break;
			
			case GYRO_DLPF_BW_41Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=0; dlpf_cfg1=1; dlpf_cfg0=1;
			break;
						
			case GYRO_DLPF_BW_20Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=1; dlpf_cfg1=0; dlpf_cfg0=0;
			break;
						
			case GYRO_DLPF_BW_10Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=1; dlpf_cfg1=0; dlpf_cfg0=1;
			break;
									
			case GYRO_DLPF_BW_5Hz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=1; dlpf_cfg1=1; dlpf_cfg0=0;
			break;
									
			case GYRO_DLPF_BW_3600Hz_Fs_8kHz:
				fchoice_b1 = 0; fchoice_b0 = 0;
				dlpf_cfg2=1; dlpf_cfg1=1; dlpf_cfg0=1;
			break;
			
			default:
			break;
			
		}
		
		MPU9250_Writebit(mpu_i2c_p, MPU9250_CONFIG, fchoice_b0, FCHOICE_B_0);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_CONFIG, fchoice_b1, FCHOICE_B_1);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_CONFIG, dlpf_cfg0, DLPF_CFG_0);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_CONFIG, dlpf_cfg1, DLPF_CFG_1);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_CONFIG, dlpf_cfg2, DLPF_CFG_2);
}

void MPU9250_ConfigAccelDLPFilter(I2C_HandleTypeDef* mpu_i2c_p, ACCEL_DLPF_t accel_dlpf)
{
		uint8_t fchoice_b0, a_dlpf_cfg0, a_dlpf_cfg1, a_dlpf_cfg2;
		switch( accel_dlpf )
		{
			case ACCEL_DLPF_BW_1046Hz:
				fchoice_b0 = 1;
				a_dlpf_cfg2=0; a_dlpf_cfg1=0; a_dlpf_cfg0=0;
			break;
			
			case ACCEL_DLPF_BW_218Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=0; a_dlpf_cfg1=0; a_dlpf_cfg0=1;
			break;
			
			case ACCEL_DLPF_BW_99Hz :
				fchoice_b0 = 0;
				a_dlpf_cfg2=0; a_dlpf_cfg1=1; a_dlpf_cfg0=0;
			break;
			
			case ACCEL_DLPF_BW_44Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=0; a_dlpf_cfg1=1; a_dlpf_cfg0=1;
			break;
			
			case ACCEL_DLPF_BW_21Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=1; a_dlpf_cfg1=0; a_dlpf_cfg0=0;
			break;
			
			case ACCEL_DLPF_BW_10Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=1; a_dlpf_cfg1=0; a_dlpf_cfg0=1;
			break;
						
			case ACCEL_DLPF_BW_5Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=1; a_dlpf_cfg1=1; a_dlpf_cfg0=0;
			break;
						
			case ACCEL_DLPF_BW_420Hz:
				fchoice_b0 = 0;
				a_dlpf_cfg2=1; a_dlpf_cfg1=1; a_dlpf_cfg0=1;
			break;
			
			default:
			break;
			
		}
		
		MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG_2, fchoice_b0, ACCEL_FCHOICE_B);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG_2, a_dlpf_cfg0, A_DLPFCFG_0);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG_2, a_dlpf_cfg1, A_DLPFCFG_1);
		MPU9250_Writebit(mpu_i2c_p, MPU9250_ACCEL_CONFIG_2, a_dlpf_cfg2, A_DLPFCFG_2);
}







