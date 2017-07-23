//============================================================================
// Name        : TCPP2PMessengerCLI.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "TCPP2PMessenger.h"
#include <iostream>
using namespace std;
using namespace networkingLab;

void printInstructions(){
	cout<<"To creat server message type: cs <port>"<<endl;
	cout<<"To creat a client message type: cc  <ip> <port> "<<endl;
	cout<<"To send a message from client type: s <message>"<<endl;
	cout<<"To reply to cliene from server message type: r <message>"<<endl;
	cout<<"To exit type: x"<<endl;
}

int main() {
	cout << "Welcome to Tomer TCP messenger!!!" << endl;
	printInstructions();

	TCPP2PMessenger *server = new TCPP2PMessenger;
	TCPP2PMessenger *client= new TCPP2PMessenger;
	while (true){

		char buffer[1024];
		//string msg;
		string command;
		cin >> command;

		if(command == "cs"){

			int port;
			cin>>port;
			server->init(port);
			sleep(2);
		}
		else if (command == "cc"){
			string ip;
			cin>>ip;
			int port;
						cin>>port;
			client->open(ip, port);
		}
		else if(command=="s"){
			cin.getline(buffer,sizeof(buffer));
			client->send(buffer);
		}
		else if(command=="r"){
			cin.getline(buffer,sizeof(buffer));
			server->reply(buffer);
		}
		else if(command=="x"){
			cout<<"Bye Bye!!"<<endl;
			client->close();
			server->close();
			delete client;
			delete server;
			break;
		}
		else{
			cout<<command<<" -invalid inpup!"<<endl;
			printInstructions();
		}

	}


	return 0;
}
