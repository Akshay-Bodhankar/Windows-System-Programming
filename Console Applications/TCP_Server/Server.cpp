/*

	Demonstrate TCP CLIENT-SERVER applictaion using winsock liberary

	@Author - Akshay Bodhankar
			  akshaybodhankar2197@gmail.com

	@Title - Windows_System_Programing [ SERVER-APPLICATION ]


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
	SOCKET sock, sess;
	SOCKADDR_IN saddr,caddr;
	int c_size = sizeof(caddr);
	int ret;
	char buff[MAXBUFF] = { '\0' };

	//entry for Socket.
	WSAStartup(MAKEWORD(2, 2), & data);
	printf("\t\t\tTCP SERVER\n");

	//creating socket for connection.
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		printf("socket failed: %d.\n", GetLastError());
		return -1;
	}

	//getting sock_addr structure
	saddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	saddr.sin_port = htons(8080);
	saddr.sin_family = AF_INET;

	//The bind function binds the specific port number and ip to the socket.
	ret = bind(sock, (sockaddr*)&saddr, sizeof(saddr));
	if (ret < 0)
	{
		printf("Bind failed: %d.\n", GetLastError());
		closesocket(sock);
		return -1;
	}

	//making socket in listening mode for incoming connection.
	ret = listen(sock, 0);
	if (ret < 0)
	{
		printf("listen failed: %d.\n", GetLastError());
		closesocket(sock);
		return -1;
	}

	//run the server
	printf("Server is running...\n");
	printf("Listening for request.....\n");
	while (1)
	{
		//The accept function serves to the incoming connection on server.
		sess = accept(sock, (sockaddr*)&caddr, &c_size);
		if (sess < 0)
		{
			printf("Accept failed: %d.\n", GetLastError());
			closesocket(sock);
			return -1;
		}

		printf("Connection establish.....\n");

		memset(buff, '\0', MAXBUFF);
		//The recv function recives the data from connected connection or client.
		ret = recv(sess, buff, sizeof(buff), 0);
		if (ret < 0)
		{
			printf("recv failed: %d.\n", GetLastError());
			closesocket(sess);
			closesocket(sock);
			return -1;
		}

		printf("Data recived.....!!!!\n");

		//message from client.
		printf("Data from client: [%s] \n", buff);

		//The send function sends the data to the connected client or connection.
		ret = send(sess, buff, strlen(buff), 0);
		if (ret < 0)
		{
			printf("Send failed: %d.\n", GetLastError());
			closesocket(sess);
			closesocket(sock);
			return -1;
		}
		printf("Data sent sucesfully...!!!\n");
		printf("Data sent to client: [%s]\n", buff);
		//closing the connection with particular connection or client.
		closesocket(sess);
	}

	//closing socket.
	closesocket(sock);
	WSACleanup();
	return 0;
}