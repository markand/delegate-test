#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "btn-delegate.h"
#include "btn.h"

#define MY_DELEGATE(dlg) \
	container_of(dlg, struct my_delegate, parent.iface)

struct my_delegate {
	int color;
	int shadow;
	struct btn_delegate_default parent;
};

static void
my_delegate__draw(struct btn_delegate *d, struct btn *b)
{
	struct my_delegate *mdy = MY_DELEGATE(d);

	puts("== my_delegate ==");
	printf("  --> draw (data = %p, color = %d, shadow = %d, title = %s)\n\n",
	    mdy, mdy->color, mdy->shadow, b->title);
}

static void
my_delegate__finish(struct btn_delegate *d, struct btn *b)
{
	struct my_delegate *mdy = MY_DELEGATE(d);

	// don't forget to cleanup parent too.
	btn_delegate_default_finish(&mdy->parent, b);

	puts("== my_delegate ==");
	printf("  --> finish (data = %p)\n\n", mdy);

	free(mdy);
}

void
my_button_init(struct btn *b)
{
	struct my_delegate *mdy;

	// allocate on the heap for user convenience.
	mdy = calloc(1, sizeof (*mdy));
	mdy->color = 1234;
	mdy->shadow = 9911;

	btn_delegate_default_init(&mdy->parent, b);
	mdy->parent.iface.draw = my_delegate__draw;
	mdy->parent.iface.finish = my_delegate__finish;

	puts("== my_delegate ==");
	printf("  --> init (data = %p)\n\n", mdy);
}

// custom extension
static void
example_1(void)
{
	struct btn button;

	puts("== EXAMPLE 1 ==");
	puts("---------------");

	my_button_init(&button);
	button.x = 10;
	button.y = 20;
	button.title = "Custom";
	btn_update(&button);
	btn_draw(&button);
	btn_finish(&button);
}

// full default implementation
static void
example_2(void)
{
	struct btn button;

	puts("== EXAMPLE 2 ==");
	puts("---------------");

	btn_init(&button, NULL);
	button.x = 10;
	button.y = 20;
	button.title = "Default";
	btn_update(&button);
	btn_draw(&button);
	btn_finish(&button);
}

int
main(void)
{
	example_1();
	example_2();
}
