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
		PA_PROT,			///协议请求
		PA_APP,				///应用请求
		PA_HEARTBEAT		///心跳包
	};

	///协议处理
	enum ProtDisp
	{
		PD_
	};
}


#endif // AGREEMENT_H__
