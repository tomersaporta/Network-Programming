/*
 * Dispatcher.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "Dispatcher.h"

namespace networkingLab {

Dispatcher::Dispatcher(DispatcherHandler* handler) {
	this->handler = handler;
	this->stop = false;
	this->newPeerToAdd = NULL;
	this->tcpListener = new MultipleTCPSocketsListener();
	this->fakeSocket=NULL;//new TCPSocket("127.0.0.1",MSNGR_PORT);//////
	this->init = true;
}

void Dispatcher::startDispatcher() {
	cout<<"dispatcher started"<<endl;
	//init the demo peer
	this->initFakeSocket();

}

Dispatcher::~Dispatcher() {
	if(this->handler!=NULL){
		delete this->handler;
		this->handler = NULL;
	}
	if(this->tcpListener!=NULL){
		delete this->tcpListener;
		this->tcpListener=NULL;
	}
}

void Dispatcher::addPeer(TCPSocket* peer) {
	if(this->init){
		//add the new socket

		this->tcpListener->addSocket(peer);
		this->init = false;
		this->start();
	}
	else{
		this->newPeerToAdd = peer;
		//Interrupt the fake socket
		this->interruptFakeSocket();
	}
}
void Dispatcher::close() {
	this->stop= true;
}

void Dispatcher::handlePeer(TCPSocket* peer) {

	char * buff;
	int cmdNet, cmd, len, port;
	int rec;
	string ip, strPort;

	bool success = true;
	rec = peer->read((char*) &cmdNet, 4);
	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {
		case OPEN_SESSION_WITH_PEER: {
			//cout << "From server: " << "OPEN_SESSION_WITH_PEER" << endl;

			peer->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			peer->read(buff, len);
			//get the ip and port from client command
			int i;
			bool readPort = false;
			for (i = 0; i < len; i++) {
				if (buff[i] == ':')
					readPort = true;
				else if (!readPort)
					ip += buff[i];
				else
					strPort += buff[i];
			}
			sscanf(strPort.c_str(),"%d", &port);
			//search the other peer
			TCPSocket * destPeer = this->tcpListener->searchSocket(port, ip);
			if (destPeer != NULL) {
				this->handler->managePeerSession(peer, destPeer);
				this->tcpListener->removeSocket(peer);
				this->tcpListener->removeSocket(destPeer);
				cout<<"got open session command: "<<peer->getRemotedSocketIP()<<":"<<peer->getRemotedSocketPort()<<"->"<<destPeer->getRemotedSocketIP()<<":"<<destPeer->getRemotedSocketPort()<<endl;
			} else {
				cout << "peer : " << ip << ":" << strPort << " not found"<<endl;
				int cmdNet = htonl(SESSION_REFUSED);
				peer->write((char*) &cmdNet, 4);
			}


			break;
		}
		case INTERRUPT_SOCKET:{
			//cout<<"INTERRUPT_SOCKET"<<endl;
				this->tcpListener->addSocket(this->newPeerToAdd);
				cout<<"new peer connected: "<<newPeerToAdd->getRemotedSocketIP()<<":"<<newPeerToAdd->getRemotedSocketPort()<<endl;

			break;
		}
		case EXIT: {
			this->tcpListener->removeSocket(peer);
			peer->close();
			break;
		}
		default: {
			break;
		}

		}
	}

}

void Dispatcher::interruptFakeSocket() {
	int cmd = htonl(INTERRUPT_SOCKET);
	int rec= this->fakeSocket->write((char*)&cmd,4);
	if (rec <4)
		perror("ERROR INTERRUPT_SOCKET Failed");

}

void Dispatcher::initFakeSocket() {
	this->fakeSocket= new TCPSocket("127.0.0.1",MSNGR_PORT);

}

void Dispatcher::run() {
	TCPSocket * aPeer;
	while(!stop){
	//Blocking call
	aPeer= this->tcpListener->listenToSocket();
	this->handlePeer(aPeer);
	}
}
string Dispatcher::getPeersList() {
	string s = this->tcpListener->getPeerList();
	return s;
}

} /* namespace networkingLab */


