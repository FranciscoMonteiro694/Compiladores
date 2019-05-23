/* 
;==========================================
; Autor: Duarte André Teresa Guerreiro 
; Número: 2016231778
; Autor: Francisco Miguel Almeida Monteiro
; Número: 2016241480 

Line <num linha>, colummn <num coluna>: unterminated comment\n
Line <num linha>, colummn <num coluna>: illegal character (<c>)\n
Line <num linha>, colummn <num coluna>: unterminated string literal\n
Line <num linha>, colummn <num coluna>: invalid escape sequence (<c>)\n
onde num linha e num coluna devem ser substituidos pelos valores correspondentes ao inicio do token que originou o erro
e <c> devem ser substituidos por esse token.
O analisador deve recuperar da ocorrência de erros lexicias a partir do fim desse token.
Tanto as linhas como as colunas são numeradas a partir de 1
;==========================================
*/
%{
#include "y.tab.h"
#include "tabelas.h"
	extern int flagLex;
%}
%{
	int numcolunas=1;
	int flag_semicolon=0;
	int flag_javarda=0;
	int aux_erroc=-1;
	int aux_errol=-1;
	char s[500];
	int tamanho=0;
	int flag_do_mal=0;
	int mais_uma=0;
	int flagString=0;

%}
%X COMENTARIO STRLITT STRLITT2 COMENTARIO_2

%option yylineno

alfa [a-zA-Z_]
numero [0-9]
espaco (" "|"\t")
SEMICOLON ";"
BLANKID "_"
PACKAGE package
RETURN return
AND "&&"
ASSIGN "="
STAR "*"
COMMA ","
DIV "/"
EQ "=="
GE ">="
GT ">"
LBRACE "{"
LE "<="
LPAR "("
LSQ "["
LT "<"
MINUS "-"
MOD "%"
NE "!="
NOT "!"
OR "||"
PLUS "+"
RBRACE "}"
RPAR ")"
RSQ "]"
ELSE else
FOR for
IF if
VAR var
INT int
FLOAT32 float32
BOOL bool
STRING string
PRINT fmt.Println
PARSEINT strconv.Atoi
FUNC func
CMDARGS os.Args
RESERVED ("default"|"break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--")
ENTER "\n"

decimal_digit [0-9]
decimals {decimal_digit}+
exponent  ((e|E)("+"|"-")?{decimals})
REALLIT ("."{decimals}{exponent}?)|({decimals}"."{decimals}?{exponent}?)|({decimals}{exponent})
decimal_lit [0-9]{decimal_digit}*
octal_digit [0-7]
octal_lit 0{octal_digit}+
hex_digit (([0-9]|[A-F])|([a-f]))
hex_lit 0(x|X){hex_digit}+
INTLIT (({decimal_lit}|{octal_lit})|{hex_lit}|0)
teste "\\"("a"|"b"|"f"|"n"|"r"|"t"|"v"|"\\"|"\"")
aux {INTLIT}$

