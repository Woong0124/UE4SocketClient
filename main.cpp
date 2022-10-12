#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>



int main()
{
	// Winsock 로드
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "Winsock Error : " << GetLastError() << std::endl;
		exit(-1);
	}

	// Socket 생성
	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "fail create Socket : " << GetLastError() << std::endl;
		exit(-1);
	}

	// 연결할 서버 요소
	SOCKADDR_IN ServerSOCKADDR;
	memset(&ServerSOCKADDR, 0, sizeof(SOCKADDR_IN));
	ServerSOCKADDR.sin_family = PF_INET;
	ServerSOCKADDR.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSOCKADDR.sin_port = htons(3307);

	// Socket 연결
	int Result = connect(ClientSocket, (SOCKADDR*)&ServerSOCKADDR, sizeof(SOCKADDR_IN));
	if (Result == SOCKET_ERROR)
	{
		std::cout << "fail connect : " << GetLastError() << std::endl;
		exit(-1);
	}





	// Send / Recive
	char SendBuffer[] = "";
	char RecvBuffer[1024] = { 0 };





	// Socket 해제
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}