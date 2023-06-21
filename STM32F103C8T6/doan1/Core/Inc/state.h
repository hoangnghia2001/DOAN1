/*
 * state.h
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

enum Status{
	Free = 0,
	Menu,
	CardID,
	FaceID,
};

void statemachineupdate( enum Status *state);


#endif /* INC_STATE_H_ */
