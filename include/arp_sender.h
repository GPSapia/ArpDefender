#ifndef _ARPSENDER_H
#define _ARPSENDER_H

#include "structures.h"

//
//the packet to send
//
char request_packet[42];
char broadcast_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
char my_mac[16];

void construct_packet (uint8_t target_ip_address);

#endif
