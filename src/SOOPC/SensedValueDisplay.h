/**********************************************************************************
 * Copyright: 
 * Project: RootElement
 * File: SOOPC/SensedValueDisplay.h
 * Code Management Tool File Version: 
 * SDD Component: SensedValueDisplay
 * Language: C
 * Author: 
 **********************************************************************************/

/*!
 * \file SOOPC/SensedValueDisplay.h
 * \brief SensedValueDisplay
 */

#ifndef SOOPC_SensedValueDisplay_H
#define SOOPC_SensedValueDisplay_H

/* Dependency with parent package */
#include "SOOPC.h"
#include "Observer.h"
/**********************************************************************************
 * SOOPC/SensedValueDisplay.h
 **********************************************************************************/

/*## package SOOPC */

/*! 
 * \package SensedValueDisplay
 */

/*## class TopLevel::SensedValueDisplay */
//Class SensedValueDisplay V-Table
typedef struct{
	ObserverVtbl superClass;
}SensedValueDisplayVtbl;


//Class SensedValueDisplay declaration
typedef struct {
	Observer super;
}SensedValueDisplay;






void SensedValueDisplay_ctor (SensedValueDisplay * self);

#endif

/**********************************************************************************
 * File Path: SOOPC/SensedValueDisplay.h
 **********************************************************************************/
