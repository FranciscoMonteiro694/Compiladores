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
	int numcolunas=0;
%}
%X COMENTARIO STRLITT



alfa [a-zA-Z_]
numero [0-9]
espaco " "
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

decimal_digit [0-9]
decimals {decimal_digit}+
exponent  ((e|E)("+"|"-")?{decimals})
REALLIT ("."{decimals}{exponent}?)|({decimals}"."{decimals}?{exponent}?)|({decimals}{exponent})
decimal_lit [1-9]{decimal_digit}*
octal_digit [0-7]
octal_lit 0{octal_digit}*
hex_digit (([0-9]|[A-F])|([a-f]))
hex_lit 0(x|X){hex_digit}+
INTLIT (({decimal_lit}|{octal_lit})|{hex_lit})

%%
{SEMICOLON} {printf("SEMICOLON\n");}
{BLANKID} {printf("BLANKID\n");}
{RETURN} {printf("RETURN\n");}
{AND} {printf("AND\n");}
{ASSIGN} {printf("ASSIGN\n");}
{STAR} {printf("STAR\n");}
{COMMA} {printf("COMMA\n");}
{DIV} {printf("DIV\n");}
{EQ} {printf("EQ\n");}
{GE} {printf("GE\n");}
{GT} {printf("GT\n");}
{LBRACE} {printf("LBRACE\n");}
{LE} {printf("LE\n");}
{LPAR} {printf("LPAR\n");}
{LSQ} {printf("LSQ\n");}
{LT} {printf("LT\n");}
{MINUS} {printf("MINUS\n");}
{MOD} {printf("MOD\n");}
{NE} {printf("NE\n");}
{NOT} {printf("NOT\n");}
{OR} {printf("OR\n");}
{PLUS} {printf("PLUS\n");}
{RBRACE} {printf("RBRACE\n");}
{RSQ} {printf("RSQ\n");}
{RPAR} {printf("RPAR\n");}
{ELSE} {printf("ELSE\n");}
{FOR} {printf("FOR\n");}
{IF} {printf("IF\n");}
{VAR} {printf("VAR\n");}
{INT} {printf("INT\n");}
{FLOAT32} {printf("FLOAT32\n");}
{BOOL} {printf("BOOL\n");}
{STRING} {printf("STRING\n");}
{PRINT} {printf("PRINT\n");}
{PARSEINT} {printf("PARSEINT\n");}
{FUNC} {printf("FUNC\n");}
{CMDARGS} {printf("CMDARGS\n");}
{PACKAGE} {printf("PACKAGE\n");} 
{alfa}+({numero}|{alfa})* {printf("ID(%s)\n",&yytext[0]);}
{REALLIT} {printf("REALLIT(%s)\n",yytext);}
{INTLIT} {printf("INTLIT(%s)\n",yytext);}
"\n" ;

{espaco}+ ;
"/*" {BEGIN COMENTARIO;}
<COMENTARIO>.	;
<COMENTARIO>"\n" ;
<COMENTARIO>"*/" {BEGIN 0;}
"//".*"\n" ;

"\"" {BEGIN STRLITT;}
<STRLITT>[^"]*|"\n" {printf("STRLIT(\"%s\")\n",&yytext[0]);}
<STRLITT>"\"" {BEGIN 0;}

. {printf("Line <%d>, colummn <num coluna>: illegal character (%s)\n",yylineno,&yytext[0]);}




%%
int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}

