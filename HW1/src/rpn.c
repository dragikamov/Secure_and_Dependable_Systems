/*
 * rpn.c --
 */

/** @file */

#include "rpn-stack.h"
#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Evaluate an expression in reverse polish notation.
 *
 * \param token Array of tokens making up the expression.
 * \param result Pointer to the string which will hold the result (malloced).
 * \result One of the error codes defined above.
 */
int rpn_eval_token(char *token[], char **result)
{
    int i = 0, n = 0;

	char *r;

	rpn_stack_t *st = rpn_stack_new();

	// Here is where I am using the later mentioned number of tokens
	for(i = 1; i < atoi(token[0]); i++)
	{
		// Checking if I need to do a computation
		if(n % 2 == 0 && n != 0)
		{
			int j = 0;

			// Checking if it is a number instead of an operator
			while(token[i][j] != '\0')
			{
				if(token[i][j] >= '0' && token[i][j] <= '9')
				{
					return RPN_MISSING_OPERATOR;
				}
				j++;
			}
			
			// Checking if it is a word instead of an operator
			if(!(strcmp(token[i],"+") == 0 || strcmp(token[i],"-") == 0 || strcmp(token[i],"*") == 0 || strcmp(token[i],"/") == 0))
			{
				*result = token[i];
				return RPN_INVALID_TOKEN;
			}
			
			// If none of those checks was the case then I do the respective computation
			if(strcmp(token[i], "+") == 0)
			{
				int a = *(int*)rpn_stack_pop(st);
				n--;
				int b = *(int*)rpn_stack_pop(st);
				n--;
				int res = a + b;
				rpn_stack_push(st, &res);
				n++;
				
				// Transforming the value to a string to be put on result
				char tempR[15];
				sprintf(tempR,"%d",*(int*)rpn_stack_peek(st));
				r = tempR;
				
				*result = r;
				
			}
			else if(strcmp(token[i], "-") == 0)
			{
				int a = *(int*)rpn_stack_pop(st);
				n--;
				int b = *(int*)rpn_stack_pop(st);
				n--;
				int res = b - a;
				rpn_stack_push(st, &res);
				n++;
				
				char tempR[15];
				sprintf(tempR,"%d",*(int*)rpn_stack_peek(st));
				r = tempR;
				
				*result = r;
			}
			else if(strcmp(token[i], "*") == 0)
			{
				int a = *(int*)rpn_stack_pop(st);
				n--;
				int b = *(int*)rpn_stack_pop(st);
				n--;
				int res = a * b;
				rpn_stack_push(st, &res);
				n++;
				
				char tempR[15];
				sprintf(tempR,"%d",*(int*)rpn_stack_peek(st));
				r = tempR;
				
				*result = r;
			}
			else if(strcmp(token[i], "/") == 0)
			{
				int a = *(int*)rpn_stack_pop(st);
				n--;
				int b = *(int*)rpn_stack_pop(st);
				n--;
				if(a == 0)
				{
					return RPN_ARITHMETIC_ERROR;
				}
				
				char tempR[15];
				n++;

				// Checking if the division would give a decimal number
				if(!((double)(b / a) == (int)(b / a)))
				{
					double res = b / a;
					rpn_stack_push(st, &res);
					sprintf(tempR,"%.2lf",*(double*)rpn_stack_peek(st));
				}
				else
				{
					int res = b / a;
					rpn_stack_push(st, &res);
					sprintf(tempR,"%d",*(int*)rpn_stack_peek(st));
				}
				
				r = tempR;
				
				*result = r;
			}
		}
		else
		{
			// Here I am pushing the numbers to the stack

			// Checking if it is a sign operator instead of an operand
			if(strcmp(token[i],"+") == 0 || strcmp(token[i],"-") == 0 || strcmp(token[i],"*") == 0 || strcmp(token[i],"/") == 0)
			{
				return RPN_MISSING_OPERAND;
			}

			int j = 0;
			
			// Checking if it is a word instead of an operand
			while(token[i][j] != '\0')
			{
				if(token[i][j] < '0' || token[i][j] > '9')
				{
					*result = token[i];
					return RPN_INVALID_TOKEN;
				}
				j++;
			}

			// Converting the string to a number and pushing it to the stack
			int val = atoi(token[i]);
			rpn_stack_push(st, &val);

			// If it is only one number there then save it as a result and end the function,
			// or check if there are two numbers and there is not a third member of the string
			if(n == 0 && atoi(token[0]) == 2)
			{
				*result = token[i];
				return RPN_OK;
			}
			else if(n == 1 && atoi(token[0]) == 3)
			{
				return RPN_MISSING_OPERATOR;
			}

			n++;
		}
	}
	return RPN_OK;
}

/**
 * \brief Evaluate an expression in reverse polish notation.
 *
 * \param expr The expression (whitespace separated numbers and operators)
 * \param result Pointer to the string which will hold the result (malloced).
 * \result One of the error codes defined above.
 */ 
int rpn_eval_expr(const char *expr, char **result)
{
    char *str = (char*)expr;
	char delim[] = " ";
	int n = 1;
	char *token[128];

	// Splitting the expression on the whitespaces
	char *ptr = strtok(str, delim);

	while(ptr != NULL)
	{
		token[n++] = ptr;
		ptr = strtok(NULL, delim);
	}

	// Putting the amount of tokens I have in the expression on token[0]
	token[0] = (char*) malloc(4 * sizeof(char));
	sprintf(token[0],"%d",n);

    return rpn_eval_token(token, result);
}