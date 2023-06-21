/*
 * state.c
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#include "state.h"
#include "stateMenu.h"
#include "stateCardID.h"
#include "stateFaceID.h"


void statemachineupdate(enum Status *state){

	switch(*state){
	case Menu:
		startmenu();
		*state = Free;
		break;
	case CardID:
		startcard();
		*state = Free;
		break;
	case FaceID :
		startface();
		*state = Free;
		break;
	case Free:
		break;
	}

}
