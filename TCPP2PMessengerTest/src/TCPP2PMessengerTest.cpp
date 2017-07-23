//============================================================================
// Name        : TCPP2PMessengerTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "TCPP2PMessenger.h"
#include <iostream>
using namespace std;
using namespace networkingLab;


int main() {

	//Create  MSN server side
	TCPP2PMessenger *server=new TCPP2PMessenger();

	TCPP2PMessenger *client = new TCPP2PMessenger();
	server->init(7771);
	sleep(2);
	//Create MSN client side

	//open connection from client to server
	client->open("127.0.0.1", 7771);

	//send message from client to server
	//char clienMsg[100]= "Tomer TCP MSG  client Test";
	//char serverMsg[100] = "Tomer TCP MSG server Test";
	client->send("Tomer TCP MSG  client send Test");
	//reply message from server to client
	server->reply("Tomer TCP MSG  server send Test");
	//close
	sleep(2);
	client->close();
	server->close();
	delete client;
	delete server;
	//compare send and received  messages - will be implemented later..

	return 0;
}
