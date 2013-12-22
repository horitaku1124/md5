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
 * Copyright (C) Junyu, SYSU 11331315, 2013
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
void md5(const uint8_t[], const size_t, uint8_t[]);


void word_to_byte(const uint32_t val, uint8_t bytes[4]);

void md5_located(uint8_t *msg, size_t initial_len, size_t new_len, uint8_t *digest);

void md5_located_55(uint8_t *msg, uint8_t *digest);
