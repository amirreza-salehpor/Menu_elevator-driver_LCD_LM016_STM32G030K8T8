#include "Store_Flash.h"
//#include "stm32G0xx_hal.h"
#include "stm32G0xx_hal_flash.h"

// Defualt value is Commercial mode
char Default_Flash_Array[255];



//---------------------------------- Reserve in Flash
uint8_t Byte_1_Device_Mode=0x6B; //107  : If you make changes to your settings, you need to update the number of settings here
//----------------------------------


//----------------------------------------------------
//------------------------ Coefficients for Default
//---------------------------------------------------- 
#define Low_speed_D 5
#define Lock_Distance_D 5
#define Accel_Lock_D 10


uint8_t Obstacle_KP_D[1]=                {20};                  															//OBP
uint8_t Learnig_Speed_D[1]=              {10};                          											//LSP
uint8_t Open_Accel_D[6]=                 {4,Accel_Lock_D,Accel_Lock_D,4,2,40};           	    //OPA
uint8_t Open_Speed_D[6]=                 {3,Low_speed_D,8,75,8,10};      										  //OPS
uint8_t Open_Current_D[6]=               {100,100,100,100,100,50};   												  //OPC
uint8_t Open_Position_D[6]=              {0,1,4,Lock_Distance_D,50,98};     									//OPP
uint8_t Close_Accel_D[6]=                {4,5,1,Accel_Lock_D,Accel_Lock_D,Accel_Lock_D};      //CLA
uint8_t Close_Speed_D[6]=                {3,65,6,Low_speed_D,8,4};        										//CLS
uint8_t Close_Current_D[6]=              {100,100,100,100,50,50};   												  //CLC
uint8_t Close_Position_D[6]=             {100,98,55,Lock_Distance_D,3,1};   									//CLP
uint8_t Stop_Accel_D[6]=                 {20,20,20,20,20,20};  				  											//BRA
uint8_t Stop_Speed_D[6]=                 {0,0,0,0,0,0};         															//BRS
uint8_t Stop_Current_D[6]=               {100,100,100,100,100,100};   												//BRC
uint8_t Stop_Position_D[6]=              {100,98,50,6,3,1};     															//BRP
uint8_t KP_Detection_Time_D[1]=          {20};                  															//OBD
uint8_t KP_Speed_Constant_D[1]=          {50};                 															  //OPC
uint8_t Opening_Destination_D[1]=        {0};                 													  		//DLO
uint8_t Closing_Destination_D[1]=        {0};                 														  	//DLC
uint8_t Normal_Jerk_D[1]=                {4};                  															  //NOJ
uint8_t Stop_Jerk_D[1]=                  {20};                   															//RDJ
uint8_t Over_Heat_Limit_D[1]=            {60};                  															//OHL
uint8_t Over_Load_Limit_D[1]=            {15};                  															//OLL
uint8_t Over_Load_Time_D[1]=             {30};                  															//OLD
uint8_t Motor_Pole_Number_D[1]=          {16};                  															//POC
uint8_t Motor_Nominal_Current_D[1]=      {100};                  															//CUR *10
uint8_t Motor_Nominal_Voltage_D[1]=      {50};                 															  //VOL *2
uint8_t Motor_Nominal_Speed_D[1]=        {80};                 															  //NSP *5
uint8_t Buzzer_Activation_D[1]=          {0};                   															//BUA	
//-----------------------------------------
uint8_t Tune_Mode_Flash_D[1]=            {0};                   															//LRN	
uint8_t Door_Direction_D[1]=             {0};                   															//DOD	
uint8_t Command_Source_Mode_D[1]=        {0};                   															//CSR	
uint8_t Demo_D[1]=                       {0};                   															//DENO
//-----------------------------------------
uint8_t Device_Mode_D[1]=                {0};
//-----------------------------------------


//----------------------------------------------------
//------------------------ Coefficients for Commercial
//---------------------------------------------------- 
#define Low_speed_C 5
#define Lock_Distance_C 5
#define Accel_Lock_C 10


