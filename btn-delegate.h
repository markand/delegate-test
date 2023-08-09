#ifndef BTN_DELEGATE_H
#define BTN_DELEGATE_H

#include "common.h"

#define BTN_DELEGATE_DEFAULT(dlg) \
	container_of(dlg, struct btn_delegate_default, iface)

struct btn;

// abstract interface
struct btn_delegate {
	void (*update)(struct btn_delegate *, struct btn *);
	void (*draw)(struct btn_delegate *, struct btn *);
	void (*finish)(struct btn_delegate *, struct btn *);
};

// default implementation
struct btn_delegate_default {
	unsigned int elapsed;
	unsigned int animation;
	struct btn_delegate iface;
};

void
btn_delegate_default_init(struct btn_delegate_default *, struct btn *);

void
btn_delegate_default_finish(struct btn_delegate_default *, struct btn *);

#endif /* BTN_DELEGATE_H */
