#include <string>
#include <stdexcept>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tcpp.h"

ServerSocket::ServerSocket(short port) {
	sockaddr_in server;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Could not create socket");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&server , sizeof(server)) < 0) {
		close(sockfd);
		throw std::runtime_error("Binding failed");
	}

	if (listen(sockfd, default_sock_backlog) < 0) {
		close(sockfd);
		throw std::runtime_error("Listening on port failed");
	}
}

RWSocket ServerSocket::accept() {
	int clientfd, len;
	sockaddr_in client;

	if ((clientfd = ::accept(sockfd, (sockaddr *)&client, (socklen_t*)&len)) < 1)
		throw std::runtime_error("Could not accept client");

	return RWSocket(clientfd, client);
}

RWSocket::RWSocket(const char *ip, short port)
{
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Could not create socket");

	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr = inet_addr(ip);
	peer.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *)&peer, sizeof(peer)) < 0)
		throw std::runtime_error("Could not connect to server");
}