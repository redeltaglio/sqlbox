
/*	$Id$ */
/*
 * Copyright (c) 2019 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHORS DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include "../config.h"

#if HAVE_ERR
# include <err.h>
#endif
#include <stdlib.h>
#include <string.h>

#include "../sqlbox.h"

int
main(int argc, char *argv[])
{
	struct sqlbox		*p;
	struct sqlbox_cfg	 cfg;

	memset(&cfg, 0, sizeof(struct sqlbox_cfg));
	cfg.msg.func_short = warnx;

	cfg.roles.rolesz = 3;
	cfg.roles.roles = calloc(3, sizeof(struct sqlbox_role));
	if (cfg.roles.roles == NULL)
		err(EXIT_FAILURE, NULL);

	cfg.roles.roles[0].rolesz = 2;
	cfg.roles.roles[0].roles = calloc(1, sizeof(size_t));
	if (cfg.roles.roles[0].roles == NULL)
		err(EXIT_FAILURE, NULL);
	cfg.roles.roles[0].roles[0] = 1;
	cfg.roles.defrole = 0;

	if ((p = sqlbox_alloc(&cfg)) == NULL)
		return EXIT_FAILURE;

	/* Fail: we can't go from 0 -> 2. */

	if (!sqlbox_role(p, 2))
		return EXIT_FAILURE;
	if (sqlbox_ping(p))
		return EXIT_FAILURE;
	sqlbox_free(p);
	return EXIT_SUCCESS;
}