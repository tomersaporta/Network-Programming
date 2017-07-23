/*
 * TCPMSNClientTest.cpp
 *
 *  Created on: Jun 11, 2017
 *      Author: user
 */

#include "TCPMSNClientTest.h"
using namespace std;
namespace networkingLab {

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                                            ///////////////////////////
///////////////////////////   ClientHandlerTest       implementation    ///////////////////////////
///////////////////////////                                            ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void ClientHandlerTest::onMessageRecived(string message) {
	this->messages = message;
	cout << "Recived message: " << message << endl;
}

void ClientHandlerTest::onOpenSession(string ipPort) {
	cout << "Open session with ip port: " << ipPort << endl;
}

void ClientHandlerTest::onClosedSession() {
	cout << "Close session" << endl;
}

TCPMSNClientTest::TCPMSNClientTest() {
}

TCPMSNClientTest::~TCPMSNClientTest() {
}

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////                                            ///////////////////////////
///////////////////////////   TCPMSNClientTest       implementation    ///////////////////////////
///////////////////////////                                            ///////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

bool networkingLab::TCPMSNClientTest::test() {
	int rec;

	//create client 1

	ClientHandlerTest handler1;

	TCPMSNClient client1(&handler1);

	//connect client 1 to server

	rec = client1.connect("127.0.0.1");
	if (rec < 0) {
		perror("ERROR connect client 1");
		return false;
	}
	sleep(2);
	//create client 2
	ClientHandlerTest handler2;

	TCPMSNClient client2(&handler2);

	//connect client 2 to server
	rec = client2.connect("127.0.0.1");
	if (rec < 0) {
		perror("ERROR connect client 2");
		return false;
	}
	sleep(2);
	//open session from client 1 to client 2
	int port = client2.getPort();
	client1.openSession("127.0.0.1", port);
	sleep(2);

	//send message from client 1 to client 2
	string msg = "Tomer Test";
	client1.sendMessage(msg);
	sleep(2);

	//compare messages
	if (strcmp(msg.data(), handler2.messages.data()) != 0) {
		perror("ERROR send messages from client 1 to client 2");
		return false;
	}

	//send message from client 2 to client 1
	msg = "Saporta Test";
	client2.sendMessage(msg);
	sleep(2);
	//compare messages
	if (strcmp(msg.data(), handler1.messages.data()) != 0) {
		perror("ERROR send messages from client 1 to client 2");
		return false;
	}
	//close session
	client1.closeSession();
	client2.closeSession();

	//close client 1, 2
	sleep(2);
	client1.disconnect();
	client2.disconnect();

	sleep(2);
	client1.exit();
	client2.exit();
	return true;
}

} /* namespace networkingLab */

