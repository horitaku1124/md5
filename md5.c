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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const uint32_t k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

static const uint32_t r[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t left_rotate(const uint32_t x, const uint32_t c)
{
	return ((x) << (c)) | ((x) >> (32 - (c))); 
}

static void word_to_byte(const uint32_t val, uint8_t bytes[4])
{
	for (int i = 0; i < 4; i++)
		bytes[i] = (uint8_t) (val >> (i * 8));
}

static void byte_to_word(const uint8_t bytes[4], uint32_t *pval)
{
	*pval = 0;
	for (int i = 0; i < 4; i++)
		*pval |= ((uint32_t) bytes[i] << (i * 8));
}

#define TEMPLATE_PROC(num, ff, fg) \
	static void proc##num(const uint32_t b, const uint32_t c, const uint32_t d, \
			const uint32_t i, uint32_t *pf, uint32_t *pg) \
{ \
	*pf = ff; \
	*pg = fg; \
}

TEMPLATE_PROC(0,
		(b & c) | ((~b) & d), i);

TEMPLATE_PROC(1,
		(d & b) | ((~d) & c), (5 * i + 1) % 16);

TEMPLATE_PROC(2,
		b ^ c ^ d, (3 * i + 5) % 16);

TEMPLATE_PROC(3,
		c ^ (b | (~d)), (7 * i) % 16);

typedef void (*proc_func_t)(const uint32_t, const uint32_t,
		const uint32_t, const uint32_t, uint32_t *, uint32_t *);

static proc_func_t procs[4] = {proc0, proc1, proc2, proc3};

/**
 * Encrypt a chunk of data using MD5 algorithm.
 *
 * @arg	Data to encrypt
 * @arg Data size in byte
 * @arg Memory block to hold result, ensure at least 16 bit length
 *
 * @pre  None
 * @post None
 */
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {

	size_t new_len;
	for (new_len = initial_len + 1; new_len % (512 / 8) != 448 / 8;
			new_len++);

	uint8_t *msg = (uint8_t*) malloc(new_len + 8);
	memcpy(msg, initial_msg, initial_len);
	msg[initial_len] = 0x80;
	for (size_t i = initial_len + 1; i < new_len; i++)
		msg[i] = 0;

	word_to_byte(initial_len * 8, msg + new_len);
	word_to_byte(initial_len >> 29, msg + new_len + 4);

	uint32_t w[16], alpha[4];
	uint32_t f, g, temp;
	uint32_t h[] = {
		0x67452301, 0xefcdab89,
		0x98badcfe, 0x10325476};

	for(size_t offset = 0; offset < new_len; offset += 512 / 8) {
		for (int i = 0; i < 16; i++)
			byte_to_word(msg + offset + i * 4, w + i);

		for (int i = 0; i < 4; i++)
			alpha[i] = h[i];

		for(int i = 0; i < 64; i++) {
			procs[i / 16](alpha[1], alpha[2], alpha[3], i, &f, &g);

			temp = alpha[3];
			alpha[3] = alpha[2];
			alpha[2] = alpha[1];
			alpha[1] = alpha[1] + left_rotate((alpha[0] + f + k[i] + w[g]), r[i]);
			alpha[0] = temp;
		}

		for (int i = 0; i < 4; i++)
			h[i] += alpha[i];
	}

	free(msg);
	for (int i = 0; i < 4; i++)
		word_to_byte(h[i], digest + 4 * i);
}


/**
 * Encrypt a chunk of data using MD5 algorithm.
 *
 * @arg	Data to encrypt
 * @arg Data size in byte
 * @arg Memory block to hold result, ensure at least 16 bit length
 *
 * @pre  None
 * @post None
 */
void md5_located(uint8_t *msg, size_t initial_len, size_t new_len, uint8_t *digest) {

	msg[initial_len] = 0x80;

	word_to_byte(initial_len * 8, msg + new_len);

	uint32_t w[16], alpha[4];
	uint32_t f, g, temp;
	uint32_t h[] = {
		0x67452301, 0xefcdab89,
		0x98badcfe, 0x10325476};

	for(size_t offset = 0; offset < new_len; offset += 64) {
		for (int i = 0; i < 16; i++)
			byte_to_word(msg + offset + i * 4, w + i);

		for (int i = 0; i < 4; i++)
			alpha[i] = h[i];

		for(int i = 0; i < 64; i++) {
			procs[i / 16](alpha[1], alpha[2], alpha[3], i, &f, &g);

			temp = alpha[3];
			alpha[3] = alpha[2];
			alpha[2] = alpha[1];
			alpha[1] = alpha[1] + left_rotate((alpha[0] + f + k[i] + w[g]), r[i]);
			alpha[0] = temp;
		}

		for (int i = 0; i < 4; i++)
			h[i] += alpha[i];
	}

	for (int i = 0; i < 4; i++)
		word_to_byte(h[i], digest + 4 * i);
}