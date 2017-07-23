/*
 * Dispatcher.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_
#include "TCPSocket.h"
#include "DispatcherHandler.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMSNProtocol.h"
#include "MThread.h"
#include <vector>



namespace networkingLab {
class Dispatcher :public MThread{
private:
	DispatcherHandler* handler;
	MultipleTCPSocketsListener *tcpListener;
	TCPSocket * newPeerToAdd;
	TCPSocket* fakeSocket;
	bool stop, init;

	void handlePeer(TCPSocket * peer);
public:

	Dispatcher(DispatcherHandler* handler);
	~Dispatcher();
	void addPeer(TCPSocket* peer);
	void startDispatcher();


	void interruptFakeSocket();
	void initFakeSocket();

	string getPeersList();
	void close();
	void run();

};

} /* namespace networkingLab */

#endif /* SRC_DISPATCHER_H_ */
