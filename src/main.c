#include "../include/arp_capture.h"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "%s\n","interface or log file not specified");
    exit(1);
  }

  init_pcap(argv[1], argv[2]);
  start_capture();

  end_capture();

  return 0;
}
