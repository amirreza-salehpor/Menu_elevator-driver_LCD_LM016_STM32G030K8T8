	//#################################################################//
	
/**
* @brief MENU Selection & Display Library (Header File)
* @details Designed for PM Drive Panel Based on LM1602 as a LCD		
* @note  Use Only For PM motor Drive Panel

	Version:1403/04/1 -> Ragan Parto Pars 
	By A.Salehpour
	Editor:... 
	Version of Edit:
*/

	//#################################################################//
#include "stm32G0xx_hal.h"
#include <stdbool.h>
#define First_Menu_Indicator "RPP"

/**
* @brief Menu Typedef Structure
* @param Page/SubPage				Current Page/Subpage			Override Vector				State Selection
*/

typedef struct
{
int Menu_Page;
int Menu_Sub_Page;
int Current_Menu_Page;
int Current_Menu_SubPage;
uint16_t Override_Vector;
uint8_t machine_state_selection;

}	Menu_HandleTypeDef;




/**
* @brief 		TM1637 Driver Init
* @param 		Menu Type def, CLK Port&Pin , DATA Port&Pin
*/
void Menu_Driver_Init(Menu_HandleTypeDef *Menu, GPIO_TypeDef *gpio_clk, uint16_t pin_clk, GPIO_TypeDef *gpio_dat, uint16_t pin_dat);

/**
* @brief 		Display Different Strings Based on Menu Page & Subpage
* @param 		Input: Menu Structer (Page, Subpage, Override Vector)			Output: User State
*/
void Menu_Data_Display(Menu_HandleTypeDef *Menu);

/**
* @brief 		Menu Page , Subpage & Over ride Value Calculator Based on Input Parameter
* @param 		UP/DOWN/LEFT/RIGHT Keys & Fault Vector
*/
void Menu_Selection(Menu_HandleTypeDef *Menu,uint8_t ESC, uint8_t ENT, uint8_t Down, uint8_t Up,uint8_t Reset,uint8_t FaultVector);

/**
* @brief 		This function set your value on your diffrent setting
* @param 		Read just 1 bytes from Flash
*/
//void Change_Value_In_Sub_Page2(char Read_Array_Flash_byte_1,char Read_Array_Flash_byte_2,char Read_Array_Flash_byte_3,char Read_Array_Flash_byte_4);
void Change_Value_In_Sub_Page2(char Read_Array_Flash_byte_1);
/**
* @brief 		This funcation change your Manual mode among OP, Auto and CL
* @param 		It does not have any parameters
*/
void change_Mode_Manual_In_Sub_Page2();

/**
* @brief 		This funcation change your mode among commercial, household and office mode
* @param 		Read just 1 bytes from Flash
*/

void change_Mode_Value_In_Sub_Page2(char Read_Array_Flash_byte_1);

/**
* @brief 		This funcation is sutable for Blinking
* @param 		There is no Input for this funcation
*/
void Toggle_Show_Save(void);

/**
* @brief 		This funcation Save your changes on your Flash Base on your Address
* @param 		There is no Input for this funcation
*/
void Save_Changes(void);

/**
* @brief 		This funncation send your Frame changes to main board
* @param 		There is no Input for this funcation
*/
void Storage_Data_On_Mainboard(uint8_t Value,uint8_t setting);

/**
* @brief 		This funncation create the Advance sections in Level 2
* @param 		There is no Input for this funcation
*/
void change_Param_ADV1(void);

/**
* @brief 		This funncation create the Advance sections in Level 3
* @param 		There is no Input for this funcation
*/
void change_Param_ADV2(void);

/**
* @brief 		This funncation create the password section for ADV 1 and ADV 2
* @param 		There is no Input for this funcation
*/
bool Check_Password(void);

/**
* @brief 		This funncation using for increase the value in diffrent circumstances
* @param 		Menu's vector
*/
void Change_Value_Conditions_Up_Key(Menu_HandleTypeDef *Menu);

/**
* @brief 		This funncation using for decrease the value in diffrent circumstances
* @param 		Menu's vector
*/
void Change_Value_Conditions_Down_Key(Menu_HandleTypeDef *Menu);
/**
* @brief 		This funncation calculate check sum
* @param 		There is no Input for this funcation
*/
int Calculate_CRC(void);