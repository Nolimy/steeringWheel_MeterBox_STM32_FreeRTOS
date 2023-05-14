#include "bsp_CAN.h"
#include "string.h"
#include "bsp_BC260Y.h"
#include "ui.h"
#include "applicationVar.h"


void CANFilter_Config(void)//���۷�ɶ�Ҷ��յ�ȫ�ա�
{
    CAN_FilterTypeDef  sFilterConfig;
    
    sFilterConfig.FilterBank = 0;                       //CAN��������ţ���Χ0-27
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;   //CAN������ģʽ������ģʽ���б�ģʽ
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;  //CAN�������߶ȣ�16λ��32λ
    sFilterConfig.FilterIdHigh = 0x000 << 5;			//32λ�£��洢Ҫ����ID�ĸ�16λ
    sFilterConfig.FilterIdLow = 0x0000;					//32λ�£��洢Ҫ����ID�ĵ�16λ
    sFilterConfig.FilterMaskIdHigh = 0x0000;			//����ģʽ�£��洢��������
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;				//����ͨ����������ƥ��󣬴洢���ĸ�FIFO
    sFilterConfig.FilterActivation = ENABLE;    		//���������
    sFilterConfig.SlaveStartFilterBank = 0;
    
    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
        printf("CAN Filter Config Fail!\r\n");
        Error_Handler();
    }
    printf("CAN Filter Config Success!\r\n");

}


//if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) 
//if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) 
void CAN1_Send(uint32_t CAN_ID, uint8_t *CAN_DATA)
{
	//uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    
  TxMessage.IDE = CAN_ID_STD;     //����ID����
	TxMessage.StdId = CAN_ID;        //����ID��
  TxMessage.RTR = CAN_RTR_DATA;   //���ô�������֡
	TxMessage.DLC = 8;              //�������ݳ���
    
	if (HAL_CAN_AddTxMessage(&hcan1, &TxMessage, CAN_DATA, (uint32_t*)CAN_TX_MAILBOX0) != HAL_OK) {
        Error_Handler();
    }
		
}
/*10��KEY��Ӧ10Bit���ݣ��ӵ�λ������1*/
void keyControlCanSend()
{
	canControlData[0] = 000;
	canControlData[1] = 0x00;
	if(HAL_GPIO_ReadPin(INPUT1_GPIO_Port, INPUT1_Pin) == RESET) canControlData[0] |= 0x01 << 0; 
	if(HAL_GPIO_ReadPin(INPUT2_GPIO_Port, INPUT2_Pin) == RESET) canControlData[0] |= 0x01 << 1;
	if(HAL_GPIO_ReadPin(INPUT3_GPIO_Port, INPUT3_Pin) == RESET) canControlData[0] |= 0x01 << 2;
	if(HAL_GPIO_ReadPin(INPUT4_GPIO_Port, INPUT4_Pin) == RESET) canControlData[0] |= 0x01 << 3;
	if(HAL_GPIO_ReadPin(INPUT5_GPIO_Port, INPUT5_Pin) == RESET) canControlData[0] |= 0x01 << 4;
	if(HAL_GPIO_ReadPin(INPUT6_GPIO_Port, INPUT6_Pin) == RESET) canControlData[0] |= 0x01 << 5;
	if(HAL_GPIO_ReadPin(INPUT7_GPIO_Port, INPUT7_Pin) == RESET) canControlData[0] |= 0x01 << 6;
	if(HAL_GPIO_ReadPin(INPUT8_GPIO_Port, INPUT8_Pin) == RESET) canControlData[0] |= 0x01 << 7;
	if(HAL_GPIO_ReadPin(INPUT9_GPIO_Port, INPUT9_Pin) == RESET) canControlData[1] |= 0x01 << 0;
	if(HAL_GPIO_ReadPin(INPUTA_GPIO_Port, INPUTA_Pin) == RESET) canControlData[1] |= 0x01 << 1;
	
	CAN1_Send(0X155, canControlData);
}
void CanFilterInit()
{
	usartTxFlag = 1;
	printf("----- CAN Test Board #1 -----\r\n");
	CANFilter_Config();
    
    /* 2. CAN Start */
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
			printf("CAN Start Fail\r\n");
			Error_Handler();
	}
	printf("CAN Start Success\r\n");
	
	/* 3. Enable CAN RX Interrupt */
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
			printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Fail\r\n");
			Error_Handler();
	}
	printf("CAN_IT_RX_FIFO0_MSG_PENDING Enable Success\r\n");
}

/*
struct RacingCarData
{

	//ID:0X193
	uint8_t FrontSpeed;          //ǰ�ֳ��� ��������Ϊ�ο����� 1Byte
	uint8_t PedalTravel;         //����̤�忪��    1Byte
	uint8_t brakeTravel;         //ɲ��̤�忪��    1Byte
	uint8_t carTravel;           //�����ܶ�����    1Byte
	uint16_t l_motor_torque;      //����Ŀ��ת��  2Byte
  uint16_t r_motor_torque;      //�ҵ��Ŀ��ת��  2Byte

	//ID:0X196 
	uint8_t batAlarm;            //��ظ澯  0~4 �޸澯��0 һ���澯��1�������أ� �����澯��2 �����澯��3
	uint8_t batTemp;               //����¶�  0-160  offset:-40
	uint8_t batLevel;            //��ص���  0-100
	uint16_t batVol;              //��ص�ѹ  0-900
	uint8_t gearMode;            //��λ��Ϣ  1Bit
	uint8_t carMode;             //��������ģʽ  1Bit 1:ת��ģʽ 2���ٶ�ģʽ
	//ID:0X191
	uint16_t lmotorSpeed;         //����ת��  2Bit offset -10000rpm �ֱ���:0.5
	//ID:0X192
	uint8_t lmotorTemp;          //�����¶�   1Byte 0~150���϶� offset:-50
	uint8_t mcu1Temp;            //���������1�¶� 1Byte 0~150���϶� offset:-50
	//ID:0X194	
	uint16_t rmotorSpeed;         //�ҵ��ת��  2Bit offset -10000rpm �ֱ���:0.5
	//ID:0X195
	uint8_t rmotorTemp;          //�ҵ���¶�
	uint8_t mcu2Temp;            //���������2�¶�
	
	
};
*/

