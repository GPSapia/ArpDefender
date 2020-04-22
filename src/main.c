#include "../include/arp_capture.h"
#include "../include/packets_storage.h"
//for debugging purposes
#include "../include/utils.h"

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

  char mac[16];
  get_mac_address (mac);
  printf("%s\n", mac);

  return 0;
}
