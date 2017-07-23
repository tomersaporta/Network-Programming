/*
 * TCPP2PClient.cpp
 *
 *  Created on: May 11, 2017
 *      Author: user
 */

#include "TCPP2PClient.h"

namespace networkingLab {

TCPP2PClient::TCPP2PClient() {
	this->clientSocket=NULL;
	this->finish=false;

}

TCPP2PClient::~TCPP2PClient() {
	if (this->clientSocket!=NULL)
		delete this->clientSocket;
}



bool TCPP2PClient::open(string ip, int port) {
	this->clientSocket= new TCPSocket(ip,port);

   if(this->clientSocket!=NULL)
   {
	   this->start();
	   return true;
   }

   else return false;
}

void TCPP2PClient::send(const char* msg) {
	int ret=this->clientSocket->write(msg,strlen(msg));
	if (ret<0){
		cout<<"Error sending message from client"<<endl;
	}

}

void TCPP2PClient::close() {
	this->finish=true;
	this->clientSocket->close();
}

void TCPP2PClient::run(){
	char buffer[1024];
	while(!finish){
		int len=this->clientSocket->read(buffer, sizeof(buffer));
			buffer[len]='\0';
			cout<<"massage from server: "<<buffer<<endl;
	}
}

bool TCPP2PClient::isActivePeerSession(){
	if(this->clientSocket!=NULL)
		return true;
	return false;
}
} /* namespace networkingLab */
