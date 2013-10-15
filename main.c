/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Junyu Wu, SYSU 11331315, 2013
 */

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./md5.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Target required\n");
		return 1;
	}

	/* Open file and read, then call MD5 */

	FILE *pf = fopen(argv[1], "r");
	if (pf == NULL) {
		perror("Open file: ");
		exit(1);
	}

	char msg[SHRT_MAX * CHAR_MAX];
	size_t len = fread(msg, sizeof(char), SHRT_MAX * CHAR_MAX, pf);
	if (errno != 0) {
		perror("read file: ");
		fclose(pf);
		exit(1);
	}
	fclose(pf);

	uint8_t result[16];
	md5((uint8_t*) msg, len, result);
	for (int i = 0; i < 16; i++)
		printf("%2.2x", result[i]);
	puts("");

	return EXIT_SUCCESS;
}

