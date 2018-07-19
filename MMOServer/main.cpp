// GameServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

long CCrashDump::_DumpCount = 0;
char* loadFile(const char *_fileName)
{
	FILE *fp;
	printf("Loding [%s]..\t", _fileName);
	fopen_s(&fp, _fileName, "rb");
	if (!fp)
	{
		printf("fail\n");
		printf("���� �̸� ���� [%s]\n", _fileName);
		fclose(fp);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *buffer = new char[(fileSize + 1)];
	size_t test = fread(buffer, fileSize, 1, fp);
	if (test == 0)
	{
		printf("fail\n");
		printf("���� �б� ���� [%s]\n", _fileName);
		delete[] buffer;
		fclose(fp);
		return NULL;
	}
	printf("complete\n");
	buffer[fileSize] = '\0';
	fclose(fp);
	return buffer;
}

int main()
{
	CCrashDump dump;
	char ControlKey;
	const char* data = loadFile("game.ini");
	GAMEServer *server = new GAMEServer(data);
	timeBeginPeriod(1);
	while (1)
	{
		ControlKey = _getwch();
		if (ControlKey == L'S' || ControlKey == L's')
		{
			server->Start(data);
		}
		if (ControlKey == L'Z' || ControlKey == L'z')
		{
			proSaveFile();
		}
		Sleep(1000);
	}
	timeEndPeriod(1);
	delete data;
	delete server;
	return 0;
}