%%
{RESERVED} {if (flagLex==1){printf("RESERVED(%s)\n",yytext);}numcolunas+=yyleng;flag_semicolon=0;return RESERVED;}
{ENTER} {flagString=0;numcolunas=1;if(flag_semicolon==1){if (flagLex==1){printf("SEMICOLON\n");}flag_semicolon=0;return SEMICOLON;}}
{espaco}+ {numcolunas+=yyleng;};
{SEMICOLON} {if (flagLex==1){printf("SEMICOLON\n");}numcolunas+=yyleng;flag_semicolon=0;return SEMICOLON;}
{BLANKID} {if (flagLex==1){printf("BLANKID\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return BLANKID;}
{RETURN} {if (flagLex==1){printf("RETURN\n");}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return RETURN;}
{AND} {if (flagLex==1){printf("AND\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return AND;}
{ASSIGN} {if (flagLex==1){printf("ASSIGN\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return ASSIGN;}
{STAR} {if (flagLex==1){printf("STAR\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return STAR;}
{COMMA} {if (flagLex==1){printf("COMMA\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return COMMA;}
{DIV} {if (flagLex==1){printf("DIV\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return DIV;}
{EQ} {if (flagLex==1){printf("EQ\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return EQ;}
{GE} {if (flagLex==1){printf("GE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return GE;}
{GT} {if (flagLex==1){printf("GT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return GT;}
{LBRACE} {if (flagLex==1){printf("LBRACE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return LBRACE;}
{LE} {if (flagLex==1){printf("LE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return LE;}
{LPAR} {if (flagLex==1){printf("LPAR\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return LPAR;}
{LSQ} {if (flagLex==1){printf("LSQ\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return LSQ;}
{LT} {if (flagLex==1){printf("LT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return LT;}
{MINUS} {if (flagLex==1){printf("MINUS\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return MINUS;}
{MOD} {if (flagLex==1){printf("MOD\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return MOD;}
{NE} {if (flagLex==1){printf("NE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return NE;}
{NOT} {if (flagLex==1){printf("NOT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return NOT;}
{OR} {if (flagLex==1){printf("OR\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return OR;}
{PLUS} {if (flagLex==1){printf("PLUS\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return PLUS;}
{RBRACE} {if (flagLex==1){printf("RBRACE\n");}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return RBRACE;}
{RSQ} {if (flagLex==1){printf("RSQ\n");}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return RSQ;}
{RPAR} {if (flagLex==1){printf("RPAR\n");}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return RPAR;}
{ELSE} {if (flagLex==1){printf("ELSE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return ELSE;}
{FOR} {if (flagLex==1){printf("FOR\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return FOR;}
{IF} {if (flagLex==1){printf("IF\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return IF;}
{VAR} {if (flagLex==1){printf("VAR\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return VAR;}
{INT} {if (flagLex==1){printf("INT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return INT;}
{FLOAT32} {if (flagLex==1){printf("FLOAT32\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return FLOAT32;}
{BOOL} {if (flagLex==1){printf("BOOL\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return BOOL;}
{STRING} {if (flagLex==1){printf("STRING\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return STRING;}
{PRINT} {if (flagLex==1){printf("PRINT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return PRINT;}
{PARSEINT} {if (flagLex==1){printf("PARSEINT\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return PARSEINT;}
{FUNC} {if (flagLex==1){printf("FUNC\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return FUNC;}
{CMDARGS} {if (flagLex==1){printf("CMDARGS\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return CMDARGS;}
{PACKAGE} {if (flagLex==1){printf("PACKAGE\n");}numcolunas+=yyleng;flag_semicolon=0;yylval.string =(char*)strdup(yytext);return PACKAGE;} 
{alfa}+({numero}|{alfa})* {if (flagLex==1){printf("ID(%s)\n",&yytext[0]);}yylval.p=criaAuxiliar((char*)strdup(yytext),numcolunas);numcolunas+=yyleng;flag_semicolon=1;return ID;}
{REALLIT} {if (flagLex==1){printf("REALLIT(%s)\n",yytext);}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return REALLIT;}
{INTLIT} {if (flagLex==1){printf("INTLIT(%s)\n",yytext);}numcolunas+=yyleng;flag_semicolon=1;yylval.string =(char*)strdup(yytext);return INTLIT;}



"/*" {aux_erroc=numcolunas;aux_errol=yylineno;numcolunas+=yyleng;BEGIN COMENTARIO;}
<COMENTARIO>"\n" {numcolunas=1;}
<COMENTARIO><<EOF>> {printf("Line %d, column %d: unterminated comment\n",aux_errol,aux_erroc);BEGIN 0;}
<COMENTARIO>"*/" {numcolunas+=yyleng;BEGIN 0;}
<COMENTARIO>.	{numcolunas+=yyleng;}


"//" {numcolunas+=yyleng;BEGIN COMENTARIO_2;}
<COMENTARIO_2>.	{numcolunas+=yyleng;};
<COMENTARIO_2>"\n" {numcolunas=1;if(flag_semicolon==1){if (flagLex==1){printf("SEMICOLON\n");}flag_semicolon=0;return SEMICOLON;}BEGIN 0;}

"\"" {aux_erroc=numcolunas;aux_errol=yylineno;numcolunas+=yyleng;BEGIN STRLITT;}
<STRLITT>"\\""\\" {s[tamanho]=yytext[0];tamanho++;s[tamanho]=yytext[1];tamanho++;numcolunas+=yyleng;}
<STRLITT>"\\""\"" {s[tamanho]=yytext[0];tamanho++;s[tamanho]=yytext[1];tamanho++;numcolunas+=yyleng;}
<STRLITT>"\\"(f|r|t|n) {s[tamanho]=yytext[0];tamanho++;s[tamanho]=yytext[1];tamanho++;numcolunas+=yyleng;}
<STRLITT>"\\". {printf("Line %d, column %d: invalid escape sequence (%s)\n",aux_errol,numcolunas,yytext);tamanho+=yyleng;numcolunas+=yyleng;flag_do_mal=1;}
<STRLITT>"\"" {if(flag_do_mal==0){s[tamanho]='\0';if (flagLex==1){printf("STRLIT(\"");printf("%s", s);printf("\")\n");}flag_semicolon=1;tamanho=0;flagString=1;BEGIN 0;yylval.string =(char*)strdup(s);numcolunas+=yyleng;return STRLIT;}tamanho=0;flag_do_mal=0;numcolunas+=yyleng;BEGIN 0;}
<STRLITT>"\\" {printf("Line %d, column %d: invalid escape sequence (%s)\n",aux_errol,numcolunas,yytext);tamanho+=yyleng;numcolunas+=yyleng;flag_do_mal=1;}
<STRLITT>. {s[tamanho]=*yytext;tamanho++;numcolunas+=yyleng;};
<STRLITT>"\n" {printf("Line %d, column %d: unterminated string literal\n",aux_errol,aux_erroc);tamanho=0;flag_do_mal=0;numcolunas=1;BEGIN 0;}
<STRLITT><<EOF>> {printf("Line %d, column %d: unterminated string literal\n",aux_errol,aux_erroc);tamanho=0;flag_do_mal=0;numcolunas=1;BEGIN 0;}


<<EOF>>	{if(flag_semicolon==1){if(flagLex==1){printf("SEMICOLON\n");}flag_semicolon=0;return SEMICOLON;}return 0;}




. {printf("Line %d, column %d: illegal character (%s)\n",yylineno,numcolunas,&yytext[0]);numcolunas+=yyleng;}



%%


int yywrap()
{
return 1;
}



