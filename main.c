#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
enum tokens
{
TYPE = 1,
NAME,
VALUE,  
LBRACE, 
RBRACE,
LCBRACE,
RCBRACE,
DACOMMA,
COMMA,
EMPTY,
INT,
VOID,
EMPT
};
/*
typedef struct{
	char* buff;
	Node** nodes;
	int Ccounter;
}Node;
*/
//void test(int x){print(x);print(2);}test(3);$
	
tokens symbol;
char litera = 0;
char* lexema = NULL;
int func();
void p1();
void p2();
int p3();
int type();
char** output = NULL;
char** flaggedoutput = NULL;
int outcount = 0; //Сумма вызывающих функций
int execcount = 0; //Вызываемых функций
int printcount = 0;
void semanticp3();
FILE * mf;
int flag = 0;
tokens scan() 
{
	
   while(1)
   {
	   
	   litera = fgetc(mf);
	   int count = 1;
	   
	   if (litera== ' ' || litera == '\t' || litera == '\n' || litera == '\r') ;
	   else if (litera == EOF) return EMPT;
	   else if (litera == '(') return LBRACE;
	   else if (litera == ')') return RBRACE;
       else if (litera == '{') return LCBRACE;
	   else if (litera == '}') return RCBRACE;
       else if (litera == ';') return DACOMMA;
	   else if (litera == ',') return COMMA;
	   else
	   {
		   //++counter
		   //лексема пуста
			lexema = (char*) calloc(++count, sizeof(char));
			lexema = strncat(lexema, &litera, 1*sizeof(char));
		   //int a = strlen(lexema);
			litera = fgetc(mf);
		   while(isalnum(litera))
		   {
				lexema = (char*) realloc(lexema, (++count) * sizeof(char));
				strncat(lexema, &litera, 1*sizeof(char));
			//Записать в лексему следующий символ(литера)
			//при помощи memcpy
		       litera = fgetc(mf);
		   }
			ungetc(litera, mf);
		    if(strcmp(lexema,"void") == 0)
			{
				return VOID;
			}
			else if(strcmp(lexema,"int") == 0)
			{
				return INT;
			}
			else if(!isdigit(lexema[0]))
			{
				return NAME;
			}
			else
			{
				if(atoi(lexema) != 0 || strlen(lexema) <= 1)
				{
					return VALUE;
				}
				else
				{
					
					return EMPTY;
				}
			}
	   }
	   
   }

}

int main()
{
	mf = fopen("stream.txt","r");
	if(mf == NULL)
	{
		printf("Error reading file is unsuccsessful");
		return -1;
	}
	symbol = scan();
	func(); 
	if (symbol != EMPT)
		perror("Still some input exists\n");
	else
	{
		if (feof(mf) != 0)
		{
			/*printf("success\n");
			if(printcount != outcount-1)//попр
			{
				printf("Printcount is not equal to outcount");
				return -1;
			}
			*/
			for(int j = 0;j < execcount-1;j++)
			{
				for(int i = 0;i < outcount-1;i++)
				{
					if(atoi(output[i]) != 0) 
					{
						printf("%с\n", output[i]);
					}
				else
					{
						printf("%s\n", (flaggedoutput[j]));
					}
				}
			}
			
		}
		else
		{
			 printf ("\nОшибка чтения из файла\n");
		}
		
	}
}
//1|<func>::=<type>name(<type>name<p_1>){<p_2>}<p_2>
//Node AST;

