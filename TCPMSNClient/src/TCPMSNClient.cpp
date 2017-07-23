/*
 * TCPMSNClient.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "TCPMSNClient.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

namespace networkingLab {

TCPMSNClient::TCPMSNClient(TCPMSNClientHandler * handler) {
	this->handler = handler;
	client = NULL;
	this->isConnected = true;

}

TCPMSNClient::~TCPMSNClient() {
//	if (client != NULL)
//		client->close();
	//if (handler!=NULL)
	//delete[]handler;
}

bool TCPMSNClient::connect(string ip) {
	client = new TCPSocket(ip, (size_t) MSNGR_PORT);
	if (this->client->socket_fd < 0)
		return false;
	this->start();
	return true;
}

bool TCPMSNClient::openSession(string ip, int port) {
	char buff[100];
	sprintf(buff, "%s:%d", ip.c_str(), port);
	//cout << "data to send:" << buff << endl;
	int rec = sendCommand(OPEN_SESSION_WITH_PEER, buff);
	if (rec < 0)
		perror("ERROR send OPEN_SESSION_WITH_PEER to server");
	return rec > -1;

}

void TCPMSNClient::sendMessage(string msg) {
	//cout << "data to send:" << msg << endl;
	int rec = sendCommand(SEND_MSG_TO_PEER, msg.data());
	if (rec < 0)
		perror("ERROR send SEND_MSG_TO_PEER  to server");

}

void TCPMSNClient::closeSession() {
	int rec = sendCommand(CLOSE_SESSION_WITH_PEER, NULL);
	if (rec < 0)
		perror("ERROR send CLOSE_SESSION_WITH_PEER  to server");
}

void TCPMSNClient::disconnect() {
	if(this->isConnected){
	int rec = sendCommand(EXIT, NULL);
		if (rec < 0){
			perror("ERROR send EXIT to server");
		}
	this->isConnected=false;
	}
}

void TCPMSNClient::exit() {
	this->client->close();
	delete this->client;
}

int TCPMSNClient::getPort() {
	struct sockaddr_in s_in;
	socklen_t len = sizeof(s_in);
	//return client->getRemotePort()();
	getsockname(client->socket_fd, (struct sockaddr *) &s_in, &len);
	return ntohs(s_in.sin_port);

}
void TCPMSNClient::run() {
	while (this->isConnected){
		this->recvCommand();
	}
}

int TCPMSNClient::sendCommand(int cmd, const char* buff) {
	int cmdNet = htonl(cmd);
	int res = client->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = client->write((char*) &lenNet, 4);
		if (res < 4) {
			return -1;
		}
		res = client->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;

}
void TCPMSNClient::recvCommand() {

	char * buff;
	int cmdNet, cmd, len;
	int rec;
	bool success = true;
	rec = client->read((char*) &cmdNet, 4);
	if (rec <=0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {

		case CLOSE_SESSION_WITH_PEER: {
			//cout << "From server: " << "CLOSE_SESSION_WITH_PEER" << endl;
			if (this->handler != NULL)
				this->handler->onClosedSession();
			break;
		}
		case OPEN_SESSION_WITH_PEER: {
			//cout << "From server: " << "OPEN_SESSION_WITH_PEER" << endl;
			this->client->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			this->client->read(buff, len);
			this->handler->onOpenSession(buff);
			break;
		}
		case EXIT: {
			cout << "From server: " << "EXIT" << endl;
			break;
		}
		case SEND_MSG_TO_PEER: {
			//cout << "From server: " << "SEND_MSG_TO_PEER" << endl;
			this->client->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			this->client->read(buff, len);
			this->handler->onMessageRecived(buff);
			break;
		}
		case SESSION_REFUSED: {
			cout << "From server: " << "SESSION_REFUSED" << endl;
			break;
		}
		case SESSION_ESTABLISHED: {
			cout << "From server: " << "SESSION_ESTABLISHED" << endl;
			break;
		}
		default: {
			break;
		}

		}
	}

}

} /* namespace networkingLab */

