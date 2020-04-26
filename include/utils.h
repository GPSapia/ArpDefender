#ifndef _UTILS_H
#define _UTILS_H

#include "arp_capture.h"
#include <arpa/inet.h>

void get_interface_ip(uint8_t* iface_address);
bool compare_addresses (uint8_t* first_address, uint8_t* second_address);
bool compare_mac (uint8_t* first_mac, uint8_t* second_mac);
void get_mac_address(char* mac);

#endif
