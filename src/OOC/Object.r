# ifndef Object_r
# define Object_r

#include <assert.h>

struct Method {
	const char * tag;
	Method selector;
	Method method;
};

struct Object {
	unsigned long magic;
	const void * class;
};

struct Class { struct Object _;
	const char * name;
	const void * super;
	size_t size;

	struct Method ctor;
	struct Method dtor;
	struct Method puto;
	struct Method delete;
	struct Method forward;
	struct Method new;
};

void * super_ctor (const void * _class, void * _self, va_list * app);
void * super_dtor (const void * _class, void * _self);
int super_puto (const void * _class, const void * _self, FILE * fp);
void super_delete (const void * _class, void * _self);
void super_forward (const void * _class, const void * _self, void * result, Method selector, const char * name, va_list * app);

struct Object * super_new (const void * _class, const void * _self, va_list * app);

#define	MAGIC	0x0effaced

# endif
