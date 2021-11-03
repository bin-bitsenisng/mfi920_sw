/* adi_dmhal.h
 * Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
 *
 * Clear BSD license
 * -----------------
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Analog Devices, Inc. nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @file
 * Public C hardware abstraction layer
 * 
 * These functions are to be implemented by the user for their chosen platform.
 */

#ifndef __ADI_DMHAL_H__
#define __ADI_DMHAL_H__

/*
 * The user may override these defines in the build to configure the SPI in the driver.
 */
#ifndef ADI_DM_SPI_IS_LSBFIRST
/**
 * Set this define to 1 if the low order bit of each byte will be transmitted first
 * by your implementation of #adi_dm_SPI
 */
#define ADI_DM_SPI_IS_LSBFIRST 0
#endif

#ifndef ADI_DM_NUM_DIGIMMIC
/**
 * Set this define to the number of DigiMMICs to be controlled by the driver.
 * This count includes both the master and slaves.
 */
#define ADI_DM_NUM_DIGIMMIC 4
#endif

#ifndef ADI_DM_NUM_SPI_SLAVES
/**
 * Set this define to the number of SPI slaves to be controlled by the driver.
 * These slaves must support the ADI SPI protocol and may be accessed with
 * #adi_dm_WriteSPI and #adi_dm_ReadSPI.
 * Must be at least 1.
 * The default value of 2 is intended to support a DigiMMIC and PMIC.
 */
#define ADI_DM_NUM_SPI_SLAVES (ADI_DM_NUM_DIGIMMIC + 1)
#endif

#ifndef ADI_DM_DIGIMMIC_MASTER_SPI_ADDR
/**
 * The slave parameter the driver should pass to #adi_dm_SPI to access the 1st DigiMMIC under its control.
 * This must always be the (DigiMMIC) master in a cascaded system.
 */
#define ADI_DM_DIGIMMIC_MASTER_SPI_ADDR 2
#endif

#ifndef ADI_DM_DIGIMMIC_SPI_SLAVE1
/**
 * The slave parameter the driver should pass to #adi_dm_SPI to access the 2nd DigiMMIC under its control.
 */
#define ADI_DM_DIGIMMIC_SPI_SLAVE1 0
#endif

#ifndef ADI_DM_DIGIMMIC_SPI_SLAVE2
/**
 * The slave parameter the driver should pass to #adi_dm_SPI to access the 3rd DigiMMIC under its control.
 */
#define ADI_DM_DIGIMMIC_SPI_SLAVE2 1
#endif

#ifndef ADI_DM_DIGIMMIC_SPI_SLAVE3
/**
 * The slave parameter the driver should pass to #adi_dm_SPI to access the 4th DigiMMIC under its control.
 */
#define ADI_DM_DIGIMMIC_SPI_SLAVE3 3
#endif

#ifndef ADI_DM_FIRST_PMIC_SPI_SLAVE
/**
 * The slave parameter the driver should pass to #adi_dm_SPI to access the 1st PMIC under its control.
 */
#define ADI_DM_FIRST_PMIC_SPI_SLAVE ADI_DM_NUM_DIGIMMIC
#endif

#ifndef ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND
/**
 * The DigiMMIC SPI peripheral accepts commands with 1, 4, 16 and 64
 * data bytes. Change this define if the host SPI peripheral is restricted
 * in number of data bytes supported. The value must be at least 4.
 */
#define ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND 64
#endif

#if ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND < 4
#   error "ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND must be at least 4."
#endif

/** @name Hardware Abstraction Layer
 * @{
 */
/**
 * Wait for a GPIO to assume a particular value, with timeout.
 *
 * @param[in] dm_num device index
 * @param[in] hPin pin to test
 * @param[in] bValue value to wait for
 * @param[in] nTimeoutNS how long to wait
 * @return ADI_DM_SUCCESS for success, ADI_DM_TIMEOUT for timeout, error codes for other errors
 */
adi_dm_err_t adi_dm_WaitGPIO(uint8_t dm_num, adi_dm_gpio_t hPin, bool bValue, uint32_t nTimeoutNS);

/**
 * Set a GPIO to a particular value.
 *
 * @param[in] dm_num device index
 * @param[in] hPin pin to write
 * @param[in] bValue new state of pin
 */
void adi_dm_WriteGPIO(uint8_t dm_num, adi_dm_gpio_t hPin, bool bValue);

/**
 * Tri-state a GPIO.
 *
 * @param[in] dm_num device index
 * @param[in] hPin pin that we want to tri-state
 */
void adi_dm_ReleaseGPIO(uint8_t dm_num, adi_dm_gpio_t hPin);

/**
 * Delay for nanoseconds.
 *
 * @param[in] nTimeNS time to delay for
 */
