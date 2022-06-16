/*
 * mb_defs.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef MB_DEFS_H_
#define MB_DEFS_H_

/* MODBUS function code =======================================*/
#define MB_FC_READ_COIL						0x01	// Read coils
#define MB_FC_READ_DISCRETE_INPUT			0x02	// Read discrete inputs
#define MB_FC_READ_HOLDING_REG				0x03	// Read holding registers
#define MB_FC_READ_INPUT_REG				0x04	// Read input registers
#define MB_FC_WRITE_SINGLE_COIL				0x05	// Write single coil
#define MB_FC_WRITE_SINGLE_REG				0x06	// Write single register
//#define MB_FC_READ_EXC_STATUS				0x07	// Read exception status (Serial Line Only)
//#define MB_FC_DIAGNOSTIC					0x08	// Diagnostics (Serial Line Only)
//#define MB_FC_GET_COMM_EVENT_COUNTER		0x0B	// Get Comm event counter (Serial Line Only)
//#define MB_FC_GET_COMM_EVENT_LOG			0x0C	// Get Comm event log (Serial Line Only)
#define MB_FC_WRITE_MULTI_COIL				0x0F	// Write multiple coils
#define MB_FC_WRITE_MULTI_REG				0x10	// Write multiple register
//#define MB_FC_REPORT_SERVER_ID				0x11	// Report server ID (Serial Line Only)
//#define MB_FC_READ_FILE_RECORD				0x14	// Read file record
//#define MB_FC_WRITE_FILE_RECORD				0x15	// Write file record
//#define MB_FC_MASK_WRITE_REGISTER			0x16	// Mask write register
//#define MB_FC_READ_WRITE_MULTI_REG			0x17	// Read/write multiple register
//#define MB_FC_READ_FIFO_QUEUE				0x18	// Read FIFO queue
//#define MB_FC_ENCAP_INTERFACE_TRANSPORT		0x2B	// Encapsulated interface transport
//#define MB_FC_READ_DEVICE_ID

#define MB_FC_SUPORT_DEFAULT	{MB_FC_READ_COIL,	\
								 MB_FC_READ_DISCRETE_INPUT,\
								 MB_FC_READ_HOLDING_REG,\
								 MB_FC_READ_INPUT_REG,\
								 MB_FC_WRITE_SINGLE_COIL,\
								 MB_FC_WRITE_SINGLE_REG,\
								 MB_FC_WRITE_MULTI_COIL,\
								 MB_FC_WRITE_MULTI_REG}


/* MODBUS protocol data unit data index */
enum
{
	MB_PDU_ID = 0,
	MB_PDU_FUNC,
	MB_PDU_ADDR_HI,
	MB_PDU_ADDR_LO,
	MB_PDU_QTY_HI,
	MB_PDU_QTY_LO,
	MB_PDU_CNT
};

/* Exception funciton code */
#define MB_EXC_FUNC			0x01
#define MB_EXC_ADDR_RANGE	0x02
#define MB_EXC_REG_QTY	    0x03
#define MB_EXC_EXECUTE		0x04


#endif /* MB_DEFS_H_ */
