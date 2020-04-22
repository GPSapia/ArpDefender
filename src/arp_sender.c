#include "../include/arp_sender.h"
#include <string.h>

void construct_packet (uint8_t target_ip_address)
{
    get_mac_address(my_mac);
    char type = {0x08, 0x06};

    memset (request_packet, 0, 42);
    memcpy (request_packet, broadcast_mac, 6);
    //source mac                                                                //CONVERT IT TO HEXADECIMAL!!!!!
    memcpy (request_packet+6, (unsigned char) strtol (my_mac, 2);
    memcpy (request_packet+8, my_mac+3, 2);
    memcpy (request_packet+10, my_mac+6, 2);
    memcpy (request_packet+12, my_mac+9, 2);
    memcpy (request_packet+14, my_mac+12, 2);
    memcpy (request_packet+16, my_mac+15, 2);
    //I'm not so sure about it (type)
    memcpy (request_packet+18, type, 2);
}
