#include "stdafx.h"


monitorClient::monitorClient(const char* _configData)
{
	loadConfig(_configData);
	serverNo = 2;
	Start(bufCode, bufKey1,bufKey2);
}

monitorClient::~monitorClient(void)
{
	Stop();
}

void monitorClient::proc_clientLogin()
{
	Sbuf *buf = packet_clientLogin();
	SendPacket(buf);
	buf->Free();
}

void monitorClient::proc_sendData(BYTE _dataType, int _dataValue, int _timeStamp)
{
	Sbuf *buf = packet_sendData(_dataType, _dataValue, _timeStamp);
	SendPacket(buf);
	buf->Free();
}

Sbuf* monitorClient::packet_clientLogin()
{
	//		WORD	Type
	//
	//		int		ServerNo		// ���� Ÿ�� ���� �� �������� ���� ��ȣ�� �ο��Ͽ� ���

	Sbuf *buf = Sbuf::Alloc();
	*buf << (WORD)en_PACKET_SS_MONITOR_LOGIN;
	*buf << serverNo;
	 
	return buf;
}

Sbuf* monitorClient::packet_sendData(BYTE _dataType, int _dataValue, int _timeStamp)
{
	//		WORD	Type
	//
	//		BYTE	DataType				// ����͸� ������ Type �ϴ� Define ��.
	//		int		DataValue				// �ش� ������ ��ġ.
	//		int		TimeStamp				// �ش� �����͸� ���� �ð� TIMESTAMP  (time() �Լ�)

	Sbuf *buf = Sbuf::Alloc();
	*buf << (WORD)en_PACKET_SS_MONITOR_DATA_UPDATE;
	*buf << _dataType;
	*buf << _dataValue;
	*buf << _timeStamp;

	return buf;
}

void monitorClient::OnClientJoin(void) 
{
	proc_clientLogin();
}

void monitorClient::OnClientLeave(void)
{
	loginFlag = false;
}

void monitorClient::OnRecv(Sbuf *_buf) {  }
bool monitorClient::OnConnectionRequest(void) { return true; }
void monitorClient::OnSend(int _sendSize) {  }
void monitorClient::OnError(int _errorCode, WCHAR *_string) {  }
void monitorClient::OnTPS(void) {  }

void monitorClient::loadConfig(const char *_buffer)
{
	// config ���� �о�ͼ� ��� ������ �� ����.
	rapidjson::Document Doc;
	Doc.Parse(_buffer);

	// IP Adress, port, maxCount, threadCount
	// DB ����
	char dummyIP[16];
	rapidjson::Value &sev = Doc["MONITOR_CLIENT"];
	strcpy_s(dummyIP, sev["SERVER_IP"].GetString());
	MultiByteToWideChar(CP_ACP, 0, dummyIP, 16, ip, 16);
	port = sev["SERVER_PORT"].GetUint();
	nagleOpt = sev["NAGLE"].GetBool();
	threadCount = sev["WORKER_THREAD"].GetUint();
	serverNo = sev["SERVER_NO"].GetInt();

	rapidjson::Value &code = sev["BUF_KEY"];
	assert(arry.IsArry());

	bufCode = (char)code[0].GetInt();
	bufKey1 = (char)code[1].GetInt();
	bufKey2 = (char)code[2].GetInt();
}

void monitorClient::shutdownServer(void)
{
	printf("recv shotdown server");
	return;
}

