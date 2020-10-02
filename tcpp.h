#ifndef _TCPP_H_
#define _TCPP_H_

#include <sstream>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

class RWSocket;

class ServerSocket
{
public:
	ServerSocket(short port);
	~ServerSocket()
	{
		if (sockfd >= 0)
			close(sockfd);
	};

	// move
	ServerSocket(ServerSocket &&other)
	{
		*this = std::move(other);
	}
	ServerSocket &operator=(ServerSocket &&other)
	{
		this->sockfd = other.sockfd;
		other.sockfd = -1;
		return *this;
	}

	// copy
	ServerSocket(ServerSocket const &) = delete;
	ServerSocket &operator=(ServerSocket const &) = delete;

	RWSocket accept();

private:
	int sockfd;
};

class RWSocket
{
	friend RWSocket ServerSocket::accept();

public:
	RWSocket(const char *ip, short port);
	~RWSocket()
	{
		if (sockfd >= 0)
			close(sockfd);
	}
	
	// move
	RWSocket(RWSocket &&other)
	{
		*this = std::move(other);
	}
	RWSocket& operator=(RWSocket &&other)
	{
		this->sockfd = other.sockfd;
		other.sockfd = -1;
		return *this;
	}

	// copy
	RWSocket(const RWSocket &other) = delete;
	RWSocket& operator=(const RWSocket &other) = delete;

	template<class T>
	RWSocket& operator>>(T& obj) {
		char buf[256];
		int bytes;

		while ((sstr >> obj).eof() && sstr.bad()) {
			bytes = recv(sockfd, buf, sizeof(buf), 0);
			if (bytes < 0) {
				throw std::runtime_error("Error reading from socket");
			} else if (bytes == 0) {
				if (sstr.eof()) {
					throw std::runtime_error("socket EOF");
				} else {
					// if socket reaches EOF, but sstr  has data, the requested format
					// was incompatible with the data in sstr
					throw std::runtime_error("Invalid input format");
				}
			} else {
				sstr.write(buf, bytes);
			}
		}

		if (sstr.bad()) {
			throw std::runtime_error("Invalid input format");
		} else {
			// successful read
			return *this;
		}
	}

private:
	RWSocket(int fd, sockaddr_in client): sockfd(fd), peer(client) {}
	int sockfd;
	sockaddr_in peer;
	std::stringstream sstr;
};

constexpr int default_sock_backlog = 4;

#endif
