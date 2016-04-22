/*-
 * Copyright (c) 2016 Alistair Crooks <agc@NetBSD.org>
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted providing that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "delta.h"

int
main(int argc, char **argv)
{
	int	dodiff;
	int	ok;
	int	i;

	dodiff = 0;
	while ((i = getopt(argc, argv, "dp")) != -1) {
		switch(i) {
		case 'd':
			dodiff = 1;
			break;
		case 'p':
			dodiff = 0;
			break;
		}
	}
	if (argc - optind != 3) {
		fprintf(stderr, "Usage: %s oldfile newfile patchfile\n", *argv);
		exit(EXIT_FAILURE);
	}
	ok = (dodiff) ?
		delta_diff_file(argv[optind], argv[optind + 1], argv[optind + 2]) :
		delta_patch_file(argv[optind], argv[optind + 1], argv[optind + 2]);
	exit((ok) ? EXIT_SUCCESS : EXIT_FAILURE);
}
