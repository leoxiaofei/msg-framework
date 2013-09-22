#ifndef RCVDUDPPACKET_H__
#define RCVDUDPPACKET_H__

class RcvdUdpPacket
{
public:
	RcvdUdpPacket()
	: ptStream(new std::stringstream){}

	unsigned short      uCurrent;
	unsigned short      uTotal;
	std::tr1::shared_ptr<std::stringstream> ptStream;
};


#endif // RCVDUDPPACKET_H__
