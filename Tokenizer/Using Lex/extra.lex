
/*
* Copyright (c) 2012-13 Jobin Raju George <jobin.rv@gmail.com> 
*
* Licensed under the GNU General Public License Version 2
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* A copy of the GNU General Public License is available at
* <http://www.gnu.org/licenses/>.
*/
%{
#include <stdio.h>
%}

DIGIT [0-9]
NUMBER {DIGIT}+
REAL {DIGIT}*"."{DIGIT}+
TEXT [a-zA-Z ]+
TEXT_NUMBERS [a-zA-Z0-9]
CONDITIONALS "if"|"else"|"else if"|"switch"|"case"
KEYWORD "break"|"continue"|"goto"|"printf"|"scanf"|"sprintf"|"sscanf"|"fopen"|"fwrite"|"fread"|"fclose"|"write"|"read"|"open"|"close"|"return"|"int"|"float"|"char"|"unsigned"|"signed"|"short"|"long"|"double"
ITERATORS "for"|"while"|"do"
PREPROCESSOR "#"|"#line"|"#undef"|"#error"|"#elif"|"#else"|"#endif"|"#if"|"#define"|"#include"|"#pragma"|"#ifndef"|"#ifdef"
DELIMITER [; :\t\n()"]
IDENTIFIER [a-zA-Z]{TEXT_NUMBERS}*|[a-zA-Z]{TEXT_NUMBERS}*[[{NUMBER}+]]
NON_IDENTIFIER {NUMBER}+[A-Za-z]+
FORMAT_SPECIFIER "%"{TEXT_NUMBERS}+
FILE "<"{IDENTIFIER}.h">"
COMMENT "/*"[a-zA-Z0-9 \t\n;.~!@#$%^&*()_+=<>?:"{}]*"*/"
AOPERATOR "+"|"-"|"*"|"/"|"="
BLOCK_BEGINS "{"
BLOCK_ENDS "}"
UNARY "++"|"--"
LOPERATOR "&"|"|"|"&&"|"~"|"||"|">"|"<"|">="|"<="|"=="
FUNCTION {IDENTIFIER}+"("{DELIMITER}*{TEXT}{TEXT_NUMBERS}*{DELIMITER}*")"
%%
\n      					// Ignore
[ \t]+  					// Ignore
{CONDITIONALS} { printf("%s is a conditional\n", yytext); }
{ITERATORS} { printf("%s is an iterator\n", yytext); }
{DIGIT} { printf("%s is a digit\n", yytext); }
{NUMBER} { printf("%s is a number\n", yytext); }
{REAL} { printf("%s is a real number\n", yytext); }
{PREPROCESSOR} { printf("%s is a preprocessor directive\n", yytext); }
{DELIMITER} { printf("%s is a delimiter\n", yytext); }
{KEYWORD} { printf("%s is a keyword\n", yytext); }
{NON_IDENTIFIER} {printf("Could not process %s", yytext); }
{IDENTIFIER} { printf("%s is an identifier\n", yytext); }
{COMMENT} { printf("%s is a comment\n", yytext); }
{AOPERATOR} { printf("%s is a mathematical operator\n", yytext); }
{LOPERATOR} { printf("%s is a logical operator\n", yytext); }
{BLOCK_BEGINS} { printf("Block begins\n"); }
{BLOCK_ENDS} { printf("Block ends\n"); }
{FILE} { printf("%s is a file\n", yytext); }
{UNARY} { printf("%s is a unary operator\n", yytext); }
{FUNCTION} { printf("%s is a function\n", yytext); }
{FORMAT_SPECIFIER} {printf("%s is a format specifier\n", yytext); }
%%

int main(int argc, char *argv[]) {
yyin=fopen("helloworld.c","r");
yylex();
return 0;
}