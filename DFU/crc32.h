#pragma once
#ifndef _CRC32_H_
#define _CRC32_H_

#include <stdint.h>

/***************************************************************************
CRC polynomial 0xedb88320 – Contributed unknowingly by Gary S. Brown.
"Copyright (C) 1986 Gary S. Brown. You may use this program, or code or
tables extracted from it, as desired without restriction."
Paraphrased comments from the original:
The 32 BIT ANSI X3.66 CRC checksum algorithm is used to compute the 32-bit
frame check sequence in ADCCP. (ANSI X3.66, also known as FIPS PUB 71 and
FED-STD-1003, the U.S. versions of CCITT's X.25 link-level protocol.)
USB Device Firmware Upgrade Specification, Revision 1.1
43
The polynomial is:
X^32+X^26+X^23+X^22+X^16+X^12+X^11+X^10+X^8+X^7+X^5+X^4+X^2+X^1+X^0
Put the highest-order term in the lowest-order bit. The X^32 term is
implied, the LSB is the X^31 term, etc. The X^0 term usually shown as +1)
results in the MSB being 1. Put the highest-order term in the lowest-order
bit. The X^32 term is implied, the LSB is the X^31 term, etc. The X^0
term (usually shown as +1) results in the MSB being 1.
The feedback terms table consists of 256 32-bit entries. The feedback
terms
simply represent the results of eight shift/xor operations for all
combinations of data and CRC register values. The values must be right-
shifted by eight bits by the UPDCRC logic so the shift must be unsigned.
***************************************************************************/
extern unsigned long _crctbl[];

#define _crc(accum,delta) (accum)=_crctbl[((accum)^(delta))&0xff]^((accum)>>8)
/***************************************************************************
The updcrc macro (referred to here as _crc) is derived from an article
Copyright © 1986 by Stephen Satchell.
“Programmers may incorporate any or all code into their programs, giving
proper credit within the source. Publication of the source routines is
permitted so long as proper credit is given to Steven Satchell, Satchell
Evaluations, and Chuck Forsberg, Omen technology."
*************************************************************************/




uint32_t calc_CRC(uint8_t* data, int length);

#endif