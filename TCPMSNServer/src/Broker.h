/*
 * Broker.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_BROKER_H_
#define SRC_BROKER_H_
#include "TCPSocket.h"
#include "MThread.h"
#include "BrokerMng.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMSNProtocol.h"


namespace networkingLab {

class BrokerMng;

class Broker: public MThread {
private:
	BrokerMng* parent;
	TCPSocket *peer1;
	TCPSocket *peer2;
	MultipleTCPSocketsListener * tcpListen;
	bool stop;
	int sendCommand(TCPSocket* destPeer,int cmd, const char* buff);
	void openSessionCommand();

public:
	Broker(TCPSocket* peer1, TCPSocket* peer2, BrokerMng* parent);
	void run();
	void handlePeer(TCPSocket* peer);
	virtual ~Broker();

};

} /* namespace networkingLab */

#endif /* SRC_BROKER_H_ */