uint8_t Obstacle_KP_C[1]=                {20};                  															//OBP
uint8_t Learnig_Speed_C[1]=              {10};                          											//LSP
uint8_t Open_Accel_C[6]=                 {4,Accel_Lock_D,Accel_Lock_D,4,2,40};           	    //OPA
uint8_t Open_Speed_C[6]=                 {3,Low_speed_D,8,75,8,10};      										  //OPS
uint8_t Open_Current_C[6]=               {100,100,100,100,100,50};   												  //OPC
uint8_t Open_Position_C[6]=              {0,1,4,Lock_Distance_D,50,98};     									//OPP
uint8_t Close_Accel_C[6]=                {4,5,1,Accel_Lock_D,Accel_Lock_D,Accel_Lock_D};      //CLA
uint8_t Close_Speed_C[6]=                {3,65,6,Low_speed_D,8,4};        										//CLS
uint8_t Close_Current_C[6]=              {100,100,100,100,50,50};   												  //CLC
uint8_t Close_Position_C[6]=             {100,98,55,Lock_Distance_D,3,1};   									//CLP
uint8_t Stop_Accel_C[6]=                 {20,20,20,20,20,20};  				  											//BRA
uint8_t Stop_Speed_C[6]=                 {0,0,0,0,0,0};         															//BRS
uint8_t Stop_Current_C[6]=               {100,100,100,100,100,100};   												//BRC
uint8_t Stop_Position_C[6]=              {100,98,50,6,3,1};     															//BRP
uint8_t KP_Detection_Time_C[1]=          {20};                  															//OBD
uint8_t KP_Speed_Constant_C[1]=          {50};                 															  //OPC
uint8_t Opening_Destination_C[1]=        {0};                 													  		//DLO
uint8_t Closing_Destination_C[1]=        {0};                 														  	//DLC
uint8_t Normal_Jerk_C[1]=                {4};                  															  //NOJ
uint8_t Stop_Jerk_C[1]=                  {20};                   															//RDJ
uint8_t Over_Heat_Limit_C[1]=            {60};                  															//OHL
uint8_t Over_Load_Limit_C[1]=            {15};                  															//OLL
uint8_t Over_Load_Time_C[1]=             {30};                  															//OLD
uint8_t Motor_Pole_Number_C[1]=          {16};                  															//POC
uint8_t Motor_Nominal_Current_C[1]=      {100};                  															//CUR *10
uint8_t Motor_Nominal_Voltage_C[1]=      {50};                 															  //VOL *2
uint8_t Motor_Nominal_Speed_C[1]=        {80};                 															  //NSP *5
uint8_t Buzzer_Activation_C[1]=          {0};                   															//BUA	
//-----------------------------------------
uint8_t Tune_Mode_Flash_C[1]=            {0};                   															//LRN	
//uint8_t Door_Direction_C[1]=             {0};                   															//DOD	
//uint8_t Command_Source_Mode_C[1]=        {0};                   															//CSR	
uint8_t Demo_C[1]=                       {0};                   															//DENO
//-----------------------------------------
uint8_t Device_Mode_C[1]=                {1};
//-----------------------------------------


//----------------------------------------------------
//------------------------ Coefficients for Household
//---------------------------------------------------- 

#define Low_speed_H 5
#define Lock_Distance_H 5
#define Accel_Lock_H 10


