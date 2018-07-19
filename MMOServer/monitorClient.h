#pragma once

class gameServer;

class monitorClient : public LanClient
{
private:
	gameServer *server;
	int serverNo;

	BYTE bufCode;
	BYTE bufKey1;
	BYTE bufKey2;
public:
	bool loginFlag;

private:
	void loadConfig(const char* _buffer);

	void proc_clientLogin();


	Sbuf* packet_clientLogin();
	Sbuf* packet_sendData(BYTE _dataType, int _dataValue, int _timeStamp);
	
public:
	monitorClient(const char *_configData);
	~monitorClient();

	// �����Լ�
	void shutdownServer(void);

	void proc_sendData(BYTE _dataType, int _dataValue, int _timeStamp);

	// �����Լ�
	virtual void OnClientJoin(void);
	virtual void OnClientLeave(void);
	virtual bool OnConnectionRequest(void); // accept �� [false : Ŭ���̾�Ʈ �ź� / true : ���� ���]
	virtual void OnRecv(Sbuf *_buf);		// ���� �Ϸ� ��
	virtual void OnSend(int _sendSize);	// �۽� �Ϸ� ��
	virtual void OnError(int _errorCode, WCHAR *_string);		// �����޼��� ����
	virtual void OnTPS(void);
};
