/*
 * main.c --
 */

/** @file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/rpn-stack.h"
#include "src/rpn.h"

#include "src/rpn-stack.c"
#include "src/rpn.c"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("Too few arguments\n");
		return 0;
	}

	char **it = argv;
	it++;
	char in[1024] = "";

	int i = 1;
	for(i = 1; i < argc; i++)
	{
		strcat(in, *it);
		strcat(in, " ");
		it++;
	}

	char *t = "None";
    char **temp = &t;

	int res = rpn_eval_expr(in,temp);
	if(res == 0)
	{
		printf("%s\n", *temp);
	}
	else if(res == -1)
	{
		printf("rpnc: invalid token '%s'\n", *temp);
	}
	else if(res == -2)
	{
		printf("rpnc: missing operand\n");
	}
	else if(res == -3)
	{
		printf("rpnc: missing operator\n");
	}
	else
	{
		printf("rpnc: arithmetic error\n");
	}
	
    return 0;
}
