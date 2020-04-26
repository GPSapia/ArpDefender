#include "../include/arp_sender.h"


void init_packet_fields()
{
  for (size_t i = 0; i < 6; i++)
    broadcast_mac[i] = 0xFF;
  arp_type[0] = 0x08;
  arp_type[1] = 0x06;
  ethernet_type[0] = 0x00;
  ethernet_type[1] = 0x01;
  prot_type[0] = 0x08;
  prot_type[1] = 0x00;
  addr_length = 6;
  proto_length = 4;
  op_code[0] = 0x00;
  op_code[1] = 0x01;
  get_mac_address(my_mac);
}


void construct_packet (uint8_t* target_ip_address)
{

    char type[2] = {0x08, 0x06};

    memset (request_packet, 0, 42);

    memcpy (request_packet, broadcast_mac, 6);                  //destination mac (broadcast)
    memcpy (request_packet+6, my_mac, 6);                       //source mac
    memcpy (request_packet+12, arp_type, 2);                    //type
    memcpy (request_packet+14, ethernet_type, 2);               //hardware type
    memcpy (request_packet+16, prot_type, 2);                   //protocol type
    memcpy (request_packet+18, &addr_length, 1);                //mac address length
    memcpy (request_packet+19, &proto_length, 1);               //ip address length
    memcpy (request_packet+20, &op_code, 2);                    //request op code
    memcpy (request_packet+22, my_mac, 6);                      //my mac address
    memcpy (request_packet+28, local_if_address, 4);            //my ip address
    memcpy (request_packet+32, broadcast_mac, 6);               //target mac address
    memcpy (request_packet+38, target_ip_address, 4);           //target ip address
}

void send_packet(uint8_t* target_ip_address)
{
    construct_packet(target_ip_address);
    if (pcap_inject(capture_session, request_packet, 42) == -1)
      printf("%s\n", "errore");
}
