#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "common.h"
#include "btn.h"
#include "btn-delegate.h"

void
btn_init(struct btn *b, struct btn_delegate *d)
{
	assert(b);

	b->x = 0;
	b->y = 0;
	b->title = NULL;

	// offer default implementation if not provided.
	if (d)
		b->dlg = d;
	else
		btn_delegate_default_new(b);
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
