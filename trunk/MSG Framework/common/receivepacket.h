#ifndef RECEIVEPACKET_H__
#define RECEIVEPACKET_H__


class ReceivePacket
{
public:
	ReceivePacket()
	: ptStream(new std::stringstream){}

	unsigned short      uCurrent;
	unsigned short      uTotal;
	std::tr1::shared_ptr<std::stringstream> ptStream;
};


#endif // RECEIVEPACKET_H__
