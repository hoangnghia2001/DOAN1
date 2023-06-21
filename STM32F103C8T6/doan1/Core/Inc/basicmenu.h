/*
 * basicmenu.h
 *
 *  Created on: May 27, 2023
 *      Author: hoang
 */

#ifndef INC_BASICMENU_H_
#define INC_BASICMENU_H_

typedef void (*MenuFunction)();

struct MenuItem{
	char * parentname;
	char * name;
	struct  MenuItem* subnext;
	struct  MenuItem* menunext;
	MenuFunction function;
};

void addmenuiem(){

}

#endif /* INC_BASICMENU_H_ */
