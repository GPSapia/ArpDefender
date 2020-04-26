#ifndef _ARPSENDER_H
#define _ARPSENDER_H

#include "arp_capture.h"

//
//the packet to send
//
char request_packet[42];

char broadcast_mac[6];
char arp_type[2];
char ethernet_type[2];
char prot_type[2];
char addr_length;
char proto_length;
char op_code[2];

void init_packet_fields();
void construct_packet (uint8_t* target_ip_address);
void send_packet(uint8_t* target_ip_address);                                                             //every thread should call it

#endif
