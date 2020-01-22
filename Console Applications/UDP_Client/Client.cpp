/*

	Demonstrate UDP CLIENT-SERVER applictaion using winsock liberary

	@Author - Akshay Bodhankar
			  akshaybodhankar2197@gmail.com

	@Title - Windows_System_Programing [ CLIENT-APPLICATION ]


*/
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <winsock.h>
#define MAXBUFF 255

#pragma comment(lib,"Ws2_32.lib")
int _tmain()
{
	WSADATA data;
	SOCKET sock;
	SOCKADDR_IN addr;
	int size_a = sizeof(addr);
	int ret;
	char buff[MAXBUFF] = { '\0' };


	//entry for socket into operating system
	WSAStartup(MAKEWORD(2, 2), &data);

	//Creating the socket for establishing connection
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		printf("Socket failed: [%d].\n", GetLastError());
		WSACleanup();
		return -1;
	}

	//get the sock_addr structure
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8080);
	addr.sin_family = AF_INET;
	



	//copying the data to send to the server.
	//strcpy_s(buff, "Hello from akshuab");

	//Getting message from the user for sending to server.
	printf("Enter the data you want to send to server: ");

	//scaning the string upto new line.
	scanf_s("%[^\n]s", buff, (unsigned)_countof(buff));


	//sendto function sends data to the server according to address stored in sock_addr.
	ret = sendto(sock, buff, strlen(buff), 0, (sockaddr*)&addr, size_a);
	if (ret < 0)
	{
		printf("sendto failed: [%d].\n", GetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	//setting buffer to null
	memset(buff, '\0', MAXBUFF);

	//The recvfrom function recives the data from server
	ret = recvfrom(sock, buff, MAXBUFF, 0, (sockaddr*)&addr, &size_a);
	if (ret < 0)
	{
		printf("recvfrom failed: [%d].\n", GetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	//printing message recived from server
	printf("The reciver data is [%s].\n", buff);

	//closing the socket
	closesocket(sock);
	WSACleanup();
	return 0;
}