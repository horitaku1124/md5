#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5_2.h"

void print_digest(unsigned char *md);

int main(int argc, char **argv)
{
	int i;
	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];

	if (argc == 1)
	{
		printf("no arguement");
	}
	else
	{
		for (i = 1; i < argc;i++)
		{
			int len = strlen(argv[i]);
			MD5_Init(&c);
			MD5_Update(&c, argv[i],(unsigned long)len);
			MD5_Final(&(md[0]),&c);
			print_digest(md);
		}
	}
	return 0;
}

void print_digest(unsigned char *digest)
{
	int i;
	for (i=0; i < MD5_DIGEST_LENGTH; i++)
	{
		printf("%02x", digest[i]);
	}
	printf("\n");
}

