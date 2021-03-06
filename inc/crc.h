/*
 * crc16.h
 *
 *  Created on: 18/03/2014
 *      Author: Renato Coral Sampaio
 */

#ifndef CRC16_H_
#define CRC16_H_

#define CRC_SIZE 2

short CRC16(short crc, char data);
short calcula_CRC(unsigned char *commands, int size);
int crc_error(unsigned char *buffer, int size);

#endif /* CRC16_H_ */
