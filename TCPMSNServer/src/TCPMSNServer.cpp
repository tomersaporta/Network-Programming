/*
 * TCPMSNServer.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "TCPMSNServer.h"


namespace networkingLab {

TCPMSNServer::TCPMSNServer(){
	this->server = new Server(MSNGR_PORT,this);
	this->dispatcher = new Dispatcher(this);
	this->brokerMng = new BrokerMng(this);

}

void TCPMSNServer::handleConnectedPeer(TCPSocket* peer){
	this->dispatcher->addPeer(peer);
}
void TCPMSNServer::managePeerSession(TCPSocket* peer1, TCPSocket* peer2){
	this->brokerMng->createBroker(peer1,peer2);
}
void TCPMSNServer::handleReturnedPeer(TCPSocket* peer){
	this->dispatcher->addPeer(peer);
}

void TCPMSNServer::startServer() {
	this->start();
}

void TCPMSNServer::close() {
	this->server->close();
	this->dispatcher->close();

}

TCPMSNServer::~TCPMSNServer() {
	if(this->server!=NULL){
		delete this->server;
		this->server=NULL;
	}
	if(this->dispatcher!=NULL){
		delete this->dispatcher;
		this->dispatcher=NULL;
	}
	if(this->brokerMng!=NULL){
		delete this->brokerMng;
		this->brokerMng=NULL;
	}
}
void TCPMSNServer::run() {
	this->server->startServer();
		sleep(2);
		this->dispatcher->startDispatcher();
		this->server->waitForThread();
		this->dispatcher->waitForThread();
}
string TCPMSNServer::getPeerList() {
	return this->dispatcher->getPeersList();
}


} /* namespace npl */


