/*
 * ClientHandlerCLI.h
 *
 *  Created on: Jun 17, 2017
 *      Author: user
 */

#ifndef CLIENTHANDLERCLI_H_
#define CLIENTHANDLERCLI_H_

#include "TCPMSNClient.h"

namespace networkingLab {

class ClientHandlerCLI :public TCPMSNClientHandler{
public:
	virtual void onMessageRecived(string message);
	virtual void onOpenSession(string ipPort);
	virtual void onClosedSession();
	ClientHandlerCLI();
	virtual ~ClientHandlerCLI();
};

} /* namespace networkingLab */

#endif /* CLIENTHANDLERCLI_H_ */