uint8_t Obstacle_KP_H[1]=                {20};                  															//OBP
uint8_t Learnig_Speed_H[1]=              {10};                          											//LSP
uint8_t Open_Accel_H[6]=                 {4,Accel_Lock_D,Accel_Lock_D,4,2,40};           	    //OPA
uint8_t Open_Speed_H[6]=                 {3,Low_speed_D,8,55,8,10};      										  //OPS
uint8_t Open_Current_H[6]=               {100,100,100,100,100,50};   												  //OPC
uint8_t Open_Position_H[6]=              {0,1,4,Lock_Distance_D,50,98};     									//OPP
uint8_t Close_Accel_H[6]=                {4,5,1,Accel_Lock_D,Accel_Lock_D,Accel_Lock_D};      //CLA
uint8_t Close_Speed_H[6]=                {3,45,6,Low_speed_D,8,4};        										//CLS
uint8_t Close_Current_H[6]=              {100,100,100,100,50,50};   												  //CLC
uint8_t Close_Position_H[6]=             {100,98,55,Lock_Distance_D,3,1};   									//CLP
uint8_t Stop_Accel_H[6]=                 {20,20,20,20,20,20};  				  											//BRA
uint8_t Stop_Speed_H[6]=                 {0,0,0,0,0,0};         															//BRS
uint8_t Stop_Current_H[6]=               {100,100,100,100,100,100};   												//BRC
uint8_t Stop_Position_H[6]=              {100,98,50,6,3,1};     															//BRP
uint8_t KP_Detection_Time_H[1]=          {20};                  															//OBD
uint8_t KP_Speed_Constant_H[1]=          {50};                 															  //OPC
uint8_t Opening_Destination_H[1]=        {0};                 													  		//DLO
uint8_t Closing_Destination_H[1]=        {0};                 														  	//DLC
uint8_t Normal_Jerk_H[1]=                {4};                  															  //NOJ
uint8_t Stop_Jerk_H[1]=                  {20};                   															//RDJ
uint8_t Over_Heat_Limit_H[1]=            {60};                  															//OHL
uint8_t Over_Load_Limit_H[1]=            {15};                  															//OLL
uint8_t Over_Load_Time_H[1]=             {30};                  															//OLD
uint8_t Motor_Pole_Number_H[1]=          {16};                  															//POC
uint8_t Motor_Nominal_Current_H[1]=      {100};                  															//CUR *10
uint8_t Motor_Nominal_Voltage_H[1]=      {50};                 															  //VOL *2
uint8_t Motor_Nominal_Speed_H[1]=        {80};                 															  //NSP *5
uint8_t Buzzer_Activation_H[1]=          {0};                   															//BUA	
//-----------------------------------------
uint8_t Tune_Mode_Flash_H[1]=            {0};                   															//LRN	
//uint8_t Door_Direction_H[1]=             {0};                   															//DOD	
//uint8_t Command_Source_Mode_H[1]=        {0};                   															//CSR	
uint8_t Demo_H[1]=                       {0};                   															//DENO
//-----------------------------------------
uint8_t Device_Mode_H[1]=                {2};
//-----------------------------------------

//----------------------------------------------------
//------------------------ Coefficients for Office
//---------------------------------------------------- 

#define Low_speed_O 15
#define Lock_Distance_O 6
#define Accel_Lock_O 6


uint8_t Obstacle_KP_O[1]=                {23};                  															//OBP
uint8_t Learnig_Speed_O[1]=              {15};                          											//LSP
uint8_t Open_Accel_O[6]=                 {4,Accel_Lock_O,Accel_Lock_O,10,10,10};           	  //OPA
uint8_t Open_Speed_O[6]=                 {8,Low_speed_O,8,90,25,8};      										  //OPS
uint8_t Open_Current_O[6]=               {100,100,100,100,100,100};   												//OPC
uint8_t Open_Position_O[6]=              {0,3,6,Lock_Distance_O,68,95};     									//OPP
uint8_t Close_Accel_O[6]=                {4,10,6,Accel_Lock_O,Accel_Lock_O,Accel_Lock_O};     //CLA
uint8_t Close_Speed_O[6]=                {12,90,8,Low_speed_O,8,8};        										//CLS
uint8_t Close_Current_O[6]=              {100,100,100,100,100,100};   												//CLC
uint8_t Close_Position_O[6]=             {100,98,55,Lock_Distance_O,3,1};   									//CLP
uint8_t Stop_Accel_O[6]=                 {10,10,10,10,10,10};  				  											//BRA
uint8_t Stop_Speed_O[6]=                 {0,0,0,0,0,0};         															//BRS
uint8_t Stop_Current_O[6]=               {100,100,100,100,100,100};   												//BRC
uint8_t Stop_Position_O[6]=              {100,98,50,6,3,1};     															//BRP
uint8_t KP_Detection_Time_O[1]=          {10};                  															//OBD
uint8_t KP_Speed_Constant_O[1]=          {50};                 															  //OPC
uint8_t Opening_Destination_O[1]=        {100};                 															//DLO
uint8_t Closing_Destination_O[1]=        {100};                 															//DLC
uint8_t Normal_Jerk_O[1]=                {15};                  															//NOJ
uint8_t Stop_Jerk_O[1]=                  {10};                   															//RDJ
uint8_t Over_Heat_Limit_O[1]=            {60};                  															//OHL
uint8_t Over_Load_Limit_O[1]=            {15};                  															//OLL
uint8_t Over_Load_Time_O[1]=             {30};                  															//OLD
uint8_t Motor_Pole_Number_O[1]=          {16};                  															//POC
uint8_t Motor_Nominal_Current_O[1]=      {100};                  															//CUR *10
uint8_t Motor_Nominal_Voltage_O[1]=      {50};                 															  //VOL *2
uint8_t Motor_Nominal_Speed_O[1]=        {80};                 															  //NSP *5
uint8_t Buzzer_Activation_O[1]=          {0};                   															//BUA	
//-----------------------------------------
uint8_t Tune_Mode_Flash_O[1]=            {0};                   															//LRN	
//uint8_t Door_Direction_O[1]=             {0};                   															//DOD	
//uint8_t Command_Source_Mode_O[1]=        {0};                   															//CSR	
uint8_t Demo_O[1]=                       {0};                   															//DENO
//-----------------------------------------
uint8_t Device_Mode_O[1]=                {3};
//-----------------------------------------