void adi_dm_DelayNS(uint32_t nTimeNS);

/**
 * Execute a SPI transfer.
 * The same number of bytes are written and read.
 * Called by @ref HLSPIDriver. The user may opt to provide an
 * implementation for this or for @ref HLSPIDriver.
 *
 * @param[in] slave index of the slave to be accessed
 * @param[in] mosi buffer containing bytes to transmit
 * @param[out] miso buffer to hold recieved bytes
 * @param[in] count the number of bytes to transfer
 **/
void adi_dm_SPI(uint8_t slave, uint8_t mosi[], uint8_t miso[], uint32_t count);

/**
 * Execute a SPI transfer for bitsensing.
 * The same number of bytes are written and read.
 * Called by @ref HLSPIDriver. The user may opt to provide an
 * implementation for this or for @ref HLSPIDriver.
 *
 * @param[in] slave index of the slave to be accessed
 * @param[in] mosi buffer containing bytes to transmit
 * @param[out] miso buffer to hold recieved bytes
 * @param[in] count the number of bytes to transfer
 **/
void adi_dm_SPI_optimize(uint8_t slave, uint32_t bp_idx);
void adi_dm_SPI_VID_optimize(uint8_t slave, uint32_t bp_idx);

/**
 * Write some tracing.
 * For example, this function could output the message to UART.
 * Note though that this function is a debugging tool
 * for the user, there is no *requirement* for it to do
 * anything. It could just return instantly although that
 * would probably make development slower.
 *
 * @param[in] msg message to write
 */
void adi_dm_Log(const char *msg, ...);

/**
 * Power up the supplies.
 * This is the bottom half of Figures 10 and 11 in @cite hrm .
 * 
 * On boards with PMICs it may just be a matter of calling
 * adi_pmic_PowerADAR690x().
 * 
 * @param[in] dm_idx DigMMIC device index
 * @return ADI_DM_SUCCESS for success, error code for errors
 */
adi_dm_err_t adi_dm_PowerUpSupplies(uint8_t dm_idx);

/**
 * Power down the supplies.
 * This is the bottom half of Figures 12 an 13 in @cite hrm .
 * 
 * @param[in] dm_idx DigMMIC device index
 * @return ADI_DM_SUCCESS for success, error code for errors
 */
adi_dm_err_t adi_dm_PowerDownSupplies(uint8_t dm_idx);

/**@}*/

/**
 * @name High level SPI driver
 * @{
 * 
 * These functions issue SPI commands suitable for communicating with a remote
 * DigiMMIC style SPI peripheral, as found in both the DigiMMIC and PMIC.
 * The code supplied with the DigiMMIC driver calls #adi_dm_SPI to pass the
 * formmated command to a local SPI device. The user may opt to provide an
 * implementation for #adi_dm_SPI or for this interface.
 *
 * Note the interface currently assumes communication with only one peripheral
 * at a time.
 */

/**
 * Write to a remote SPI device with ADI SPI slave IP.
 * 
 * @param[in] spi_slave The SPI Slave for the remote device. A number between 0 and ADI_DM_NUM_SPI_SLAVES-1.
 * @param[in] addr 32-bit address on remote device to be written to.
 * @param[in] bytes Number of data bytes to be sent. Must be a number supported by remote device.
 * @param[in] data Array of data to be sent.
 */
void adi_dm_WriteSPI(uint8_t spi_slave, uint32_t addr, int_fast16_t bytes, const uint32_t * data);

/**
 * Read from a remote SPI device with ADI SPI slave IP.
 * 
 * @param[in] spi_slave The SPI Slave for the remote device. A number between 0 and ADI_DM_NUM_SPI_SLAVES-1.
 * @param[in] addr 32-bit address on remote device to be read from.
 * @param[in] bytes Number of data bytes to be received. Must be a number supported by remote device.
 * @param[in] data Array of data to be received.
 * @return ADI_DM_SUCCESS on success or 
 */
adi_dm_err_t adi_dm_ReadSPI(uint8_t spi_slave, uint32_t addr, int_fast16_t bytes, uint32_t * data);

/**
 * Set local model of remote ADI SPI slave IP to power on state.
 * 
 * @param[in] spi_slave The slave number of the connection to be reset.
 */
void adi_dm_ResetSPIConnection(uint8_t spi_slave);

/**
 * Initialize the connection to remote ADI SPI slave IP.
 * 
 * @param[in] spi_slave The slave number of the connection to be reset.
 * @param[in] disable_crc If true disable the CRC checks on the connection.
 */
void adi_dm_InitSPIConnection(uint8_t spi_slave, bool disable_crc);

/**@}*/

#endif                          /* __ADI_DMHAL_H__ */
