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
		PA_PROT,			///Э������
		PA_APP,				///Ӧ������
		PA_HEARTBEAT		///������
	};

	///Э�鴦��
	enum ProtDisp
	{
		PD_
	};
}


#endif // AGREEMENT_H__
