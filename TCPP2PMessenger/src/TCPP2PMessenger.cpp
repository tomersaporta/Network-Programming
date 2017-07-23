/*
 * TCPP2PMessenger.cpp
 *
 *  Created on: May 11, 2017
 *      Author: user
 */


#include "TCPP2PMessenger.h"

using namespace std;
namespace networkingLab {
TCPP2PMessenger::TCPP2PMessenger() {

	this->client=new TCPP2PClient();
	this->server= new TCPP2PServer();

}

void TCPP2PMessenger::init(size_t port) {
	this->server->init(port);

}

bool TCPP2PMessenger::open(string ip, size_t port) {
	return this->client->open(ip, port);
}

void TCPP2PMessenger::send(const char* msg) {
	 this->client->send(msg);
}

void TCPP2PMessenger::reply(const char* msg) {
	this->server->reply(msg);
}

void TCPP2PMessenger::close() {
	this->client->close();
	this->server->close();
}

bool TCPP2PMessenger::isActiveClientSession() {
	return this->server->isActiveClientSession();
}

bool TCPP2PMessenger::isActivePeerSession() {
return this->client->isActivePeerSession();
}

TCPP2PMessenger::~TCPP2PMessenger() {
	if(this->client!=NULL)
			delete this->client;
	if(this->server!=NULL)
			delete this->server;

}
}/* namespace networkingLab */
