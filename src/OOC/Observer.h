# ifndef Observer_h
# define Observer_h

# include "Object.h"

extern const void * const Observer (void);

void update (void * _self, int value);

extern const void * const ObserverClass (void);

# endif
