/*
 * BrokerMng.h
 *
 *  Created on: Jun 26, 2017
 *      Author: user
 */

#ifndef SRC_BROKERMNG_H_
#define SRC_BROKERMNG_H_

#include "TCPSocket.h"
#include "Broker.h"
#include "BrokerMngHandler.h"

namespace networkingLab {


class BrokerMng {
	BrokerMngHandler* handler;
public:
	BrokerMng(BrokerMngHandler* handler);
	void createBroker(TCPSocket* peer1, TCPSocket* peer2);
	void rleasePeer(TCPSocket* peer);
	//void deleteBroker(Broker* broker);
	virtual ~BrokerMng();
};

} /* namespace networkingLab */

#endif /* SRC_BROKERMNG_H_ */
