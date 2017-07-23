/*
 * Broker.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#include "Broker.h"

namespace networkingLab {

Broker::Broker(TCPSocket* peer1, TCPSocket* peer2, BrokerMng* parent) {
	this->parent = parent;
	this->peer1 = peer1;
	this->peer2 = peer2;
	this->tcpListen = new MultipleTCPSocketsListener();
	this->stop = false;

	this->tcpListen->addSocket(peer1);
	sleep(2);
	this->tcpListen->addSocket(peer2);

	openSessionCommand();
	this->start();
}
void Broker::run() {
	TCPSocket* aPeer;
	while (!stop) {
		aPeer = this->tcpListen->listenToSocket();
		this->handlePeer(aPeer);
	}
}

Broker::~Broker() {
	// TODO Auto-generated destructor stub
}

void Broker::handlePeer(TCPSocket* peer) {
	char * buff;
	int cmdNet, cmd, len;
	int rec;
	string ip, strPort;
	bool success = true;

	//set the destination peer
	TCPSocket* destPeer;
	if (peer->socket_fd == this->peer1->socket_fd)
		destPeer = this->peer2;
	else
		destPeer = this->peer1;
	rec = peer->read((char*) &cmdNet, 4);

	if (rec <= 0)
		success = false;
	cmd = ntohl(cmdNet);

	if (success) {
		switch (cmd) {
		case SEND_MSG_TO_PEER: {
			//cout<< "SEND_MSG_TO_PEER" << endl;

			peer->read((char *) &len, sizeof(len));
			len = ntohl(len);
			buff = new char[len];
			peer->read(buff, len);
			int rec= sendCommand(destPeer, cmd, buff);
			if(rec<len){
				cout<<"Error sending message"<<endl;
				break;
			}
			cout << "sending msg:" << peer->getRemotedSocketIP() << ":"
								<< peer->getRemotedSocketPort() << "->"
								<< destPeer->getRemotedSocketIP() << ":"
								<< destPeer->getRemotedSocketPort() << endl;
			break;
		}

		case CLOSE_SESSION_WITH_PEER: {
			int rec = sendCommand(this->peer1, CLOSE_SESSION_WITH_PEER, NULL);
			if (rec < len) {
				cout << "Error sending CLOSE_SESSION_WITH_PEER1" << endl;
			}
			rec = sendCommand(this->peer2, CLOSE_SESSION_WITH_PEER, NULL);
			if (rec < len) {
				cout << "Error sending CLOSE_SESSION_WITH_PEER1" << endl;
			}

			this->parent->rleasePeer(peer1);
			sleep(3);
			this->parent->rleasePeer(peer2);

			cout<<"closing session: "<<peer1->getRemotedSocketIP()<<":"<<peer1->getRemotedSocketPort()<<"->"<<peer2->getRemotedSocketIP()<<":"<<peer2->getRemotedSocketPort()<<endl;
			cout<<"broker deleted"<<endl;

			//delete the current Broker
			delete this;
			break;
		}
		case EXIT: {
			int rec = sendCommand(destPeer, CLOSE_SESSION_WITH_PEER, NULL);
			if (rec < len)
				cerr << "Error sending message" << endl;
			this->parent->rleasePeer(destPeer);
			peer->close();
			//delete the current Broker
			delete this;
			break;
		}
			default:
			break;
		}

	}
}


int Broker::sendCommand(TCPSocket* destPeer, int cmd, const char* buff) {

	int cmdNet = htonl(cmd);
	int res = destPeer->write((char*) &cmdNet, 4);
	if (res < 4) {
		return -1;
	}
	if (buff != NULL) {
		int len = strlen(buff);
		int lenNet = htonl(len);
		res = destPeer->write((char*) &lenNet, 4);
		if (res < 4) {
			return -1;
		}
		res = destPeer->write(buff, len);
		if (res < len) {
			return -1;
		}
	}
	return res;

}

void Broker::openSessionCommand() {
	string msg = peer1->getRemotedSocketIP();
	char buffer [sizeof(peer1->getRemotedSocketPort())+1];
	msg+=":";
	sprintf(buffer, "%d",this->peer1->getRemotedSocketPort());
	msg+=buffer;
	sendCommand(this->peer2, OPEN_SESSION_WITH_PEER, msg.c_str());

	string msg2 = peer2->getRemotedSocketIP();
	char buff [sizeof(peer2->getRemotedSocketPort())+1];
	msg2+=":";
	sprintf(buff, "%d",this->peer2->getRemotedSocketPort());
	msg2+=buff;

	sendCommand(this->peer1, OPEN_SESSION_WITH_PEER, msg.c_str());
	cout<<"create new broker between: "<<msg<<" and "<<msg2<<endl;
}

} /* namespace networkingLab */


