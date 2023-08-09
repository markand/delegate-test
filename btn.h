#ifndef BTN_H
#define BTN_H

struct btn_delegate;

struct btn {
	int x, y;
	const char *title;
	struct btn_delegate *dlg;
};

void
btn_init(struct btn *, struct btn_delegate *);

void
btn_update(struct btn *);

void
btn_draw(struct btn *);

void
btn_finish(struct btn *);

#endif /* !BTN_H */
