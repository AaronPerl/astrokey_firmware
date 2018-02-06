//-----------------------------------------------------------------------------
// flash.h
//-----------------------------------------------------------------------------
// Copyright 2018 AstroKey
// https://github.com/AstroKey/astrokey_firmware/blob/master/LICENSE
//
// File Description:
//
// External flash driver function implementations
//

#include "flash.h"

// SFR page used to access SPI registers
#define SPI_SFR_PAGE 0x20

static void SPI0_FlushRx()
{
  uint8_t savedPage = SFRPAGE;
  SFRPAGE = SPI_SFR_PAGE;

  // Flush RX Buffer
  SPI0FCN0 |= SPI0FCN0_RFLSH__FLUSH;

  while (SPI0_isBusy()) {}

  SFRPAGE = savedPage;
}

static uint8_t readFlashStatus()
{
  uint8_t status;

  // Flush the Rx Buffer
  SPI0_FlushRx();

  // Wait until SPI is not busy
  while (SPI0_isBusy()) {}

  // Assert Chip Select
  FLASH_CS = 0;

  // Send READ_STATUS command
  SPI0_pollWriteByte(FLASH_CMD_READ_STATUS_1);

  // Write a dummy byte to clock the status byte into the FIFO
  SPI0_pollWriteByte(0x00);

  // Wait for TX to complete
  while (SPI0_isBusy()) {}

  // Read dummy byte
  SPI0_pollReadByte();

  // Read the status byte from the FIFO
  status = SPI0_pollReadByte();

  // Wait until SPI is not busy
  while (SPI0_isBusy()) {}

  // Deassert Chip Select
  FLASH_CS = 1;

  return status;
}

static void setFlashWriteEnable()
{
  // Wait until chip not busy
  while (readFlashStatus() & FLASH_STATUS1_BUSY) {}

  do
  {
    // Assert Chip Select
    FLASH_CS = 0;

    // Send Write Enable Command
    SPI0_pollWriteByte(FLASH_CMD_WRITE_ENABLE);

    // Wait until byte is written
    while (SPI0_isBusy()) {}

    // Deassert Chip Select
    FLASH_CS = 1;
  } while ((readFlashStatus() & FLASH_STATUS1_WEL) == 0);
}

void readFlashBytes(uint32_t addr,
                    SI_VARIABLE_SEGMENT_POINTER(rxBuffer, uint8_t, SI_SEG_GENERIC),
                    uint16_t len)
{
  bool modeChanged = astrokeyEnterFlashMode();

  // Wait until chip not busy
  while (readFlashStatus() & FLASH_STATUS1_BUSY) {}

  // Assert Chip Select
  FLASH_CS = 0;

  // Initialize Read
  SPI0_pollWriteByte(FLASH_CMD_READ);

  // Send Address
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >> 16)));
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  8)));
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  0)));

  // Wait for TX to complete
  while (SPI0_isBusy()) {}

  // Flush rx buffer
  SPI0_FlushRx();

  while (len > 0)
  {
    // Send clock to flash chip
    SPI0_pollWriteByte(0x00);
    // Read in byte
    *rxBuffer = SPI0_pollReadByte();

    len--;
    rxBuffer++;
  }

  // Deassert Chip Select
  FLASH_CS = 1;

  if (!modeChanged)
  astrokeyEnterButtonMode();
}

void writeFlashBytes(uint32_t addr,
                     SI_VARIABLE_SEGMENT_POINTER(txBuffer, uint8_t, SI_SEG_GENERIC),
                     uint16_t len)
{
  bool modeChanged = astrokeyEnterFlashMode();
  uint32_t pageEnd = FLASH_WRITE_PAGE_SIZE * (addr / FLASH_WRITE_PAGE_SIZE);

  while (len > 0)
  {
    // Calculate end of current write page
    pageEnd += FLASH_WRITE_PAGE_SIZE;

    // Enable Writes
    setFlashWriteEnable();

    // Assert Chip Select
    FLASH_CS = 0;

    // Initialize Write
    SPI0_pollWriteByte(FLASH_CMD_PROGRAM);

    // Send Address
    SPI0_pollWriteByte((uint8_t) (0xFF & (addr >> 16)));
    SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  8)));
    SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  0)));

    // Write current page bytes
    while (addr < pageEnd && len > 0)
    {
      SPI0_pollWriteByte(*txBuffer);

      len--;
      addr++;
      txBuffer++;
    }

    // Wait for TX to complete
    while (SPI0_isBusy()) {}

    // Deassert Chip Select
    FLASH_CS = 1;
  }

  if (!modeChanged)
  astrokeyEnterButtonMode();
}

void eraseFlashBlock(uint32_t addr)
{
  bool modeChanged = astrokeyEnterFlashMode();

  // Enable Writes
  setFlashWriteEnable();

  // Assert Chip Select
  FLASH_CS = 0;

  // Send clear block command
  SPI0_pollWriteByte(FLASH_CMD_BLOCK_ERASE_4K);

  // Send Address
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >> 16)));
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  8)));
  SPI0_pollWriteByte((uint8_t) (0xFF & (addr >>  0)));

  // Wait until byte is written
  while (SPI0_isBusy()) {}

  FLASH_CS = 1;

  if (!modeChanged)
  astrokeyEnterButtonMode();
}

