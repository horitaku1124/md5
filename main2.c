
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
	for(int i = 0;i < len;i++) {
		msg[i] = argv[1][i];
	}


	md5((uint8_t*) msg, len, result);
	for (int i = 0; i < 16; i++)
		printf("%2.2x", result[i]);
	puts("");

	free(msg);
	return EXIT_SUCCESS;
}

