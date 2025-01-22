#include <stdio.h>
#include <winsock2.h>


/*
  From page https://www.tenouk.com/Winsock/Winsock2example2.html

	This Client example will:
	  * Open a socket (to a server),
	  * Read Data from Server
	  * Send reply to the server


  * Add in C / C++ > Preprocessor > Preprocessor Definitions value  _WINSOCK_DEPRECATED_NO_WARNINGS
	-- > Project Settings >
	*Add in Linker > Input > Additionnal Dependencies the value ws2_32.lib


*/


int main()
{
	// Initialize Winsock.
	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
	else
		printf("Client: WSAStartup() initialised...\n");


	// Create a socket.
	SOCKET m_socket;
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_socket == INVALID_SOCKET)
	{
		printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());

		WSACleanup();
		return 0;
	}
	else
		printf("Client: socket created...\n");

	// Connect to a server.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);

	if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		printf("Client: Failed to connect to server on %s port %d.\n", "127.0.0.1", 55555);

		WSACleanup();
		return 0;
	}
	else
		printf("Client: Connect established on server at %s , port %d.\n", "127.0.0.1", 55555);


	// Send and receive data.
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;

	// Be careful with the array bound, provide some checking mechanism
	char sendbuf[200] = "Client: Sending some test string to server...";
	char recvbuf[200] = "";
 
	// First, listen to the server, and reading a string from it ... 
	while (bytesRecv == SOCKET_ERROR)
	{
		bytesRecv = recv(m_socket, recvbuf, 200, 0);
		if (bytesRecv == 0 || bytesRecv == WSAECONNRESET)
		{
			printf("Client: Connection Closed.\n");

			break;
		}

		if (bytesRecv < 0)
			return 0;
		else
		{
			printf("Client: Received data from server: \"%s\"\n", recvbuf);
			printf("Client: Bytes received is: %ld.\n", bytesRecv);
		}
	}


	// Will reply to the server by sending a string...

	bytesSent = send(m_socket, sendbuf, strlen(sendbuf), 0);
	if (bytesSent == SOCKET_ERROR)
		printf("Client: reply to server error %ld.\n", WSAGetLastError());
	else
	{
		printf("Client: reply to server --> Bytes sent: %ld\n", bytesSent);
		printf("Client: The test string sent: \"%s\"\n", sendbuf);
	}



	WSACleanup();

	return 0;
}