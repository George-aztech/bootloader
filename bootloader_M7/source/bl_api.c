/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if 0
#include "bl_api.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define g_bootloaderTree ((bootloader_api_entry_t *)*(uint32_t *)0x0020001c)

#define api_flexspi_nor_erase_sector \
    ((status_t(*)(uint32_t instance, flexspi_nor_config_t * config, uint32_t address))0x0021055d)
#define api_flexspi_nor_erase_block \
    ((status_t(*)(uint32_t instance, flexspi_nor_config_t * config, uint32_t address))0x002104a9)



flexspi_nor_config_t zgmconfig= {
	    .memConfig =
	        {
	            .tag              = FLEXSPI_CFG_BLK_TAG,
	            .version          = FLEXSPI_CFG_BLK_VERSION,
	            .readSampleClkSrc = kFlexSPIReadSampleClk_LoopbackFromDqsPad,
	            .csHoldTime       = 3u,
	            .csSetupTime      = 3u,
				//
							.columnAddressWidth = 0u,/*列地址宽度*/
							.deviceModeCfgEnable = 1u,/*设备模式配置使能*/
						    .deviceModeType = 1u,/*Quad 使能命令*/
							.deviceModeSeq.seqNum = 1u,/*LUT序列号*/
							.deviceModeSeq.seqId = 4u, /*LUT序列索引*/
							.deviceModeArg = 0x000200,/*设置 QE=1（S9）*/
							.deviceType = kFlexSpiDeviceType_SerialNOR,/*设备类型为nor flash*/
							//
	            .sflashPadType    = kSerialFlash_4Pads,
	            .serialClkFreq    = kFlexSpiSerialClk_100MHz,
	            .sflashA1Size     = 8u * 1024u * 1024u,
	            .lookupTable =
	                {


						 // Sequence 0 - Quad Read
						// 0x6B - Fast read Quad Output command, 0x18 - 24 bit address
						[0]  = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x6B,
											RADDR_SDR, FLEXSPI_1PAD, 0x18),
						 // 0x08 - 8 dummy clocks, 0x80 - read 128 bytes
						[1]  = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD, 0x08,
											   READ_SDR,  FLEXSPI_4PAD, 0x80),

						// Sequence 1 - Read Status Register
						// 0x05 - Read status register command, 0x4 - read 4 bytes
						[4]  = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x05,
											  READ_SDR,  FLEXSPI_1PAD, 0x04),

						// Sequence 2 - Write Status Register 2
						// 0x31 - Write status register 2 command, 0x1 - write 1 byte
						[8]  = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x31,
						 WRITE_SDR, FLEXSPI_1PAD, 0x01),

						// Sequence 3 - Write enable
						// 0x06 - Write enable command
						[12] = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x06,
												 STOP,      0x00,          0x00),
						//[16] - Seq 4 empty

						// Sequence 5 - 4K Sector erase
						 // 0x20 - Sector erase command, 0x18 - 24 bit address
						[20] = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x20,
												RADDR_SDR, FLEXSPI_1PAD, 0x18),
						//[24] - Seq 6 empty
						//[28] - Seq 7 empty
						 //[32] - Seq 8 empty

						// Sequence 9 - Page Program, 256 bytes
						 // 0x02 - page program command, 0x18 - 24 bit address
						 [36] = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x02,
												 RADDR_SDR, FLEXSPI_1PAD, 0x18),
						// 0x04 - write 4 bytes
						[37] = FLEXSPI_LUT_SEQ(WRITE_SDR, FLEXSPI_1PAD, 0x04,
												 STOP,      0x00,          0x00),
						//[40] - Seq 10 empty
						//[44] - Seq 11 empty

						// Sequence 12 - Read JEDEC
						// 0x9F - read JEDEC command, 0x04 - read 4 bytes
						[48] = FLEXSPI_LUT_SEQ(CMD_SDR,       FLEXSPI_1PAD, 0x9F,
						 READ_SDR,  FLEXSPI_1PAD, 0x04),
						//[52-60] - Seqs 13 - 15 empty

	                },
	        },
	    .pageSize           = 256u,
	    .sectorSize         = 4u * 1024u,
	    .blockSize          = 64u * 1024u,
	    .isUniformBlockSize = false,
	};


/*******************************************************************************
 * Codes
 ******************************************************************************/

/*******************************************************************************
 * FlexSPI NOR driver
 ******************************************************************************/
status_t flexspi_nor_flash_init(uint32_t instance, flexspi_nor_config_t *config)
{
    return g_bootloaderTree->flexSpiNorDriver->init(instance, config);
}

status_t flexspi_nor_flash_page_program(uint32_t instance,
                                        flexspi_nor_config_t *config,
                                        uint32_t dstAddr,
                                        const uint32_t *src)
{
    return g_bootloaderTree->flexSpiNorDriver->program(instance, config, dstAddr, src);
}

status_t flexspi_nor_flash_erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length)
{
    return g_bootloaderTree->flexSpiNorDriver->erase(instance, config, start, length);
}

status_t flexspi_nor_flash_erase_sector(uint32_t instance, flexspi_nor_config_t *config, uint32_t start)
{
    return api_flexspi_nor_erase_sector(instance, config, start);
}

status_t flexspi_nor_flash_erase_block(uint32_t instance, flexspi_nor_config_t *config, uint32_t start)
{
    return api_flexspi_nor_erase_block(instance, config, start);
}

status_t flexspi_command_xferdata(uint32_t instance, flexspi_xfer_t *xfer)
{
    return g_bootloaderTree->flexSpiNorDriver->xfer(instance, xfer);
}

void flexspi_clear_cache(uint32_t instance)
{
    g_bootloaderTree->flexSpiNorDriver->clear_cache(instance);
}



status_t flash_init(void)
{
	return flexspi_nor_flash_init(0, &zgmconfig);
}

status_t flash_page_program( uint32_t dstAddr,const uint32_t *src)
{
	return 	flexspi_nor_flash_page_program(0, &zgmconfig, dstAddr,src);
}


status_t flash_erase(uint32_t start, uint32_t length)
{
	return flexspi_nor_flash_erase(0, &zgmconfig,start,length);
}

status_t flash_erase_sector( uint32_t start)
{

	return flexspi_nor_flash_erase_sector(0, &zgmconfig,start);
}

status_t flash_erase_block(uint32_t start)
{
	return flexspi_nor_flash_erase_block(0, &zgmconfig,start);
}


status_t flash_xferdata(flexspi_xfer_t *xfer)
{
	return flexspi_command_xferdata(0,xfer);
}

void flash_clear_cache(void)
{
	flexspi_clear_cache(0);
}

#endif