int func() 
{
	if(type())
	{
		symbol = scan();
		if(symbol == NAME)
		{//test
			/*
			AST.buff = (char*)calloc(strlen(lexema)+1,sizeof(char));
			AST.buff = strcpy(AST.buff,lexema);
			AST.Ccounter = 0;
			AST.nodes = NULL;*/
			//char* buffer = (char*)calloc(strlen(lexema)+1,sizeof(char));
			//strcpy(buffer,lexema);
			symbol = scan();
			if(symbol == LBRACE)
			{
				symbol = scan();
				if(type())
				{
					symbol = scan();
					if(symbol == NAME)
					{
						symbol = scan();
						p1();
						if(symbol == RBRACE)
						{
							symbol = scan();
							if(symbol == LCBRACE)
							{
								symbol = scan();
								p2();
								if(symbol == RCBRACE)
								{
									flag = 1;
									symbol = scan();
									/*if(strcmp(lexema,buffer) == 0)
									{
										
									}
									else
									{
										perror("Wrong call of function");
									}*/
									//test
									/*if(strcmp(lexema,buffer) == 0)
										++testcount;*/
									p2();
								}
								else
								{
									perror("Error:func - symbol is not RCBRACE");
								}
							}
							else
							{
								perror("Error:func - symbol is not LCBRACE");
							}
						}
						else
						{
							perror("Error:func - symbol is not RBRACE");
						}
					}
					else
					{
						perror("Error:func - symbol is not NAME");
					}
				}
				else
				{
					perror("Error:func - symbol is not TYPE");
				}
			}
			else
			{
				perror("Error:func - symbol is not LBRACE");
			}
		}
		else
		{
			perror("Error:func - symbol is not NAME");
		}
	}
	else
	{
		perror("Error:func - symbol is not TYPE");
	}
}
//2|<p_1>::= ,<type>name<p_1>|e
void p1()
{
	if(symbol == COMMA)
	{
		symbol = scan();
		if(type())
		{
			symbol = scan();
			if(symbol == NAME)
			{
				symbol = scan();
				p1();
			}
			else
			{
				perror("Error:p1 - symbol is not NAME");
			}
		}
		else
		{
			perror("Error:p1 - symbol is not TYPE");
		}
	}
}
//4|<p_2>::=name(<p_3>);<p_2>|e
void p2()
{
	if(symbol == NAME)
	{
		/*
		AST.buff = (char*)calloc(strlen(lexema)+1, sizeof(char));
		AST.buff = strcpy(AST.buff,lexema);
		AST.nodes = (Node**)calloc(++(AST.Ccounter), sizeof(Node*));
		*/
		//print
		
		if(strcmp(lexema,"print") == 0)
			++printcount;
		
		symbol = scan();
		if(symbol == LBRACE)
		{
			symbol = scan();
			
			if(p3())
			{
			
				if(symbol == RBRACE)
				{
					symbol = scan();
					if(symbol == DACOMMA)
					{
						symbol = scan();
						p2();
					}
					else
					{
						perror("Error:p2 - symbol is not DACOMMA");
					}
				}
				else
				{
					perror("Error:p2 - symbol is not RBRACE");
				}
			}
		}
		else
		{
			perror("Error:p2 - symbol is not LBRACE");
		}
	}
}
//<p_3>::= name|value
int p3()
{
	
	
	if(symbol == NAME)
	{
		semanticp3();
		//printf("%s\n",lexema);
		symbol = scan();
		return NAME;
	}
	else if(symbol == VALUE)
	{
		semanticp3();
		//printf("%d\n",atoi(lexema));
		symbol = scan();
		return VALUE;
	}
	else
	{
		perror("Error:p3 - symbol is not NAME and is not VALUE");
		return 0;
	}
}
//7|<type>::= int|void
int type()
{
	if(symbol == INT)
	{
		return symbol;
	}
	else if(symbol == VOID)
	{
		return symbol;
	}
	else
	{
		perror("Error:p3 - symbol is not NAME and is not VALUE");
		return 0;
	}

}
void semanticp3()
{
	if( (output == NULL) && (printcount>0) )
	{
	output = (char**) calloc(++outcount, sizeof(char*));
	output[outcount-1] = (char*) calloc(strlen(lexema)+1, sizeof(char));
	strncat(output[outcount-1], lexema,(strlen(lexema)+1)*sizeof(char));
	--printcount;
	//output = (char**) malloc((++outcount) * sizeof(char*));
	//memset(output, 0, (++outcount) * sizeof(char*));
	}
	else if( (flag == 0) && (printcount>0) )
	{
		output = (char**) realloc(output, (++outcount) * sizeof(char*));
		//lexema = (char*) realloc(lexema, (++count) * sizeof(char));
		output[outcount-1] = (char*) calloc(strlen(lexema)+1, sizeof(char));
		strncat(output[outcount-1], lexema,(strlen(lexema)+1)*sizeof(char));
		--printcount;
	}
	else if((flaggedoutput == NULL) && (flag == 1))
	{
		flaggedoutput = (char**)calloc(++execcount,sizeof(char*));
		flaggedoutput[execcount-1] = (char*)calloc(strlen(lexema)+1, sizeof(char));
		strncat(flaggedoutput[execcount-1], lexema,(strlen(lexema)+1)*sizeof(char));
	}
	else if(flag == 1)
	{
		flaggedoutput = (char**)realloc(flaggedoutput,(++execcount)*sizeof(char*));
		flaggedoutput[execcount-1] = (char*)calloc(strlen(lexema)+1, sizeof(char));
		strncat(flaggedoutput[execcount-1], lexema,(strlen(lexema)+1)*sizeof(char));
	}
	//strlen(lexema)+1 ~ count but count is must be global
}

//1|<func>::=<type>name(<type>name<p_1>){<p_2>}<p_2>
//2|<p_1>::= ,<type>name<p_1>
//3|<p_1>::= e
//4|<p_2>::=name(<p_3>);<p_2>
//5|<p_2>::= e
//6|<p_3>::= name|value
//7|<type>::= int|void
