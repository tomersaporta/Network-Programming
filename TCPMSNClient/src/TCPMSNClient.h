
/*
 * TCPMSNClient.h
 *
 *  Created on: Jun 11, 2017
 *      Author: Tomer Saporta
 */

#ifndef SRC_TCPMSNCLIENT_H_
#define SRC_TCPMSNCLIENT_H_

#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "MThread.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
namespace networkingLab {



// Abstract class implementation in TCPMSNClientTest ans TCPMSNClientCLI
class TCPMSNClientHandler{
public:
	virtual void onMessageRecived(string message)=0;
	virtual void onOpenSession(string ipPort)=0;
	virtual void onClosedSession()=0;
	virtual ~TCPMSNClientHandler(){}
};


class TCPMSNClient :public MThread{

public:
	TCPSocket *client;
	TCPMSNClientHandler * handler;
	bool isConnected;

	TCPMSNClient(TCPMSNClientHandler * handler);
	virtual ~TCPMSNClient();

	/*
	 * connect the client to remote server on given ip,
	 *  the server readied from the protocol
	 *
	 *  @param ip- the ip of the server to connect to
	 *
	 *  @return true on success otherwise false
	 */
	bool connect(string ip);

	/*
	 * open session between the client to other client on given ip and port
	 *
	 *  @param ip- the ip of the remote client to connect to
	 *	@param port- the port of the remote client to connect to
	 *
	 *  @return true on success otherwise false
	 */
	bool openSession(string ip, int port);

	/*
	 * send message to the connected remote client
	 *
	 *  @param msg- message to send to
	 *
	 */

	void sendMessage(string msg);

	/*
	 * close the session with the remote client
	 */
	void closeSession();

	/*
	 * disconnect the session with the server
	 */
	void disconnect();

	/*
	 * closing the application
	 */
	void exit();
	/*
	 * @return  int- the client port
	 */
	int getPort();
	/*
	 * run thread
	 */
	virtual void run();

	int sendCommand(int cmd,const char* buff);

	void recvCommand();

};

} /* namespace networkingLab */

#endif /* SRC_TCPMSNCLIENT_H_ */
