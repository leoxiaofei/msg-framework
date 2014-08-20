#ifndef AGREEMENT_H__
#define AGREEMENT_H__

namespace Agreement
{
	///协议行为
	enum ProtAct { 
		PA_CONNECT,			///连接消息
		/// 广播
		PA_ONLINE,			///上线
		PA_OFFLINE,			///离线 
		PA_CALL,			///查询在线状态
		/// 单播
		PA_HERE,			///在线回执
		PA_PROT_REQ,		///协议请求
		PA_PROT_RESP,		///协议应答
		PA_APP,				///应用消息
		PA_HEARTBEAT		///心跳包
	};

	///协议处理
	enum ProtDisp
	{
		PD_ZLIB,
		PD_XOR,
		PD_VERSION
	};
}


#endif // AGREEMENT_H__
