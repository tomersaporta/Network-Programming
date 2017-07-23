/*
 * TCPP2PServer.cpp
 *
 *  Created on: May 11, 2017
 *      Author: user
 */

#include "TCPP2PServer.h"

namespace networkingLab {

TCPP2PServer::TCPP2PServer() {
	this->serverSocket=NULL;
	this->aClient=NULL;
	this->finish=false;

}

TCPP2PServer::~TCPP2PServer() {
	if(this->serverSocket!=NULL)
		delete this->serverSocket;
	if(this->aClient!=NULL)
		delete this->aClient;
}

void TCPP2PServer::init(size_t port) {
	this->serverSocket=new TCPSocket(port);
	this->start();
}

void TCPP2PServer::reply(const char* msg) {
	int ret=this->aClient->write(msg, strlen(msg));
	if (ret<0)
		cout<<"Error sending message from server"<<endl;

}

void TCPP2PServer::close() {
	this->finish=true;
	this->serverSocket->close();
	this->aClient->close();
}

void TCPP2PServer::run(){
	this->aClient=this->serverSocket->listenAndAccept();
	char buffer[1024];

	while(!this->finish){
		int len=this->aClient->read(buffer,sizeof(buffer));
		if (len<=0){
			this->finish=true;
			break;
		}
		buffer[len]='\0';
		cout<<"massage from client "<<aClient->fromAddr()<<" : "<<buffer<<endl;
	}


}

bool TCPP2PServer::isActiveClientSession() {
	if (this->aClient!=NULL)
			return true;
		return false;
}
} /* namespace networkingLab */
