/*
 * TPMessengerListener.h
 *
 *  Created on: May 22, 2017
 *      Author: Tomer Saporta
 */

#ifndef SRC_TPMESSENGERLISTENER_H_
#define SRC_TPMESSENGERLISTENER_H_

namespace networkingLab {

class TPMessengerListener {
public:

	//abstract class
		//void MSNHandler(char* msn)=0;
	TPMessengerListener();
	virtual ~TPMessengerListener();
};

} /* namespace networkingLab */

#endif /* SRC_TPMESSENGERLISTENER_H_ */
