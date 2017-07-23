/*
 * ClientHandlerCLI.cpp
 *
 *  Created on: Jun 17, 2017
 *      Author: user
 */

#include "ClientHandlerCLI.h"

namespace networkingLab {

ClientHandlerCLI::ClientHandlerCLI() {
	// TODO Auto-generated constructor stub

}

void ClientHandlerCLI::onMessageRecived(string message) {
	cout << "Recived message from client: " << message << endl;
}

void ClientHandlerCLI::onOpenSession(string ipPort) {
	cout << "Open session with ip port: " << ipPort << endl;
}

void ClientHandlerCLI::onClosedSession() {
	cout << "Close session" << endl;
}

ClientHandlerCLI::~ClientHandlerCLI() {

	// TODO Auto-generated destructor stub
}

} /* namespace networkingLab */
