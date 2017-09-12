/*
flex token.lex
gcc lex.yy.c -lfl
./a.out
*/


D				[0-9]
L				[a-zA-Z_]
H				[a-fA-F0-9]
E				[Ee][+-]?{D}+
FS				(f|F|l|L)
IS				(u|U|l|L)*
TEXT_NUMBERS 	[a-zA-Z0-9]
PREPROCESSOR 	"#"|"#line"|"#undef"|"#error"|"#elif"|"#else"|"#endif"|"#if"|"#define"|"#include"|"#pragma"|"#ifndef"|"#ifdef"
FORMAT_SPECIFIER "%"{TEXT_NUMBERS}+
FILE    	   	 <(.*)?.h>
KEY				("auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while")
ID          	[_A-Za-z][_a-zA-Z0-9]*

%%
\n      					// Ignore
[ \t]+  					// Ignore
{PREPROCESSOR}				printf("%s -> PreProcessor\n",yytext);		
{FORMAT_SPECIFIER}			printf("%s -> Format Specifier\n",yytext);		
{FILE}      				printf("%s -> Header File\n",yytext);
"/*"						{ printf ("\nCOMMENT START /*\n"); comment(); printf("\n%s\nCOMMNENT END\n",yytext); }
"//"						{ printf ("Single Line Comment\n//"); scomment(); printf("\nComment End\n"); }
{D}+{E}{FS}?				printf("%s -> CONSTANT\n",yytext);		
{D}*"."{D}+({E})?{FS}?		printf("%s -> CONSTANT\n",yytext);
{D}+"."{D}*({E})?{FS}?		printf("%s -> CONSTANT\n",yytext);
0{D}+{IS}?					printf("%s -> CONSTANT\n",yytext);
{D}+{IS}?					printf("%s -> CONSTANT\n",yytext);
L?\"(\\.|[^\\"])+\"			printf("%s -> STRING LITERAL\n",yytext);
{KEY}   					printf("%s -> Keyword\n",yytext);
{ID}        				printf("%s -> Identifier\n",yytext);
"..."						printf("%s -> ELLIPSIS\n",yytext);
">>="						printf("%s -> RIGHT_ASSIGN\n",yytext);
"<<="						printf("%s -> LEFT_ASSIGN\n",yytext);
"+="						printf("%s -> ADD_ASSIGN\n",yytext);
"-="						printf("%s -> SUB_ASSIGN\n",yytext);
"*="						printf("%s -> MUL_ASSIGN\n",yytext);
"/="						printf("%s -> DIV_ASSIGN\n",yytext);
"%="						printf("%s -> MOD_ASSIGN\n",yytext);
"&="						printf("%s -> AND_ASSIGN\n",yytext);
"^="						printf("%s -> XOR_ASSIGN\n",yytext);
"|="						printf("%s -> OR_ASSIGN\n",yytext);
">>"						printf("%s -> RIGHT_OP\n",yytext);
"<<"						printf("%s -> LEFT_OP\n",yytext);
"++"						printf("%s -> INC_OP\n",yytext);
"--"						printf("%s -> DEC_OP\n",yytext);
"->"						printf("%s -> PTR_OP\n",yytext);
"&&"						printf("%s -> AND_OP\n",yytext);
"||"						printf("%s -> OR_OP\n",yytext);
"<="						printf("%s -> LE_OP\n",yytext);
">="						printf("%s -> GE_OP\n",yytext);
"=="						printf("%s -> EQ_OP\n",yytext);
"!="						printf("%s -> NE_OP\n",yytext);
"="							printf("%s -> ASSIGNMENT OPERATOR\n",yytext);
"-"							printf("%s -> MINUS OPERATOR\n",yytext);
"+"							printf("%s -> PLUS OPERATOR\n",yytext);
"*"							printf("%s -> MULTIPLY OPERATOR\n",yytext);
"/"							printf("%s -> DIVIDE OPERATOR\n",yytext);
"%"							printf("%s -> MOD OPERATOR\n",yytext);
"<"							printf("%s -> LESS THAN OPERATOR\n",yytext);
">"							printf("%s -> GREATER THAN OPERATOR\n",yytext);
"^"							printf("%s -> POWER OPERATOR\n",yytext);
"|"							printf("%s -> OR OPERATOR\n",yytext);
"&"							printf("%s -> AND OPERATOR\n",yytext);
"!"							printf("%s -> NOT OPERATOR\n",yytext);
";"							printf("%s -> DELIMITER\n",yytext);
("{"|"<%")					printf("%s -> DELIMITER\n",yytext);
("}"|"%>")					printf("%s -> DELIMITER\n",yytext);
","							printf("%s -> DELIMITER\n",yytext);
":"							printf("%s -> DELIMITER\n",yytext);
"("							printf("%s -> DELIMITER\n",yytext);
")"							printf("%s -> DELIMITER\n",yytext);
("["|"<:")					printf("%s -> DELIMITER\n",yytext);
("]"|":>")					printf("%s -> DELIMITER\n",yytext);
"."							printf("%s -> DELIMITER\n",yytext);
"~"							printf("%s -> DELIMITER\n",yytext);
"?"							printf("%s -> DELIMITER\n",yytext);
%%					

void comment()
{
	char c, c1;

	loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}

void scomment()
{
	char c;
	loop:
	while ((c = input()) != '\n' && c != 0)
		putchar(c);

}

int main()
{
	yyin = fopen("helloworld.c","r");
	yylex();
	fclose(yyin);
	return 0;
}



