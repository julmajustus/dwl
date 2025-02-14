/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_scratchpad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:35:02 by jmakkone          #+#    #+#             */
/*   Updated: 2025/01/04 13:35:50 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
addscratchpad(const Arg *arg)
{
	Client *cc, *c = focustop(selmon);

	if (!c)
		return;
	/* Check if the added client is already a scratchpad client */
	wl_list_for_each(cc, &scratchpad_clients, link_temp) {
		if (cc == c)
			return;
	}
	if (!c->isfloating) {
		setfloating(c, 1);
	}
	wl_list_insert(&scratchpad_clients, &c->link_temp);
}

void
togglescratchpad(const Arg *arg)
{
	Client *c;
	Monitor *m = selmon;

	scratchpad_visible = !scratchpad_visible;
	if (scratchpad_visible) {
		wl_list_for_each(c, &scratchpad_clients, link_temp) {
			c->mon = m;
			c->tags = m->tagset[m->seltags];
			arrange(m);
			focusclient(c, 1);
		}
	} else {
		wl_list_for_each(c, &scratchpad_clients, link_temp) {
			c->tags = 0;
			focusclient(focustop(m), 1);
			arrange(m);
		}
	}
}

void
removescratchpad(const Arg *arg)
{
	Client *sc, *c = focustop(selmon);

	if (c && wl_list_length(&scratchpad_clients) > 0) {
		/* Check if c is in scratchpad_clients */
		wl_list_for_each(sc, &scratchpad_clients, link_temp) {
			if (sc == c) {
				wl_list_remove(&c->link_temp);
				break;
			}
		}
	}
}