//--------------------------------------------------------------
void writeFlash(uint32_t startAddress, char str[]) {
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Page = startAddress;
  EraseInitStruct.NbPages     = 0;	
	uint32_t PAGEError = 0;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);	//Fill FF, as -1. 
	
	for(int i = 0; i < strlen(str); i++) {
//		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, startAddress, str[i]);
//		startAddress += 2;
		//HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, startAddress, str[i]);	//waste: we only use 1 byte of 4 bytes.
		//startAddress += 4;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, startAddress, str[i]);
		startAddress += 8;
		//HAL_Delay(1);
	}
	
	HAL_FLASH_Lock();
		
}
//--------------------------------------------------------------
uint32_t readFlash(uint32_t addr) {
	uint32_t data = *(__IO uint32_t *)(addr);
	return data;
}
//--------------------------------------------------------------
void Erase_Flash(uint32_t startAddress, uint32_t baseAddress) {
	
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks=FLASH_BANK_1;
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Page = ((int)(startAddress-baseAddress))/2048;
  EraseInitStruct.NbPages     = 1;	
	uint32_t PAGEError = 0;
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);	//Fill FF, as -1.
	HAL_FLASH_Lock();
	
}
//--------------------------------------------------------------
void Setup_Flash(void){
	

	
			Manage_Memory(Default_Flash_Array,0);
	

			
			
			//memcpy(&Default_Flash_Array[Byte_1_Device_Mode],&Device_Mode[0],1);
			
			Erase_Flash(FLASH_USER_START_ADDR,ADDR_FLASH_PAGE_BASE);
			
			incriment_array(1,sizeof(Default_Flash_Array),Default_Flash_Array);
			writeFlash(FLASH_USER_START_ADDR, Default_Flash_Array);	
			incriment_array(-1,sizeof(Default_Flash_Array),Default_Flash_Array);
		
}
//--------------------------------------------------------------
void incriment_array(int increment,int size_array,char array[]){	
	for(int Counter=0;Counter<=size_array;Counter++){
		array[Counter]+=increment;
	}
}
//--------------------------------------------------------------
void Manage_Memory(char array[],uint8_t mode){
	
	
	switch(mode){
		
		case 0://Default Value
			memset(&array[0],1,1);
			//--------------------------------------------------- Level 1
			memcpy(&array[1],&Obstacle_KP_D[0],1);
			memcpy(&array[2],&Open_Speed_D[3],1); //High SP Open
			memcpy(&array[3],&Close_Speed_D[1],1);//High SP Close
			memcpy(&array[4],&Open_Speed_D[1],1); //High SP Open == low speed
			memcpy(&array[5],&Close_Speed_D[3],1);//High SP Close == low speed
		  memcpy(&array[6],&Tune_Mode_Flash_D[0],1);
			memcpy(&array[7],&Door_Direction_D[0],1);
			memcpy(&array[8],&Command_Source_Mode_D[0],1);
			//--------------------------------------------------- Level 2
			memcpy(&array[14],&Open_Accel_D[4],2);
			memcpy(&array[16],&Open_Speed_D[0],1);
			memcpy(&array[17],&Open_Speed_D[2],1);		
			memcpy(&array[18],&Open_Speed_D[4],2);
			memcpy(&array[20],&Close_Accel_D[1],2);		
			memcpy(&array[22],&Close_Speed_D[0],1);
			memcpy(&array[23],&Close_Speed_D[2],1);
			memcpy(&array[24],&Close_Speed_D[4],2);
			memcpy(&array[26],&Open_Position_D[3],1);
			memcpy(&array[27],&Close_Position_D[3],1);
			memcpy(&array[28],&Buzzer_Activation_D[0],1);
			//--------------------------------------------------- Level 3
			memcpy(&array[34],&Open_Accel_D[0],4);
			memcpy(&array[38],&Open_Current_D[0],6);
			memcpy(&array[44],&Close_Accel_D[0],1);
			memcpy(&array[45],&Close_Accel_D[3],3);
			memcpy(&array[48],&KP_Detection_Time_D[0],1);
			memcpy(&array[49],&Normal_Jerk_D[0],1);
			memcpy(&array[50],&Stop_Jerk_D[0],1);
			memcpy(&array[51],&Over_Load_Limit_D[0],1);
			memcpy(&array[52],&Over_Load_Time_D[0],1);
			memcpy(&array[53],&Motor_Pole_Number_D[0],1);
			memcpy(&array[54],&Motor_Nominal_Current_D[0],1);
			memcpy(&array[55],&Motor_Nominal_Voltage_D[0],1);
			memcpy(&array[56],&Motor_Nominal_Speed_D[0],1);
			memcpy(&array[57],&Opening_Destination_D[0],1);
			memcpy(&array[58],&Closing_Destination_D[0],1);
			memcpy(&array[59],&Demo_D[0],1);
			//--------------------------------------------------- Level 4
			memcpy(&array[63],&Learnig_Speed_D[0],1);
			memcpy(&array[64],&Open_Position_D[0],3);
			memcpy(&array[67],&Open_Position_D[4],2);
			memcpy(&array[69],&Close_Current_D[0],6);
			memcpy(&array[75],&Close_Position_D[0],3);
			memcpy(&array[78],&Close_Position_D[4],2);
			memcpy(&array[80],&Stop_Accel_D[0],6);
			memcpy(&array[86],&Stop_Speed_D[0],6);
			memcpy(&array[92],&Stop_Current_D[0],6);
			memcpy(&array[98],&Stop_Position_D[0],6);
			memcpy(&array[104],&KP_Speed_Constant_D[0],1);
			memcpy(&array[105],&Over_Heat_Limit_D[0],1);
			//---------------------------------------------------------------- Reserve
			memcpy(&array[Byte_1_Device_Mode],&Device_Mode_D[0],1);
			
			
			break;
			
		case 1://Commercial Value
			memset(&array[0],1,1);
			//--------------------------------------------------- Level 1
			memcpy(&array[1],&Obstacle_KP_C[0],1);
			memcpy(&array[2],&Open_Speed_C[3],1); //High SP Open
			memcpy(&array[3],&Close_Speed_C[1],1);//High SP Close
			memcpy(&array[4],&Open_Speed_C[1],1); //High SP Open == low speed
			memcpy(&array[5],&Close_Speed_C[3],1);//High SP Close == low speed
		  memcpy(&array[6],&Tune_Mode_Flash_C[0],1);
			//memcpy(&array[7],&Door_Direction_C[0],1);
			//memcpy(&array[8],&Command_Source_Mode_C[0],1);
			//--------------------------------------------------- Level 2
			memcpy(&array[14],&Open_Accel_C[4],2);
			memcpy(&array[16],&Open_Speed_C[0],1);
			memcpy(&array[17],&Open_Speed_C[2],1);		
			memcpy(&array[18],&Open_Speed_C[4],2);
			memcpy(&array[20],&Close_Accel_C[1],2);		
			memcpy(&array[22],&Close_Speed_C[0],1);
			memcpy(&array[23],&Close_Speed_C[2],1);
			memcpy(&array[24],&Close_Speed_C[4],2);
			memcpy(&array[26],&Open_Position_C[3],1);
			memcpy(&array[27],&Close_Position_C[3],1);
			memcpy(&array[28],&Buzzer_Activation_C[0],1);
			//--------------------------------------------------- Level 3
			memcpy(&array[34],&Open_Accel_C[0],4);
			memcpy(&array[38],&Open_Current_C[0],6);
			memcpy(&array[44],&Close_Accel_C[0],1);
			memcpy(&array[45],&Close_Accel_C[3],3);
			memcpy(&array[48],&KP_Detection_Time_C[0],1);
			memcpy(&array[49],&Normal_Jerk_C[0],1);
			memcpy(&array[50],&Stop_Jerk_C[0],1);
			memcpy(&array[51],&Over_Load_Limit_C[0],1);
			memcpy(&array[52],&Over_Load_Time_C[0],1);
			memcpy(&array[53],&Motor_Pole_Number_C[0],1);
			memcpy(&array[54],&Motor_Nominal_Current_C[0],1);
			memcpy(&array[55],&Motor_Nominal_Voltage_C[0],1);
			memcpy(&array[56],&Motor_Nominal_Speed_C[0],1);
			memcpy(&array[57],&Opening_Destination_C[0],1);
			memcpy(&array[58],&Closing_Destination_C[0],1);
			memcpy(&array[59],&Demo_C[0],1);
			//--------------------------------------------------- Level 4
			memcpy(&array[63],&Learnig_Speed_C[0],1);
			memcpy(&array[64],&Open_Position_C[0],3);
			memcpy(&array[67],&Open_Position_C[4],2);
			memcpy(&array[69],&Close_Current_C[0],6);
			memcpy(&array[75],&Close_Position_C[0],3);
			memcpy(&array[78],&Close_Position_C[4],2);
			memcpy(&array[80],&Stop_Accel_C[0],6);
			memcpy(&array[86],&Stop_Speed_C[0],6);
			memcpy(&array[92],&Stop_Current_C[0],6);
			memcpy(&array[98],&Stop_Position_C[0],6);
			memcpy(&array[104],&KP_Speed_Constant_C[0],1);
			memcpy(&array[105],&Over_Heat_Limit_C[0],1);
			//---------------------------------------------------------------- Reserve
			memcpy(&array[Byte_1_Device_Mode],&Device_Mode_C[0],1);
			
			break;
			
		case 2://Household Value
			memset(&array[0],1,1);
			//--------------------------------------------------- Level 1
			memcpy(&array[1],&Obstacle_KP_H[0],1);
			memcpy(&array[2],&Open_Speed_H[3],1); //High SP Open
			memcpy(&array[3],&Close_Speed_H[1],1);//High SP Close
			memcpy(&array[4],&Open_Speed_H[1],1); //High SP Open == low speed
			memcpy(&array[5],&Close_Speed_H[3],1);//High SP Close == low speed
		  memcpy(&array[6],&Tune_Mode_Flash_H[0],1);
			//memcpy(&array[7],&Door_Direction_H[0],1);
			//memcpy(&array[8],&Command_Source_Mode_H[0],1);
			//--------------------------------------------------- Level 2
			memcpy(&array[14],&Open_Accel_H[4],2);
			memcpy(&array[16],&Open_Speed_H[0],1);
			memcpy(&array[17],&Open_Speed_H[2],1);		
			memcpy(&array[18],&Open_Speed_H[4],2);
			memcpy(&array[20],&Close_Accel_H[1],2);		
			memcpy(&array[22],&Close_Speed_H[0],1);
			memcpy(&array[23],&Close_Speed_H[2],1);
			memcpy(&array[24],&Close_Speed_H[4],2);
			memcpy(&array[26],&Open_Position_H[3],1);
			memcpy(&array[27],&Close_Position_H[3],1);
			memcpy(&array[28],&Buzzer_Activation_H[0],1);
			//--------------------------------------------------- Level 3
			memcpy(&array[34],&Open_Accel_H[0],4);
			memcpy(&array[38],&Open_Current_H[0],6);
			memcpy(&array[44],&Close_Accel_H[0],1);
			memcpy(&array[45],&Close_Accel_H[3],3);
			memcpy(&array[48],&KP_Detection_Time_H[0],1);
			memcpy(&array[49],&Normal_Jerk_H[0],1);
			memcpy(&array[50],&Stop_Jerk_H[0],1);
			memcpy(&array[51],&Over_Load_Limit_H[0],1);
			memcpy(&array[52],&Over_Load_Time_H[0],1);
			memcpy(&array[53],&Motor_Pole_Number_H[0],1);
			memcpy(&array[54],&Motor_Nominal_Current_H[0],1);
			memcpy(&array[55],&Motor_Nominal_Voltage_H[0],1);
			memcpy(&array[56],&Motor_Nominal_Speed_H[0],1);
			memcpy(&array[57],&Opening_Destination_H[0],1);
			memcpy(&array[58],&Closing_Destination_H[0],1);
			memcpy(&array[59],&Demo_H[0],1);
			//--------------------------------------------------- Level 4
			memcpy(&array[63],&Learnig_Speed_H[0],1);
			memcpy(&array[64],&Open_Position_H[0],3);
			memcpy(&array[67],&Open_Position_H[4],2);
			memcpy(&array[69],&Close_Current_H[0],6);
			memcpy(&array[75],&Close_Position_H[0],3);
			memcpy(&array[78],&Close_Position_H[4],2);
			memcpy(&array[80],&Stop_Accel_H[0],6);
			memcpy(&array[86],&Stop_Speed_H[0],6);
			memcpy(&array[92],&Stop_Current_H[0],6);
			memcpy(&array[98],&Stop_Position_H[0],6);
			memcpy(&array[104],&KP_Speed_Constant_H[0],1);
			memcpy(&array[105],&Over_Heat_Limit_H[0],1);
			//---------------------------------------------------------------- Reserve
			memcpy(&array[Byte_1_Device_Mode],&Device_Mode_H[0],1);
			
			break;
			
		case 3://Office Value
			memset(&array[0],1,1);
			//--------------------------------------------------- Level 1
			memcpy(&array[1],&Obstacle_KP_O[0],1);
			memcpy(&array[2],&Open_Speed_O[3],1); //High SP Open
			memcpy(&array[3],&Close_Speed_O[1],1);//High SP Close
			memcpy(&array[4],&Open_Speed_O[1],1); //High SP Open == low speed
			memcpy(&array[5],&Close_Speed_O[3],1);//High SP Close == low speed
		  memcpy(&array[6],&Tune_Mode_Flash_O[0],1);
			//memcpy(&array[7],&Door_Direction_O[0],1);
			//memcpy(&array[8],&Command_Source_Mode_O[0],1);
			//--------------------------------------------------- Level 2
			memcpy(&array[14],&Open_Accel_O[4],2);
			memcpy(&array[16],&Open_Speed_O[0],1);
			memcpy(&array[17],&Open_Speed_O[2],1);		
			memcpy(&array[18],&Open_Speed_O[4],2);
			memcpy(&array[20],&Close_Accel_O[1],2);		
			memcpy(&array[22],&Close_Speed_O[0],1);
			memcpy(&array[23],&Close_Speed_O[2],1);
			memcpy(&array[24],&Close_Speed_O[4],2);
			memcpy(&array[26],&Open_Position_O[3],1);
			memcpy(&array[27],&Close_Position_O[3],1);
			memcpy(&array[28],&Buzzer_Activation_O[0],1);
			//--------------------------------------------------- Level 3
			memcpy(&array[34],&Open_Accel_O[0],4);
			memcpy(&array[38],&Open_Current_O[0],6);
			memcpy(&array[44],&Close_Accel_O[0],1);
			memcpy(&array[45],&Close_Accel_O[3],3);
			memcpy(&array[48],&KP_Detection_Time_O[0],1);
			memcpy(&array[49],&Normal_Jerk_O[0],1);
			memcpy(&array[50],&Stop_Jerk_O[0],1);
			memcpy(&array[51],&Over_Load_Limit_O[0],1);
			memcpy(&array[52],&Over_Load_Time_O[0],1);
			memcpy(&array[53],&Motor_Pole_Number_O[0],1);
			memcpy(&array[54],&Motor_Nominal_Current_O[0],1);
			memcpy(&array[55],&Motor_Nominal_Voltage_O[0],1);
			memcpy(&array[56],&Motor_Nominal_Speed_O[0],1);
			memcpy(&array[57],&Opening_Destination_O[0],1);
			memcpy(&array[58],&Closing_Destination_O[0],1);
			memcpy(&array[59],&Demo_O[0],1);
			//--------------------------------------------------- Level 4
			memcpy(&array[63],&Learnig_Speed_O[0],1);
			memcpy(&array[64],&Open_Position_O[0],3);
			memcpy(&array[67],&Open_Position_O[4],2);
			memcpy(&array[69],&Close_Current_O[0],6);
			memcpy(&array[75],&Close_Position_O[0],3);
			memcpy(&array[78],&Close_Position_O[4],2);
			memcpy(&array[80],&Stop_Accel_O[0],6);
			memcpy(&array[86],&Stop_Speed_O[0],6);
			memcpy(&array[92],&Stop_Current_O[0],6);
			memcpy(&array[98],&Stop_Position_O[0],6);
			memcpy(&array[104],&KP_Speed_Constant_O[0],1);
			memcpy(&array[105],&Over_Heat_Limit_O[0],1);
			//---------------------------------------------------------------- Reserve
			memcpy(&array[Byte_1_Device_Mode],&Device_Mode_O[0],1);
			
			break;	
		}
}


