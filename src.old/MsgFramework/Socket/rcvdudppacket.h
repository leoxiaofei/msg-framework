#ifndef RCVDUDPPACKET_H__
#define RCVDUDPPACKET_H__


class RcvdUdpPacket
{
public:
	unsigned short      uCurrent;
	unsigned short      uTotal;
	std::vector<char>*  pData;
};

#endif // RCVDUDPPACKET_H__
