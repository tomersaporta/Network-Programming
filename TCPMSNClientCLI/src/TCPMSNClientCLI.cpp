//============================================================================
// Name        : TCPMSNClientCLI.cpp
// Author      : Tomer Saporta
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TCPMSNClient.h"
#include "ClientHandlerCLI.h"
using namespace std;
using namespace networkingLab;

void printInstructions(){
		cout<<"To open connect to server type: c <server ip>"<<endl;
		cout<<"To open session type with peer: o <peer ip> <peer port>"<<endl;
		cout<<"Opening session will close any previously active sessions"<<endl;
		cout<<"After the session is opened, to send message type: s <message>"<<endl;
		cout<<"To close opened session type: cs"<<endl;
		cout<<"To disconnect from server type: d"<<endl;
		cout<<"To exit type: x"<<endl;
	}


int main() {
	cout << "Welcome to TCP messenger" << endl;
	printInstructions();
	ClientHandlerCLI handler;
	TCPMSNClient* client = new TCPMSNClient(&handler);
	while (true) {
		string msg;
		string command;
		cin >> command;
		if (command == "c") {
			string ip;
			cin >> ip;
			client->connect(ip);
		} else if (command == "o") {
			string ip;
			int port;
			cin >> ip;
			cin >> port;
			client->openSession(ip, port);
		} else if (command == "s") {
			getline(std::cin, msg);
			if (msg.size() > 0 && msg[0] == ' ')
				msg.erase(0, 1);
			// TODO- check if the session active

			client->sendMessage(msg);
		} else if (command == "cs") {
			client->closeSession();
		} else if (command == "d") {
			client->disconnect();
		} else if (command == "x") {
			break;
		} else {
			cout << "wrong input" << endl;
			printInstructions();
		}
	}
	client->disconnect();
	delete client;
	cout << "messenger was closed" << endl;
	return 0;
}
