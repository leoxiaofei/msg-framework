#ifndef TCPPACKET_H__
#define TCPPACKET_H__


struct TcpPacket
{
	unsigned int        uSize;
	unsigned short      sType;
};

struct SendTcpPacket
{
	unsigned int               uOrder;
	unsigned int               uCur;
	std::vector<unsigned char> vecData;
};

#endif // TCPPACKET_H__
