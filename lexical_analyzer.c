/*

Objective	: Implementing the lexical analyzer phase in a compiler by using C
Description	: The programming language that is tokenized by the program is C. The program itself is written in C.
			  Lexical analyzer is the phase of the compiler that allows a program to be tokenized and constructs a symbol table for
			  further use in the following phases of the compiler. The meaningful patterns that are recognized are called lexemes and t
			  they are stored in the symbol table as tokens.
			  
Input		: File containing a program written in C
Output		: List of lexemes from the input program
Author		: Afreen S
Date		: 1st March, 2014
Comments 	:
	Does not completely detect the lexemes
	Can be optimized further
	Construction of symbol table not done, but it recognizes the different all identifiers and keywords.
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX 10

char key[32][10]={"auto","break","case","char","const","continue","default","do","double","else","enum", "extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static", "struct","switch","typedef","union","unsigned","void","volatile", "while"};
char id[50][20];
char str[MAX];

FILE *fp;


void append(char s[], char c, int pos)
{
	s[pos]=c;
	s[pos+1]='\0';
	
}
	
void isKey(char word[])
{
	int i,flagK=0,flagR=0,n=0;
	int len=0;
	while(word[len]!='\0')
	{
		len++;
	}
	for(i=0;i<32;i++)
	{
		if(strcmp(key[i],word)==0)
		{
			printf("%s\t\tKeyword\n",word);
			flagK=1;
			return;
		}
	}
	
	if(!flagK)
	{
			printf("%s\t\tIdentifier\n",word);
			//strcpy(id[n],word);
			//append(id[n],'\0',len+1);
			//n++;
	}
	
		
	return;
}

void isRelop(char rop[])
{
	printf("%s\t\tRelational operator\n",rop);
	return;
}

void isOp(char op)
{
	printf("%c\t\tArithmetic operator\n",op);
	return;
}

void isPar(char p)
{
	printf("%c\t\tParentheses\n",p);
	return;
}

void isUndef(char u)
{
	return;
}
	
void check()
{
	char ch;
	int i,cur=0;
	ch=str[cur];
	while(ch!='\0')
	{
		char token[100];
		i=0;
		if(isalpha(ch)||ch=='_')
		{
			while(isalpha(ch)||isdigit(ch)||ch=='_')
			{
				append(token,ch,i);
				i++;
				cur++;
				ch=str[cur];
			}
			append(token,'\0',i);
			isKey(token);
		}
		else if(ispunct(ch))
		{
			if(ch=='<'||ch=='>'||ch=='=')
			{
				append(token,ch,i);
				i++;
				cur++; 
				ch=str[cur];
				if(ch=='=')
				{
					append(token,ch,i);
					i++;
					cur++;
					ch=str[cur];
					isRelop(token);
				}
				else
					isRelop(token);
			}
			else if(ch=='!')
			{
				append(token,ch,i);
				i++;
				cur++;
				ch=str[cur];
				if(ch=='=')
				{
					append(token,ch,i);
					i++;;
					cur++;
					ch=str[cur];
					isRelop(token);
				}
				else
					continue;
			}
			else if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']')
			{
				isPar(ch);
				cur++;
				ch=str[cur];
			}
			else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='%'||ch=='^')
			{
				isOp(ch);
				cur++;
				ch=str[cur];
				
			}
			else if(ch=='"')
			{
				while(ch!='"')
				{
					cur++;
					ch=str[cur];
				}
			}
			else if(ch==','||ch==';')
			{
				cur++;
				ch=str[cur];
			}
		}
		else if(strncmp(&ch," ",1)==0||ch=='\t'||ch=='\n')
		{
			while(strncmp(&ch," ",1)==0||ch=='\t'||ch=='\n')
			{
				cur++;
				ch=str[cur];
			}
		}
		else if(isdigit(ch))
		{
			append(token,ch,i);
			i++;
			cur++;
			ch=str[cur];
			while(isdigit(ch))
			{
				append(token,ch,i);
				i++;
				cur++;
				ch=str[cur];
			}
			printf("%s\t\tNumeric constant\n",token);
			if(ch=='.')
			{
				append(token,ch,i);
				i++;
				cur++;
				ch=str[cur];
				while(isdigit(ch))
				{
					append(token,ch,i);
					i++;
					cur++;
					ch=str[cur];
				}
				printf("%s\t\tNumeric constant\n",token);
			}
		}
		else
		{
			isUndef(ch);
			cur++;
			ch=str[cur];
		}
	}
			
}				
		
			
			
int main(int argc, char** argv)
{
	int len,i=0;
	fp=fopen(argv[1],"r");
	while(!feof(fp))
	{
		while(fscanf(fp,"%s",str) ==1)
		{
			check();
		}
	}
	fclose(fp);
	return 0;
}
					
					
					
					
		

