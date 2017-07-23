/*
 * TCPMSNClientTest.h
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#ifndef TCPMSNCLIENTTEST_H_
#define TCPMSNCLIENTTEST_H_

#include "TCPMSNClient.h"
#include <iostream>

using namespace std;


namespace networkingLab {

class ClientHandlerTest:public TCPMSNClientHandler{

public:
	string messages;

	virtual void onMessageRecived(string message);
	virtual void onOpenSession(string ipPort);
	virtual void onClosedSession();
	virtual ~ClientHandlerTest(){}
};


class TCPMSNClientTest {
public:
	TCPMSNClientTest();
	virtual ~TCPMSNClientTest();
	bool test();
};

} /* namespace networkingLab */

#endif /* TCPMSNCLIENTTEST_H_ */
