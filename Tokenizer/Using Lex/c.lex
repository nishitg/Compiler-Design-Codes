/*
flex file.lex
gcc lex.yy.c -lfl
./a.out
*/


D				[0-9]
E				[Ee][+-]?{D}+
L				[a-zA-Z_]
FS				(f|F|l|L)
CONSTANT		(({D})|({D}+{E}{FS}?)|({D}*"."{D}+({E})?{FS}?)|({D}+"."{D}*({E})?{FS}?))
STRING 			{L}?\"(\\.|[^\\"])*\"
FILE            #include[ \t]*<[a-zA-Z_0-9\/-]+\.h>
KEYWORD         ("auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"return"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while")
ID              [_A-Za-z][_a-zA-Z0-9]*
DELIM     	[\(|\)|;|\{|\}]
%%
\n      // Ignore
[ \t]+  // Ignore
{STRING} 	printf("%s -> String\n",yytext);
{FILE}          printf("%s -> Header File\n",yytext);
{KEYWORD}       printf("%s -> Keyword\n",yytext);
{ID}            printf("%s -> Identifier\n",yytext);
{CONSTANT} 	printf("%s -> CONSTANT\n",yytext);
{DELIM}    	printf("%s -> Delim\n",yytext);
%%

main()
{
	yyin = fopen("helloworld.c","r");
	yylex();
	fclose(yyin);
}



