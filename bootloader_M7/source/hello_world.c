/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
//#include "bl_api.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#define FLASH_START_ADD								0x60000000  //bootloader 64k
#define FLASH_APP1_CODE_ADD							0x60010000  //APP1   400K
#define FLASH_APP2_CODE_ADD							0x60074000  //APP2   400K
#define FLASH_APP_USER_DATA_ADD						0x600d8000  //APP recoder user data 160K
#define SDRAM_APP_CODE_ADD							0x80000000  //SDRAM START ADDR
#define APP_WRITE_ONCE_SIZE							0x0000A000
#define RUNAPP1                                       1
#define RUNAPP2                                       2
#define PAGESIZE                                     256
#define SECTORSIZE                                  0X1000

typedef struct iap_config
{
	uint32_t apprun;
    uint32_t app1Size;
    uint32_t app1verion;
    uint32_t app2Size;
    uint32_t app2verion;
} iap_config_t;

typedef void(*application_handler_t)(void);
enum{
	QuadSPI_Image_Start=0x80000000,
};
uint32_t Image_Start=0;
iap_config_t iap_config={0};

void delay_ms(uint32_t value)
{
	uint32_t i=0;
	uint32_t j=0;

	for(i=0;i<value;i++){

		for(j=0;j<10000;j++){

		}

	}

}

int main(void)
{

    static uint32_t s_stackPointer=0;
    static application_handler_t runApplication;

    BOARD_ConfigMPU();
    delay_ms(10000);
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    PRINTF("\r\n************enter bootloader**********\r\n");
   memcpy((void*)&iap_config, (void*)FLASH_APP_USER_DATA_ADD, sizeof(iap_config_t));
       PRINTF("apprun=0x%x\r\n",iap_config.apprun);
       PRINTF("app1Size=0x%x\r\n",iap_config.app1Size);
       PRINTF("app1ver=0x%x\r\n",iap_config.app1verion);
       PRINTF("app2Size=0x%x\r\n",iap_config.app2Size);
       PRINTF("app2ver=0x%x\r\n",iap_config.app2verion);


    if(iap_config.apprun==RUNAPP1)
    {
      memcpy((void*)SDRAM_APP_CODE_ADD, (void*)FLASH_APP1_CODE_ADD, iap_config.app1Size);
    }else if(iap_config.apprun==RUNAPP2){
      memcpy((void*)SDRAM_APP_CODE_ADD, (void*)FLASH_APP2_CODE_ADD, iap_config.app2Size);
    }
    else
    {
		 iap_config.apprun=RUNAPP1;
		 iap_config.app1verion=1;
		 iap_config.app1Size=400000;
		 iap_config.app2verion=2;
		 iap_config.app2Size=400000;
		 memcpy((void*)SDRAM_APP_CODE_ADD, (void*)FLASH_APP1_CODE_ADD, iap_config.app1Size);
    }

    Image_Start=QuadSPI_Image_Start;
    s_stackPointer=*(uint32_t*)Image_Start;
   	SCB->VTOR=Image_Start;
   	runApplication=*(application_handler_t*)(Image_Start+4);
   	__set_MSP(s_stackPointer);
   	__set_PSP(s_stackPointer);
   	runApplication();
    while (1)
    {

    }
}
