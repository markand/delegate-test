#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "btn-delegate.h"
#include "btn.h"
#include "common.h"

static void
default__update(struct btn_delegate *d, struct btn *b)
{
	(void)b;

	struct btn_delegate_default *def = BTN_DELEGATE_DEFAULT(d);

	def->elapsed += 10;
	puts("== default ==");
	printf("  --> update (data = %p, elapsed = %d)\n\n", def, def->elapsed);
}

static void
default__draw(struct btn_delegate *d, struct btn *b)
{
	struct btn_delegate_default *def = BTN_DELEGATE_DEFAULT(d);

	puts("== default ==");
	printf("  --> draw (data = %p, animation = %d, title = %s)\n\n", def, def->animation, b->title);
}

static void
default__finish(struct btn_delegate *d, struct btn *b)
{
	struct btn_delegate_default *def = BTN_DELEGATE_DEFAULT(d);

	// forward to public function
	btn_delegate_default_finish(def, b);
}

static void
default__finish_free(struct btn_delegate *d, struct btn *b)
{
	struct btn_delegate_default *def = BTN_DELEGATE_DEFAULT(d);

	// call default impl and then free.
	btn_delegate_default_finish(def, b);
	free(def);
}

void
btn_delegate_default_new(struct btn *b)
{
	struct btn_delegate_default *ret;

	ret = calloc(1, sizeof (*ret));
	btn_delegate_default_init(ret, b);
	ret->iface.finish = default__finish_free;
}

void
btn_delegate_default_init(struct btn_delegate_default *d, struct btn *b)
{
	puts("== default ==");
	printf("  --> init (data = %p)\n\n", d);

	d->elapsed = 0;
	d->animation = 300;
	d->iface.update = default__update;
	d->iface.draw = default__draw;
	d->iface.finish = default__finish;

	b->dlg = &d->iface;
}

void
btn_delegate_default_finish(struct btn_delegate_default *d, struct btn *b)
{
	(void)b;

	puts("== default ==");
	printf("  --> finish (data = %p)\n\n", d);
}
