#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <stdint.h>
#include <stdlib.h>

#define ETHERNET_ADDRESS_LENGTH 6
#define NIC_NAME_LENGTH 30
#define ARP_ETHERNET_HEADER_LEN 14

struct arp_response {
  struct arp_response* next;
  uint8_t ip_address[4];
  uint8_t mac[ETHERNET_ADDRESS_LENGTH];
};

struct request_item {
  struct request_item* next;
  uint8_t ip_address[4];
};

struct arp_header {
    unsigned short int ar_hrd;		/* Format of hardware address.  */
    unsigned short int ar_pro;		/* Format of protocol address.  */
    unsigned char ar_hln;		      /* Length of hardware address.  */
    unsigned char ar_pln;		      /* Length of protocol address.  */
    unsigned short int ar_op;		  /* ARP opcode (command).  */
}__attribute__((packed));

struct arp_packet {
	struct arp_header header;		                        /* fixed-size header */
	uint8_t sender_mac_address[ETHERNET_ADDRESS_LENGTH];	/* sender hardware address */
	uint8_t sender_ip_address[4];		                      /* sender protocol address */
	uint8_t target_mac_address[ETHERNET_ADDRESS_LENGTH];	/* target hardware address */
	uint8_t target_ip_address[4];		                      /* target protocol address */
}__attribute__((packed));

#endif
