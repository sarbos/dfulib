// DFU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "DFU.h"
#include <fstream>

using namespace std;

int main()
{
	ifstream firmware;
	
	firmware.open("C:\\Users\\Bash\\Downloads\\lufa\\Demos\\Device\\ClassDriver\\GenericHID\\GenericHID.bin", ios::in | ios::binary| ios::ate);
	const int buf_len = 32000;
	int file_len = firmware.tellg();
	char fw_buf[buf_len];

	firmware.clear();
	firmware.seekg(0, ios::beg);
	firmware.read(fw_buf, file_len);



	DFU test(0x03EB, 0x2FF0);
	test.init();
	test.eraseChip();
	status_response status;
	test.getStatus(status);
	test.blankCheck(status, 0x100, 0x4FF);

	test.programData((uint8_t*)fw_buf, 0x00, file_len, 0);
	test.startApplication(TRUE, 0);

}

