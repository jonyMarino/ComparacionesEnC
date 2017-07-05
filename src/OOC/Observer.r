# ifndef Observer_r
# define Observer_r

# include "Object.r"

struct Observer { const struct Object _;
};

struct ObserverClass { const struct Class _;
	struct Method update;
};

void super_update (const void * _class, void * _self, int value);

# endif
