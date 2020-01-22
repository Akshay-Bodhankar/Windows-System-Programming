/*

	Demonstrate UDP CLIENT-SERVER applictaion using winsock liberary

	@Author - Akshay Bodhankar
			  akshaybodhankar2197@gmail.com

	@Title - Windows_System_Programing [ SERVER-APPLICATION ]


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
	SOCKADDR_IN saddr;

	//get the structure length.
	int size_a = sizeof(saddr);
	int ret;
	char buff[MAXBUFF] = { '\0' };

	//entry for socket into operating system.
	WSAStartup(MAKEWORD(2, 2), &data);

	//Creating the socket for establishing connection.
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		printf("Socket failed: [%d].\n", GetLastError());
		WSACleanup();
		return -1;
	}
	printf("Socket created sucesfully...\n");

	//get the sock_addr structure
	saddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(8080);
	saddr.sin_family = AF_INET;

	//The bind function binds the specific port number and ip to the socket.
	ret = bind(sock, (sockaddr*)&saddr, size_a);
	if (ret < 0)
	{
		printf("Bind failed: [%d].\n", GetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	printf("Bind successful...\n");

	//server started
	printf("Waiting.........\n\n");
	while (1)
	{
		//The recvfrom function recives the datagram and stores the source address.
		ret = recvfrom(sock, buff, MAXBUFF, 0, (sockaddr*)&saddr, &size_a);
		if (ret < 0)
		{
			printf("Recv from failed: [%d].\n", GetLastError());
			closesocket(sock);
			WSACleanup();
			return -1;
		}
		printf("Recvform successful....\n\n");

		//data recived from client.
		printf("Data recived: [%s].\n", buff);

		//sending same data to client as a server message.
		ret = sendto(sock, buff, strlen(buff), 0, (sockaddr*)&saddr, size_a);
		if (ret < 0)
		{
			printf("Send to failed: [%d].\n", GetLastError());
			closesocket(sock);
			WSACleanup();
			return -1;
		}
		printf("Data sent successfully.....\n");
	}

	//close the socket.
	closesocket(sock);
	WSACleanup();
	return 0;
}