#ifndef RCVDTCPPACKET_H__
#define RCVDTCPPACKET_H__


class RcvdTcpPacket
{
public:
	unsigned int      uCurrent;
	unsigned int      uTotal;
	std::tr1::shared_ptr<std::stringstream> ptStream;
};

#endif // RCVDTCPPACKET_H__
