#ifndef RCVDTCPPACKET_H__
#define RCVDTCPPACKET_H__


class RcvdTcpPacket
{
public:
	unsigned int       uCurrent;
	unsigned int       uTotal;
	std::vector<char>* pData;
};

#endif // RCVDTCPPACKET_H__
