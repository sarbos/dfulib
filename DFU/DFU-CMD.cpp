// DFU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "libusb-1.0\libusb.h"
#include "DFU.h"

using namespace std;

int main()
{
	DFU test(0x03EB, 0x2FF0, product::atmega32u2);
	test.init();
	test.eraseChip();
	status_response status;
	test.getStatus(status);
	while (1);
}

