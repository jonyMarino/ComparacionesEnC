#ifndef OOC_OOC_LIB_MEMSRV_H
#define OOC_OOC_LIB_MEMSRV_H

/* Standard Object services tables */
extern struct ooc_memsrv ooc_memStdSrv[1];
extern struct ooc_memsrv ooc_memBigSrv[1];
extern struct ooc_memsrv ooc_memAbsSrv[1];
#if OOC_GC_USE
extern struct ooc_memsrv ooc_memGCSrv [1];
#endif

#endif /* OOC_OOC_LIB_MEMSRV_H */
