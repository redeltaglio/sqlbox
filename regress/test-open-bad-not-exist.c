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

#include <sys/param.h>
#include <sys/stat.h>

#if HAVE_ERR
# include <err.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../sqlbox.h"
#include "regress.h"

int
main(int argc, char *argv[])
{
	char			 db[MAXPATHLEN];
	struct stat		 st;
	struct sqlbox		*p;
	struct sqlbox_cfg	 cfg;
	struct sqlbox_src	 srcs[] = {
		{ .fname = db,
		  .mode = SQLBOX_SRC_RW }
	};

	strlcpy(db, tmpnam(NULL), sizeof(db));

	memset(&cfg, 0, sizeof(struct sqlbox_cfg));
	cfg.srcs.srcs = srcs;
	cfg.srcs.srcsz = nitems(srcs);
	cfg.msg.func_short = warnx;

	if (stat(srcs[0].fname, &st) != -1)
		errx(EXIT_FAILURE, "%s: exists", srcs[0].fname);
	if ((p = sqlbox_alloc(&cfg)) == NULL)
		errx(EXIT_FAILURE, "sqlbox_alloc");
	if (sqlbox_open(p, 0))
		errx(EXIT_FAILURE, "sqlbox_open should fail");

	sqlbox_free(p);

	if (stat(srcs[0].fname, &st) != -1)
		errx(EXIT_FAILURE, "%s: exists", srcs[0].fname);

	return EXIT_SUCCESS;
}
