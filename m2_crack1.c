
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./md5_2.h"

int g_targetLen = 0;
int g_candidateLen = 0;
uint8_t* g_targetChar;
uint8_t* g_result;
uint8_t* g_input;

int new_message_len = 0;

int decrypt(uint8_t* cand, int depth)
{
	if(depth == 0)
	{
	
		MD5_CTX c;
		for(int i = 0;i < g_targetLen;i++)
		{
			cand[0] = g_targetChar[i];
			
			MD5_Init(&c);
			MD5_Update(&c, cand,(unsigned long)g_candidateLen);
			MD5_Final(&(g_result[0]),&c);

			short sameArray = 1;
			for(int j = 0;j < 16;j++)
			{
				if(g_input[j] != g_result[j])
				{
					sameArray = 0;
					break;
				}
			}
			if(sameArray)
			{
				printf("\n Found => ");
				for (int k = 0; k < g_candidateLen; k++)
				{
					printf("%c", cand[k]);
				}
				printf("\n");
				return 1;
			}
		}
	}
	else
	{
		for(int i = 0;i < g_targetLen;i++)
		{
			cand[depth] = g_targetChar[i];
			decrypt(cand, depth - 1);
		}
	}
	return 0;
}

uint8_t ctoi(char c)
{
	if(c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else if(c >= 'a' && c <= 'z')
	{
		return c - 'a' + 10;
	}
	else if(c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 10;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char* targetChar = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char* md5str;
	uint8_t input[16];
	int targetLen = 4; // Must be less than 56
	uint8_t* candidate;

	if (argc < 2) {
		fprintf(stderr, "Target required\n");
		return 1;
	}

	int len = strlen(argv[1]);
	md5str = malloc(sizeof(char) * (len + 1));
	strcpy(md5str, argv[1]);
	int inputLen = strlen(md5str) / 2;
	//printf("md5str = %s\n", md5str);


	for(int i = 0;i < inputLen;i++) {
		uint8_t c1 = ctoi(md5str[2 * i]);
		uint8_t c2 = ctoi(md5str[2 * i + 1]);
		input[i] = c1 * 16;
		input[i] += c2;
	}

	g_input = input;
	g_targetChar = (uint8_t*)targetChar;
	g_targetLen = strlen(targetChar);
	g_result = malloc(sizeof(uint8_t) * 16);

	new_message_len = 56;


	for(int j = 0;j < targetLen;j++) {
		int candLen = j + 1;
		candidate = malloc(sizeof(char) * candLen);
		for(int i = 0;i < candLen;i++) {
			candidate[i] = (uint8_t)targetChar[0];
		}

		g_candidateLen = candLen;

		decrypt(candidate, candLen - 1);
		free(candidate);
	}

	free(md5str);
	free(g_result);
	return 0;
}

