#ifndef AGREEMENT_H__
#define AGREEMENT_H__

namespace Agreement
{
	///Э����Ϊ
	enum ProtAct { 
		PA_CONNECT,			///������Ϣ
		/// �㲥
		PA_ONLINE,			///����
		PA_OFFLINE,			///���� 
		PA_CALL,			///��ѯ����״̬
		/// ����
		PA_HERE,			///���߻�ִ
		PA_PROT_REQ,		///Э������
		PA_PROT_RESP,		///Э��Ӧ��
		PA_APP,				///Ӧ����Ϣ
		PA_HEARTBEAT		///������
	};

	///Э�鴦��
	enum ProtDisp
	{
		PD_ZLIB,
		PD_XOR,
		PD_VERSION
	};
}


#endif // AGREEMENT_H__
