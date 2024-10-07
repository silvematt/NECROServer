#ifndef TCP_SOCKET_H
#define TCP_SOCEKT_h

#ifdef _WIN32
#include "WinSock2.h"
typedef SOCKET sock_t;
#else
typedef int sock_t;
#endif

#include "SocketAddress.h"
#include <memory>

const int TCP_LISTEN_DEFUALT_BACKLOG = 128;

enum SocketAddressesFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

//-------------------------------------------------------
// Defines a TCP Socket object.
//-------------------------------------------------------
class TCPSocket
{
private:
	friend class SocketAddress;
	sock_t m_socket;

public:
	TCPSocket(SocketAddressesFamily family);
	TCPSocket(sock_t inSocket);

	~TCPSocket();
	
	int							Bind(const SocketAddress& addr);
	int							Listen(int backlog = TCP_LISTEN_DEFUALT_BACKLOG);
	std::shared_ptr<TCPSocket>	Accept(SocketAddress& addr);
	int							Connect(const SocketAddress& addr);
	int							Send(const void* inData, int inLen);
	int							Receive(void* inBuffer, int inLen);

	int							SetBlockingEnabled(bool blocking);
	int							SetSocketOption(int lvl, int optName, const char* optVal, int optLen);
};

#endif
