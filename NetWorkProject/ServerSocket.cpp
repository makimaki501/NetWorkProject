#include "ServerSocket.h"
#include "SocketImpl.h"



ServerSocket::ServerSocket()
	:mImpl(new SocketImpl())
{
}

ServerSocket::ServerSocket(int port, int backlog)
	: mImpl(new SocketImpl())
{
	bind(port, backlog);
}

ServerSocket::~ServerSocket()
{
}

std::auto_ptr<Socket> ServerSocket::accept()
{
	return std::auto_ptr<Socket>(new Socket(mImpl->accept()));
}

void ServerSocket::bind(int port, int backlog)
{
	mImpl->bind(port);

	mImpl->listen(backlog);
}

void ServerSocket::close()
{
	if (mImpl->isConnected() == true) {
		mImpl->close();
	}
}

InetAddress ServerSocket::getAddress() const
{
	return mImpl->getLocalInetSocketAddress().getInetAddress();
}

int ServerSocket::getPort() const
{
	return mImpl->getLocalInetSocketAddress().getPort();
}
