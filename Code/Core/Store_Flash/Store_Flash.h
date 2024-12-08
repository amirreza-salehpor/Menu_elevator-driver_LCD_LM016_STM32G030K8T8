#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"



//--------------------------------------------------------------
#define ADDR_FLASH_PAGE_START  ((uint32_t)0x0800F000) /* Base @ of Page 30, 2 Kbytes */
#define ADDR_FLASH_PAGE_END    ((uint32_t)0x0800F800) /* Base @ of Page 31, 2 Kbytes */
#define ADDR_FLASH_PAGE_BASE   ((uint32_t)0x08000000) /* Base @ of Page 0,  2 Kbytes */
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_START   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ADDR_FLASH_PAGE_END + FLASH_PAGE_SIZE   /* End @ of user Flash area */





//--------------------------------------------------------------
void writeFlash(uint32_t startAddress, char str[]);
//--------------------------------------------------------------
uint32_t readFlash(uint32_t addr);
//--------------------------------------------------------------
void Erase_Flash(uint32_t startAddress, uint32_t baseAddress);
//--------------------------------------------------------------
/**
* @brief 		This funnction would be call at start moment (before while)
* @param 		There is no Input for this funcation
*/
void Setup_Flash(void);                                            
//--------------------------------------------------------------
/**
* @brief 		When we want to write data to flash memory, we add one unit to the byte
* @param 		There is no Input for this funcation
*/
void incriment_array(int increment,int size_array,char array[]); 
//--------------------------------------------------------------
/**
* @brief 		This function manage all cofficients 
* @param 		There is no Input for this funcation
*/
void Manage_Memory(char array[],uint8_t mode);
//--------------------------------------------------------------