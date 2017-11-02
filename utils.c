#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

//void print_list(char** list);

//char **list_of_strings(char *s);



char **list_of_strings(char *s)
{
	
	char *message = s;
	int length_of_message = strlen(message);

	char **list = malloc(100 * sizeof(char *));;
	for (int i = 0; i < 100; i++)
		list[i] = (char *)0;
		
	char buf_string[100];
	int index_list = 0;
	char c;
	int in_word = 1; //state
	int index_string = 0;


	for (int i = 0; i < length_of_message ; i++)
	{
		c = message[i];
		if (c == ' ' || c == '\n' || c == '\t')
		{
			if (in_word == 1)
			{
				in_word = 0;
				buf_string[index_string] = '\0';
				//char *new_s = malloc(strlen(buf_string) * sizeof(char));
				char *new_s = malloc((index_string + 1) * sizeof(char));
				list[index_list] = strcpy(new_s, buf_string);
				index_list++;
								
			}	
			index_string = 0;
		}	
		else
		{
			in_word = 1;
			buf_string[index_string] = c;
			index_string++;		
		}
	}
	return list;
}


void print_list(char** list)
{
	int i = 0;
	while (list[i] != NULL)
		printf("%s\n", list[i++]);
}
