# include "Observer.h"
# include "Observer.r"

#include <stdio.h>

/*
 Observer ctor {
	struct Observer * self = super_ctor(Observer(), _self, app);

	return self;
}

 Observer dtor {
casts
	return super_dtor(Observer(), self);
}
*/

void update (void * _self, int value) {
	const struct ObserverClass * class = (const void *) classOf(_self);

	if (isOf(class, ObserverClass()) && class -> update.method) {

		((void (*) ()) class -> update.method)(_self, value);
	} else
		forward(_self, 0, (Method) update, "update", _self, value);
}

void super_update (const void * _class, void * _self, int value) {
	const struct ObserverClass * superclass = cast(ObserverClass(), super(_class));

	assert(superclass -> update.method);
	((void (*) ()) superclass -> update.method)(_self, value);
}

static void * ObserverClass_ctor (void * _self, va_list * app) {
	struct ObserverClass * self = super_ctor(ObserverClass(), _self, app);
	Method selector;
	va_list ap;
	va_copy(ap,*app);

	while ((selector = va_arg(ap, Method)))
	{	const char * tag = va_arg(ap, const char *);
		Method method = va_arg(ap, Method);

		if (selector == (Method) update)
		{	if (tag)
				self -> update.tag = tag,
				self -> update.selector = selector;
			self -> update.method = method;
			continue;
		}
	}
	return self;
}

static const void * _ObserverClass;

const void * const ObserverClass (void) {
	return _ObserverClass ? _ObserverClass :
		(_ObserverClass = new(Class(),
			"ObserverClass", Class(), sizeof(struct ObserverClass),
			ctor, "", ObserverClass_ctor,
			(void *) 0));
}

static const void * _Observer;

const void * const Observer (void) {
	return _Observer ? _Observer :
		(_Observer = new(ObserverClass(),
			"Observer", Object(), sizeof(struct Observer),
			(void *) 0));
}
