/*
 * TCPMSNServer.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_TCPMSNSERVER_H_
#define SRC_TCPMSNSERVER_H_
#include "Server.h"
#include "Dispatcher.h"
#include "BrokerMng.h"
#include "BrokerMngHandler.h"
#include "DispatcherHandler.h"
#include "ServerHandler.h"
#include "TCPMSNProtocol.h"
#include "MThread.h"

namespace networkingLab {

class TCPMSNServer: public ServerHandler,DispatcherHandler,BrokerMngHandler, MThread {
private:
	Server* server;
	Dispatcher* dispatcher;
	BrokerMng* brokerMng;


public:
	TCPMSNServer();
	virtual void handleConnectedPeer(TCPSocket* peer);
	virtual void managePeerSession(TCPSocket* peer1, TCPSocket* peer2);
	virtual void handleReturnedPeer(TCPSocket* peer);
	void startServer();
	void close();
	virtual ~TCPMSNServer();
	void run();
	string getPeerList();

};

} /* namespace npl */

#endif /* SRC_TCPMSNSERVER_H_ */
