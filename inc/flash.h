//-----------------------------------------------------------------------------
// flash.h
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// File Description:
//
// External flash driver definitions and function declarations.
//

#ifndef FLASH_H_
#define FLASH_H_

#include "astrokey.h"
#include "spi_0.h"

//////////////
// Commands //
//////////////

// Read
#define FLASH_CMD_READ_HS         0x0B // High-Speed Array Read (1 dummy address byte)
#define FLASH_CMD_READ            0x03 // Standard Array Read (0 dummy address bytes)

// Write/Erase
#define FLASH_CMD_BLOCK_ERASE_4K  0x20 // Erase 4KB Block
#define FLASH_CMD_BLOCK_ERASE_32K 0x52 // Erase 32KB Block
#define FLASH_CMD_BLOCK_ERASE_64K 0xD8 // Erase 64KB Block
#define FLASH_CMD_CHIP_ERASE      0x60 // Erase Entire Chip
#define FLASH_CMD_CHIP_ERASE_ALT  0xC7 // Erase Entire Chip (identical to 0x60)
#define FLASH_CMD_PROGRAM         0x02 // Program byte/array

// Protect
#define FLASH_CMD_WRITE_ENABLE    0x06 // Enable Writes
#define FLASH_CMD_WRITE_DISABLE   0x04 // Disable Writes

// Status
#define FLASH_CMD_READ_STATUS_1   0x05 // Read Status Register Byte 1
#define FLASH_CMD_READ_STATUS_2   0x35 // Read Status Register Byte 2
#define FLASH_CMD_WRITE_STATUS    0x01 // Write Status Register

///////////////
// Bit Masks //
///////////////

// Status byte 1
#define FLASH_STATUS1_BUSY        0x01
#define FLASH_STATUS1_WEL         0x02
#define FLASH_STATUS1_BP0         0x04
#define FLASH_STATUS1_BP1         0x08
#define FLASH_STATUS1_BP2         0x10
#define FLASH_STATUS1_TB          0x20
#define FLASH_STATUS1_SEC         0x40
#define FLASH_STATUS1_SRP0        0x80

// Status byte 2
#define FLASH_STATUS2_SRP1        0x01
#define FLASH_STATUS2_QE          0x02
#define FLASH_STATUS2_RES1        0x04
#define FLASH_STATUS2_LB1         0x08
#define FLASH_STATUS2_LB2         0x10
#define FLASH_STATUS2_LB3         0x20
#define FLASH_STATUS2_CMP         0x40
#define FLASH_STATUS2_RES2        0x80

///////////////
// Constants //
///////////////

#define FLASH_WRITE_PAGE_SIZE     0x00000100UL
#define FLASH_4K_BLOCK_SIZE       0x00001000UL
#define FLASH_32K_BLOCK_SIZE      0x00008000UL
#define FLASH_64K_BLOCK_SIZE      0x00010000UL
#define FLASH_SIZE                0x00080000UL

///////////////
// Functions //
///////////////

void readFlashBytes(uint32_t addr,
                    SI_VARIABLE_SEGMENT_POINTER(rxBuffer, uint8_t, SI_SEG_GENERIC),
                    uint16_t len);

void writeFlashBytes(uint32_t addr,
                     SI_VARIABLE_SEGMENT_POINTER(txBuffer, uint8_t, SI_SEG_GENERIC),
                     uint16_t len);

void eraseFlashBlock(uint32_t addr);

#endif /* FLASH_H_ */
