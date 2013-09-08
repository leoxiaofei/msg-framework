#ifndef UDPPACKET_H__
#define UDPPACKET_H__

#define SPLIT_SIZE 1014

struct UdpPacket
{
	unsigned int        uOrder;
	unsigned short      uCurrent;
	unsigned short      uTotal;
	unsigned short      uUsed;
	unsigned char       szData[SPLIT_SIZE];
};



#endif // UDPPACKET_H__
