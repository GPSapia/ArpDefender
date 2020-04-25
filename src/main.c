#include "../include/arp_capture.h"
#include "../include/packets_storage.h"
//for debugging purposes
#include "../include/utils.h"
#include "../include/arp_sender.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "%s\n","interface not specified");
    exit(1);
  }

  init_pcap(argv[1]);
  /*start_capture();

  print_responses();

  end_capture();*/

  /*char mac[16];
  get_mac_address (mac);
  printf("%s\n", mac);
  */
  uint8_t ip_addr[4] = {192, 168, 1, 1};

  init_packet_fields();
  construct_packet (ip_addr);
    send_packet();

  return 0;
}
