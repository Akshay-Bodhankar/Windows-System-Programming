/*

	Demonstrate TCP CLIENT-SERVER applictaion using winsock liberary

	@Author - Akshay Bodhankar
			  akshaybodhankar2197@gmail.com

	@Title - Windows_System_Programing [ CLIENT-APPLICATION ]


*/
#include <Windows.h>
#include <stdio.h>
#include <winsock.h>
#include <tchar.h>

#define MAXBUFF 255

#pragma comment(lib,"Ws2_32.lib")

int _tmain()
{
	WSADATA data;
	SOCKET sock;
	SOCKADDR_IN addr;
	int ret;
	char buff[MAXBUFF] = { '\0' };

	//Entry for socket.
	WSAStartup(MAKEWORD(2, 2), &data);
	printf("\t\t\tTCP CLIENT\n");

	//Creating socket for connection.
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		printf("socket failed: %d.\n", GetLastError());
		return -1;
	}

	//getting sock_addr structure and filling all details.
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8080);
	addr.sin_family = AF_INET;

	//The connect function establish a conection to specific socket.
	ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
	{
		printf("Connection failed : %d.\n", GetLastError());
		closesocket(sock);
		return -1;
	}
	printf("Connection established....\n");

	//getting message from the user for sending to server.
	printf("Enter the data to send: ");
	scanf_s("%[^\n]s", buff,(unsigned)_countof(buff));

	printf("Data entered is [%s].\n", buff);

	//The send function send the message to particular socket which it is connected.
	ret = send(sock, buff, strlen(buff), 0);
	if (ret < 0)
	{
		printf("Send failed: %d.\n", GetLastError());
		closesocket(sock);
		return -1;
	}
	printf("Data sent sucessfully...!!!\n");

	memset(buff, '\0', MAXBUFF);
	//The recv function recvives the message to particular socket which it is connected.
	ret = recv(sock, buff, sizeof(buff), 0);
	if (ret < 0)
	{
		printf("recv failed: %d.\n", GetLastError());
		closesocket(sock);
		return -1;
	}
	printf("Data recived sucessfully...!!!\n");

	//message
	printf("Data recived from Server [%s]", buff);

	//closing the connection.
	closesocket(sock);
	WSACleanup();
	return 0;
}