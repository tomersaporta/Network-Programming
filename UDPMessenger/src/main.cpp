/*
 * main.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "UDPMessenger.h"
#include <iostream>

using namespace std;
using namespace networkingLab;


void printInstructions(){
	cout<<"To send a message type: s <ip> <port> <message>"<<endl;
	cout<<"To reply to a message type: r <message>"<<endl;
	cout<<"To exit type: x"<<endl;
}

int main(){

	cout<<"Welcome to UDP messenger"<<endl;
	UDPMessenger* messenger = new UDPMessenger();
	printInstructions();
	cout<<"local port: "<<messenger->MSG_PORT<<endl;
	while(true){
		//cout<<"from port"<<messenger->udp_socket->fromAddr())<<endl;
		string msg;
		string command;
		cin >> command;
		if(command == "s"){
			string ip;
			cin >> ip;
			int port;
			cin >> port;
			getline(std::cin,msg);
			if(msg.size()>0 && msg[0] == ' ') msg.erase(0,1);
			messenger->sendTo(msg,ip,port);
		}else if(command == "r"){
			getline(std::cin,msg);
			if(msg.size()>0 && msg[0] == ' ') msg.erase(0,1);
			cout<<"from add: "<<messenger->udp_socket->fromAddr()<<endl;
			messenger->reply(msg);
		}else if(command == "x"){
			break;
		}else{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}
	messenger->close();
	delete messenger;
	cout<<"messenger was closed"<<endl;

	return 0;

}


#endif /* MAIN_CPP_ */
