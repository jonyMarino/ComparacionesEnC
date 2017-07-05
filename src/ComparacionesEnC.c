/*
 ============================================================================
 Name        : ComparacionesEnC.c
 Author      : Jonathan Marino
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define SOOPC 0
#define OOC 1
#define LDOOPC 2
#define OOCS 3

#define SMELL OOC

#if SMELL == LDOOPC
#include "LDOOPC/SensedValueDisplay.h"
#elif SMELL == SOOPC
#include "SOOPC/SensedValueDisplay.h"
#elif SMELL == OOCS
#include "OOCS/SensedValueDisplay.h"
#include "OOCS/SensedValueDisplay_p.h"
#elif SMELL == OOC
#include "OOC/SensedValueDisplay.h"
#endif




int main(void) {
#if SMELL == LDOOPC
    t_SensedValueDisplay display[1] = { SensedValueDisplay.SensedValueDisplay() };
    sendMsg_(super(display,Observer), update) SMELL __;
#elif SMELL == SOOPC
	SensedValueDisplay display;
	SensedValueDisplay_ctor(&display);
	Observer_update(&display,SMELL);
#elif SMELL == OOCS
	struct SensedValueDisplay_attribute display_a = {{ 0, REFCNT_AUTO()} };
	struct SensedValueDisplay *display = (struct SensedValueDisplay*)&display_a;

	display->i = SensedValueDisplay_interface();
	//display->i->init(display);
	display->i->update(display,SMELL);
	//display->i->deinit(display);
#elif SMELL == OOC

	void *display = new( SensedValueDisplay() );
	update(display,SMELL);
	delete(display);

#endif

	return EXIT_SUCCESS;
}
