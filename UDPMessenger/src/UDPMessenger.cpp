//============================================================================
// Name        : UDPMessenger.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "UDPMessenger.h"

using namespace std;


namespace networkingLab {

UDPMessenger::UDPMessenger() {
	//init
	udp_socket = new UDPSocket(MSG_PORT);
	isRun=true;
	this->start();
}

UDPMessenger::~UDPMessenger() {
	// TODO Auto-generated destructor stub
}

void UDPMessenger::sendTo(string msg,string ip,int port){
	cout<<"sendTo ip:"<<ip<<" port:"<<port<<" msg:" << msg <<endl;
	udp_socket->connect(ip, port);
	udp_socket->write(msg.data(), msg.length());
}

void UDPMessenger::reply(string msg){
	cout<<"reply"<<endl;
	udp_socket->reply(msg);
	//if (udp_socket->reply(msg)<0)
		//cout<<"Error reply"<<endl;
}

void UDPMessenger::close(){
	isRun=false;
	//close socket
	cout<<"close"<<endl;
	udp_socket->close();
	this->waitForThread();
	delete udp_socket;

}
void UDPMessenger::run(){

	while(isRun){
		int rec;
		char buffer [1024];
		rec = udp_socket->read(buffer,sizeof(buffer));
		if(rec<0)
			break;
		buffer[rec]= '\0';
		cout<<"\n message from: "<< udp_socket->fromAddr()<<"\n-------------------------\n"<<buffer<<"\n-------------------------"<<endl;
	}

}

} /* namespace networkingLab */
