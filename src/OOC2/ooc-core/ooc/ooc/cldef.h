#ifndef OOC_OOC_OOC_H
#error "libooc: use ooc/ooc/ooc.h instead of ooc/ooc/cldef.h directly"
#endif 

/*
 ******************************
 * Core classes definition
 * -----
 * Object Oriented C progamming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: cldef.h,v 1.14 2005/12/15 16:58:59 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 ******************************
 */

/*
 * Base definitions (not seen by the reflection)
 */

#define CLASSDEF_OOC_AnyObject			\
  ooc_visible(OOC__ISA , _isa)			\
  ooc_visible(unsigned , _cnt)

#define CLASSDEF_OOC_AnyClass						\
  ooc_visible(OOC__SPR , _spr)						\
  ooc_visible(OOC__DAT , _dat)						\
  CLASSDEF_OOC_AnyClass_init						\
  ooc_visibleP(void    , initialize  , (void))				\
  ooc_visibleP(void    , deinitialize, (void))				\
  ooc_visibleP(TYPE    , init        , (TYPE))				\
  ooc_visibleP(void    , deinit      , (TYPE))				\
  ooc_visibleP(Object  ,  cast       , (TYPE, classObject   cls))	\
  ooc_visibleP(Protocol, pcast       , (TYPE, classProtocol cls))

#if OOC_THREAD_USE
#define CLASSDEF_OOC_AnyClass_init ooc_visibleP(void, _init, (void))
#else
#define CLASSDEF_OOC_AnyClass_init
#endif
