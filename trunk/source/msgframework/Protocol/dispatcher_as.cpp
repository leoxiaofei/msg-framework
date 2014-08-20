#include "stdafx.h"
#include "dispatcher.h"

#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>

#include "../Common/trafficdata.h"


void Dispatcher::as_ReceiveUdpData(const TrafficData& tfcData, unsigned int uNetId)
{
	GetIOs().post(boost::bind(&Dispatcher::ReceiveUdpData, this, tfcData, uNetId));

}
