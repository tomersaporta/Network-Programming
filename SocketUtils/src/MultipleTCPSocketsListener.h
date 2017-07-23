/*
 * MultipleTCPSocketsListener.h
 *
 *  Created on: Feb 14, 2013
 *      Author: efi
 */

#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "TCPSocket.h"

using namespace std;


namespace networkingLab{

class MultipleTCPSocketsListener{
//class properties which include a vector (this will be the socket list) to hold the given sockets
	typedef vector<TCPSocket*> socketVector;
		socketVector sockets;

public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Set the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket();

	/*
	 * Remove socket from vector
	 *
	 */
	int removeSocket(TCPSocket* socket);

	/*
	 * Search socket in the vector and return
 	 *
	 */
	TCPSocket * searchSocket(int port,string ip);

	string getPeerList();
};

} /* namespace networkingLab */

#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */

