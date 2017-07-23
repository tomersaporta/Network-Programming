/*
 * TCPP2PServer.h
 *
 *  Created on: May 11, 2017
 *      Author: user
 */


#ifndef TCPP2PSERVER_H_
#define TCPP2PSERVER_H_


#include "TCPSocket.h"
#include "MThread.h"

#include <iostream>

using namespace std;
namespace networkingLab {

class TCPP2PServer : public MThread{

public:

	 TCPSocket* serverSocket;
	 TCPSocket* aClient;
	 bool finish;

	TCPP2PServer();
	virtual ~TCPP2PServer();
	void init(size_t port);
	void reply(const char* msg);
	void run();
	void close();
	bool isActiveClientSession();


};
} /* namespace networkingLab */
#endif /* TCPP2PSERVER_H_ */
