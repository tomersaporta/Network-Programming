/*
 * TCPP2PMessenger.h
 *
 *  Created on: May 11, 2017
 *      Author: user
 */

#ifndef SRC_TCPP2PMESSENGER_H_
#define SRC_TCPP2PMESSENGER_H_

#include <iostream>
#include <string.h>
#include "TCPP2PServer.h"
#include "TCPP2PClient.h"

using namespace std;
namespace networkingLab {

class TCPP2PMessenger {

private:
	TCPP2PClient *client;
	TCPP2PServer *server;

public:
	TCPP2PMessenger();

	virtual ~TCPP2PMessenger();

	/*
	 * init open the messenger server on given port
	 *
	 * @param port- server port number
	 *
	 */
	void init(size_t port);



	/*open a connection to the given IP address and once
		the connection is established it will open a thread to read incoming messages
		from the socket.*/
	bool open (string ip, size_t port);

	/*send a message on the client open connection, the
	message is sent in the form: [message length - 4 bytes][message data]*/
	void send(const char* msg);


	/*send a message on the server socket incomming
		connection, the message is sent in the form: [message length - 4 bytes][message
		data]*/

	void reply(const char* msg);

	/*close all resources / sockets */

	void close();


	/* return true if the client socket is connected. */
	bool isActiveClientSession();

	/*return true if there is an open incoming connection*/
	bool isActivePeerSession();



};
}/* namespace networkingLab */
#endif /* SRC_TCPP2PMESSENGER_H_ */
