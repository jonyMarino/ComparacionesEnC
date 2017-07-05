# include "SensedValueDisplay.h"
# include "SensedValueDisplay.r"

#include <stdio.h>

static void * SensedValueDisplay_ctor (void * _self, va_list * app) {
	struct SensedValueDisplay * self = super_ctor(SensedValueDisplay(), _self, app);

	return self;
}

static void SensedValueDisplay_update (void * _self, int value) {
	struct SensedValueDisplay * self = cast(SensedValueDisplay(), _self);

	printf("updated: %d\n",value);
}

static const void * _SensedValueDisplay;

const void * const SensedValueDisplay (void) {
	return _SensedValueDisplay ? _SensedValueDisplay :
		(_SensedValueDisplay = new(ObserverClass(),
			"SensedValueDisplay", Observer(), sizeof(struct SensedValueDisplay),
			ctor, "ctor", SensedValueDisplay_ctor,
			update, "update", SensedValueDisplay_update,
			(void *) 0));
}
