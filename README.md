A software for maliciuos gratuitous ARP response detection.
It listens for gratuitous ARP response. When it receives one, it sends an ARP request for the sender IP address of the maliciuos response.
The subsequent response to the request sent by our sender will allow us to understand if the gratuitous response was malicious (if the mac address of the last response is different from the mac address of the gratuitous response) or not.

It uses libpcap.
To be compiled (only on Linux) with -lpcap option.

Usage  ----->  2 options need to be specified:
  1) name of the interface on which start the capture of ARP packets
  2) name of the log file

In the log file, "mac1" is the mac of the legitimate host, while "mac2" is the mac of the (potential) attacker.
