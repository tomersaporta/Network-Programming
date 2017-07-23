/*
 * TCPP2PClient.h
 *
 *  Created on: May 11, 2017
 *      Author: user
 */

#ifndef SRC_TCPP2PCLIENT_H_
#define SRC_TCPP2PCLIENT_H_

#include "TCPSocket.h"
#include <iostream>
#include "MThread.h"

using namespace std;
namespace networkingLab {

class TCPP2PClient : public MThread{

private:
	TCPSocket* clientSocket;
	bool finish;
public:

	TCPP2PClient();
	virtual ~TCPP2PClient();


	bool open(string ip,int port);
	void send(const char* msg);
	void close();
	void run();
	bool isActivePeerSession();
};

} /* namespace networkingLab */

#endif /* SRC_TCPP2PCLIENT_H_ */
