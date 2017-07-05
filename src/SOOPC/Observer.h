/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/Observer.h
 * Code Management Tool File Version: 
 * SDD Component: Observer
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file SOOPC/Observer.h
 * \brief Observer
 */

#ifndef SOOPC_Observer_H
#define SOOPC_Observer_H

/* Dependency with parent package */
#include "SOOPC.h"
/**********************************************************************************
 * SOOPC/Observer.h
 **********************************************************************************/

/*## package SOOPC */

/*! 
 * \package Observer
 */
struct ObserverVtbl;
/*## class TopLevel::Observer */



//Class Observer declaration
typedef struct {
	struct ObserverVtbl const *vptr;
}Observer;

//Class Observer V-Table
typedef struct ObserverVtbl{
	void (*update)(Observer * self, int value);
}ObserverVtbl;


void Observer_update (Observer * self, int value);


#endif

/**********************************************************************************
 * File Path: SOOPC/Observer.h
 **********************************************************************************/
