#pragma once

class gameServer;

enum playerStatus
{
	NONE, MOVE, ATTACK, ATTACK_MOVE
};


class player : public GameSession
{
public:
	INT64 accountNo;
	char sessionKey[64];

	WCHAR id[dfID_MAX_LEN];
	WCHAR nickName[dfNICK_MAX_LEN];

	// ��Ÿ �ʿ� �������� ������ �߰�.
public:
	player();
	~player();



	// �����Լ�
		// auth
		void proc_loginReq(Sbuf *_buf);

		// game
		void proc_echo(Sbuf *_buf);

	// ��Ŷ �Լ�
	Sbuf* packet_loginRes(BYTE _status);
	Sbuf *packet_echo(INT64 _acNo, LONGLONG _sendTick);

	// �����Լ�
	void onAuth_clientJoin(void);
	void onAuth_clientLeave(void);
	void onAuth_Packet(Sbuf *_buf);

	void onGame_clientJoin(void);
	void onGame_clientLeave(void);
	void onGame_Packet(Sbuf *_buf);

	void onGame_Release(void);

	friend class gameServer;
};