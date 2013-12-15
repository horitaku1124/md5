
#include <stdio.h>
#include "./md5.h"

int main(int argc, char *argv[])
{
	uint8_t result[16];
	uint8_t* msg;

	if (argc < 2) {
		fprintf(stderr, "Target required\n");
		return 1;
	}

	size_t len = strlen(argv[1]);
	msg = malloc((int)len * sizeof(uint8_t));
	for(size_t i = 0;i < len;i++) {
		msg[i] = argv[1][i];
	}


	size_t new_len = len;
	size_t initial_len = len;
	
	for (new_len = initial_len + 1; new_len % (512 / 8) != 448 / 8;
			new_len++);

	//printf(" new_len = %d\n", new_len);
	uint8_t *msg2 = (uint8_t*) malloc(new_len + 8);
	for(size_t i = 0;i < (new_len + 8);i++)
	{
		msg2[i] = 0;
	}
	memcpy(msg2, msg, len);


	md5_located( msg2, len, new_len, result);
	for (int i = 0; i < 16; i++)
		printf("%2.2x", result[i]);
	puts("");

	free(msg);
	return EXIT_SUCCESS;
}

