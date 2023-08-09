#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "btn.h"
#include "btn-delegate.h"

// wrap default implementation dynamically for convenience

static void
delegate_finish(struct btn_delegate *d, struct btn *b)
{
	struct btn_delegate_default *def = BTN_DELEGATE_DEFAULT(d)

	def = container_of(d, struct btn_delegate_default, iface);

	free(def);
	b->dlg = NULL;
}

static void
delegate_set(struct btn *b)
{
	struct btn_delegate_default *d;

	d = calloc(1, sizeof (*d));

	btn_delegate_default_init(d, b);
	d->iface.finish = delegate_finish;
}

void
btn_init(struct btn *b, struct btn_delegate *d)
{
	assert(b);

	b->x = 0;
	b->y = 0;
	b->title = NULL;

	// offer default implementation if not provided.
	if (!d)
		delegate_set(b);
	else
		b->dlg = d;
}

void
btn_update(struct btn *b)
{
	assert(b);

	b->dlg->update(b->dlg, b);
}

void
btn_draw(struct btn *b)
{
	assert(b);

	b->dlg->draw(b->dlg, b);
}

void
btn_finish(struct btn *b)
{
	assert(b);

	b->dlg->finish(b->dlg, b);
}
