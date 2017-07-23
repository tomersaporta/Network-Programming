/*
 * UDPMessenger.h
 *
 *  Created on: Apr 5, 2017
 *      Author: user
 */

#ifndef UDPMESSENGER_H_
#define UDPMESSENGER_H_

#include <string>
#include <iostream>
#include "UDPSocket.h"
#include <string.h>
#include "MThread.h"


using namespace std;

namespace networkingLab {

class UDPMessenger : public MThread{
public:
	static const  int MSG_PORT = 3457;
	UDPSocket * udp_socket;
	bool isRun;

	UDPMessenger();
	virtual ~UDPMessenger();

	void sendTo(string msg,string ip,int port);
	void reply(string msg);
	void close();
	void run();
};

} /* namespace networkingLab */

#endif /* UDPMESSENGER_H_ */
