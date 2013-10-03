#include "stdafx.h"
#include "udpsession.h"

#include "../Tools/MsgObjectPool.hpp"
#include "rcvdudppacket.h"
#include "udppacket.h"


#include <queue>


class UdpSession::Impl
{
public:
	Impl(MsgObjectPool<UdpPacket> &pool):mopPackPool(pool){}
	std::map<unsigned int, RcvdUdpPacket> mapReceiveData;
	std::map<unsigned int, unsigned int> mapTimeOut;
	std::queue<UdpPacket*> quReadyData;

	MsgObjectPool<UdpPacket> &mopPackPool;

	boost::asio::ip::udp::endpoint epSend;
	FuncSend funcSend;
	FuncReceive funcReceive;
};

UdpSession::UdpSession(MsgObjectPool<UdpPacket> &mopPackPool)
: m_pImpl(new Impl(mopPackPool))
{

}

UdpSession::~UdpSession()
{

}

void UdpSession::Clear()
{
	m_pImpl->mapReceiveData.clear();
	m_pImpl->mapTimeOut.clear();
	while(!m_pImpl->quReadyData.empty())
	{
		m_pImpl->mopPackPool.Recycle(m_pImpl->quReadyData.front());
		m_pImpl->quReadyData.pop();
	}
}

void UdpSession::ReceiveData( const char* szData, std::size_t packet_bytes )
{
	UdpPacket* pData = m_pImpl->mopPackPool.New();
	if (pData == NULL)
	{
		pData = new UdpPacket;
	}
	memcpy_s(pData, sizeof(UdpPacket), szData, packet_bytes);
	do
	{
		if(!CheckPacket(pData))
		{
			break;
		}

		if ( pData->uUsed == 0 ) ///Ӧ���
		{
			UdpPacket* p = m_pImpl->quReadyData.front();

			if (   p->uOrder   == pData->uOrder
				&& p->uCurrent == pData->uCurrent 
				&& p->uTotal   == pData->uTotal )
			{
				m_pImpl->quReadyData.pop();
				m_pImpl->mopPackPool.Recycle(p);

				if (!m_pImpl->quReadyData.empty())
				{
					///������һ������
					m_pImpl->funcSend(m_pImpl->quReadyData.front(), m_pImpl->epSend);
				}
			}
			
		}
		else  ///���ݰ�
		{
			///��������
			std::map<unsigned int, RcvdUdpPacket>::iterator iFind = 
				m_pImpl->mapReceiveData.find(pData->uOrder);
			if(iFind == m_pImpl->mapReceiveData.end())
			{
				///������
				if (pData->uCurrent != 1)
				{
					break;
				}
				RcvdUdpPacket& rPacket = m_pImpl->mapReceiveData[pData->uOrder];
				rPacket.uCurrent = pData->uCurrent;
				rPacket.uTotal   = pData->uTotal;
				rPacket.ptStream->write((char*)pData->szData, pData->uUsed);
			}
			else
			{
				///��������
				RcvdUdpPacket& rPacket = iFind->second;
				if (pData->uTotal != rPacket.uTotal)
				{
					break;
				}
				if (rPacket.uCurrent < pData->uCurrent)
				{
					assert(rPacket.uCurrent + 1 == pData->uCurrent);
					rPacket.uCurrent = pData->uCurrent;
					rPacket.ptStream->write((char*)pData->szData, pData->uUsed);
				}
			}
			CheckEmitReceive(pData->uOrder);
			///����Ӧ����Ϣ
			pData->uUsed = 0;
			m_pImpl->funcSend(pData, m_pImpl->epSend);
		}
	}while(0);

	m_pImpl->mopPackPool.Recycle(pData);
}

void UdpSession::SetSendFunc( const FuncSend& pFunc )
{
	m_pImpl->funcSend = pFunc;
}

bool UdpSession::CheckPacket( UdpPacket* packet )
{
	bool bRet(false);

	do 
	{
		if (   packet->uOrder == 0
			|| packet->uTotal == 0
			|| packet->uCurrent == 0 )
		{
			break;
		}

		if ( packet->uCurrent > packet->uTotal )
		{
			break;
		}

		if ( packet->uUsed > SPLIT_SIZE )
		{
			break;
		}

		bRet = true;

	} while (0);

	return bRet;
}

void UdpSession::CheckEmitReceive( unsigned int uOrder )
{
	std::map<unsigned int, RcvdUdpPacket>::iterator iFind = 
		m_pImpl->mapReceiveData.find(uOrder);
	if(iFind != m_pImpl->mapReceiveData.end())
	{
		RcvdUdpPacket& rPacket = iFind->second;
		if (rPacket.uCurrent == rPacket.uTotal)
		{
			///TODO:�����յ���Ϣ���ύ����
			//m_pImpl->sigReceiveData(uOrder, rPacket.ptStream);
			m_pImpl->funcReceive(rPacket.ptStream, m_pImpl->epSend);
			m_pImpl->mapReceiveData.erase(iFind);
		}
	}
}

void UdpSession::SetEndPoint( const boost::asio::ip::udp::endpoint& point )
{
	m_pImpl->epSend = point;
}

void UdpSession::SendData( unsigned int uOrder, const char* szData, std::size_t packet_bytes )
{
	bool bSend = m_pImpl->quReadyData.empty();
	SplitPacket(uOrder, szData, packet_bytes, m_pImpl->quReadyData);
	if(bSend)
	{
		m_pImpl->funcSend(m_pImpl->quReadyData.front(), m_pImpl->epSend);
	}
}

void UdpSession::SplitPacket( unsigned int uOrder, const void* szData, 
	unsigned int uSize, std::queue<UdpPacket*>& queData )
{
	unsigned int uPos(0);
	unsigned int uCopy(0);
	unsigned int uTotal = uSize / SPLIT_SIZE + 1;
	unsigned int uCurrent(0);

	do 
	{
		UdpPacket* pData = m_pImpl->mopPackPool.New();
		if (pData == NULL)
		{
			pData = new UdpPacket;
		}

		pData->uOrder = uOrder;
		pData->uCurrent = ++uCurrent;
		pData->uTotal = uTotal;
		uCopy = uTotal == uCurrent ? uSize - uPos: SPLIT_SIZE;
		pData->uUsed = uCopy;
		memcpy_s(pData->szData, SPLIT_SIZE, (unsigned char*)szData + uPos, uCopy);
		uPos += uCopy;

		queData.push(pData);

	} while (uPos < uSize);

}

void UdpSession::SetReceiveFunc( const FuncReceive& pFunc )
{
	m_pImpl->funcReceive = pFunc;
}

