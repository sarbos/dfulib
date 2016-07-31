#ifndef DFU_H
#define DFU_H

#include "stdint.h"
#include "libusb-1.0\libusb.h"

//All DFU based Commands

#define REQUEST_TYPE_TO_HOST	0xA1
#define REQUEST_TYPE_TO_DEVICE	0x21

typedef enum e_dfu_request
{
	detach = 0,
	dnload,
	upload,
	get_status,
	clr_status,
	get_state,
	abort_dfu
} dfu_request_type;

typedef enum e_dfu_status 
{
	OK = 0,
	errTARGET,
	errFILE,
	errWRITE,
	errERASE,
	errCHECK_ERASED,
	erPROG,
	errVERIFY,
	errADDRESS,
	errNOTDONE,
	errFIRMWARE,
	errVENDOR,
	errUSBR,
	errPOR,
	errUNKNOWN,
	errSTALLEDPK
}dfu_status;

typedef enum e_dfu_state 
{
	appIDLE = 0,
	appDETACH,
	dfuIDLE,
	dfuDNLOAD_SYNC,
	dfuDNBUSY,
	dfuDNLOAD_IDLE,
	dfuMANIFEST_SYNC,
	dfuMANIFEST_WAIT_RESET,
	dfuUPLOAD_IDLE,
	dfuERROR
}dfu_state;


typedef enum e_dfu_error
{
	USB_OK = 0,
	USB_IO = -1,
	USB_INVALID_PARAM = -2,
	USB_ACCESS = -3,
	USB_NO_DEVICE = -4,
	USB_NOT_FOUND = -5,
	USB_BUSY = -6,
	USB_TIMEOUT = -7,
	USB_OVERFLOW = -8,
	USB_PIPE = -9,
	USB_INTERRUPTED = -10,
	USB_NO_MEM = -11,
	USB_NOT_SUPPORTED = -12,
	USB_OTHER = -99
	
}dfu_error;

typedef struct status_response_t
{
	dfu_status status;
	uint32_t poll_timeout;
	dfu_state state;
	uint32_t string_index;

}status_response;


/*
DFU file suffix
Members are reverse of DFU specification because all offsets are negative, and appear at the end of the file.
*/
typedef struct file_suffix_t 
{
	uint16_t bcdDevice;
	uint16_t idProduct;
	uint16_t idVendor;
	uint16_t bcdDFU = 0x0100;
	uint8_t  ucDfuSignature_0 = 0x55;
	uint8_t  ucDfuSignature_1 = 0x46;
	uint8_t  ucDfuSignature_2 = 0x44;
	uint8_t  bLength = 16;
	uint32_t dwCRC;

}file_suffix;


class DFU
{
	uint16_t vid;
	uint16_t pid;
	libusb_context *ctx = NULL; //a libusb session
	libusb_device_handle *dev_handle;

public:

	DFU();
	DFU(uint16_t vid, uint16_t pid);
	DFU(uint16_t vid, uint16_t pid, libusb_device_handle* dev_handle);

	dfu_error init();

	~DFU();

	dfu_error detach(int timeout);

	dfu_error download(uint8_t* data, int length, int block);

	dfu_error upload(uint8_t* data, int length, int block);

	dfu_error getStatus(status_response &status);

	dfu_error clearStatus();

	dfu_error getState(dfu_state &state);

	dfu_error abortDFU();

	dfu_error programData(uint8_t* data, uint16_t start, uint16_t length, uint8_t memory);

	dfu_error readData(uint8_t* data, uint16_t start, uint16_t end, uint8_t memory);

	dfu_error blankCheck(status_response &status, uint16_t start, uint16_t end);
	
	dfu_error eraseChip();

	dfu_error readConfig(uint16_t command, uint8_t* data);

	dfu_error startApplication(bool reset, uint16_t address);

};

#endif