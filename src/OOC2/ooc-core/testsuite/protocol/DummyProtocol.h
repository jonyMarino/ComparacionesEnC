#ifndef OOC_TESTSUITE_PROTOCOL_DUMMYPROTOCOL_H
#define OOC_TESTSUITE_PROTOCOL_DUMMYPROTOCOL_H

#include <ooc/Object.h>

#include ooc_Interface

#define PROTOCOL    DummyProtocol
#define SUPER_CLASS Protocol

#define PROTODEF_DummyProtocol	\
    ooc_method0(int, mth1)	\
    ooc_method0(int, mth2)

#include ooc_End

#endif /* OOC_TESTSUITE_PROTOCOL_DUMMYPROTOCOL_H */
