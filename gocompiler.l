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
	int numcolunas=1;
	int flag_semicolon=0;
%}
%X COMENTARIO STRLITT COMENTARIO_2

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
RESERVED ("break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--")
ENTER "\n"

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
{ENTER} {if(flag_semicolon==1){printf("SEMICOLON\n");flag_semicolon=0;}numcolunas=1;}
{espaco}+ {numcolunas+=yyleng;};
{SEMICOLON} {printf("SEMICOLON\n");numcolunas+=yyleng;}
{BLANKID} {printf("BLANKID\n");numcolunas+=yyleng;}
{RETURN} {printf("RETURN\n");numcolunas+=yyleng;flag_semicolon=1;}
{AND} {printf("AND\n");numcolunas+=yyleng;}
{ASSIGN} {printf("ASSIGN\n");numcolunas+=yyleng;}
{STAR} {printf("STAR\n");numcolunas+=yyleng;}
{COMMA} {printf("COMMA\n");numcolunas+=yyleng;}
{DIV} {printf("DIV\n");numcolunas+=yyleng;}
{EQ} {printf("EQ\n");numcolunas+=yyleng;}
{GE} {printf("GE\n");numcolunas+=yyleng;}
{GT} {printf("GT\n");numcolunas+=yyleng;}
{LBRACE} {printf("LBRACE\n");numcolunas+=yyleng;}
{LE} {printf("LE\n");numcolunas+=yyleng;}
{LPAR} {printf("LPAR\n");numcolunas+=yyleng;}
{LSQ} {printf("LSQ\n");numcolunas+=yyleng;}
{LT} {printf("LT\n");numcolunas+=yyleng;}
{MINUS} {printf("MINUS\n");numcolunas+=yyleng;}
{MOD} {printf("MOD\n");numcolunas+=yyleng;}
{NE} {printf("NE\n");numcolunas+=yyleng;}
{NOT} {printf("NOT\n");numcolunas+=yyleng;}
{OR} {printf("OR\n");numcolunas+=yyleng;}
{PLUS} {printf("PLUS\n");numcolunas+=yyleng;}
{RBRACE} {printf("RBRACE\n");numcolunas+=yyleng;flag_semicolon=1;}
{RSQ} {printf("RSQ\n");numcolunas+=yyleng;flag_semicolon=1;}
{RPAR} {printf("RPAR\n");numcolunas+=yyleng;flag_semicolon=1;}
{ELSE} {printf("ELSE\n");numcolunas+=yyleng;}
{FOR} {printf("FOR\n");numcolunas+=yyleng;}
{IF} {printf("IF\n");numcolunas+=yyleng;}
{VAR} {printf("VAR\n");numcolunas+=yyleng;}
{INT} {printf("INT\n");numcolunas+=yyleng;}
{FLOAT32} {printf("FLOAT32\n");numcolunas+=yyleng;}
{BOOL} {printf("BOOL\n");numcolunas+=yyleng;}
{STRING} {printf("STRING\n");numcolunas+=yyleng;}
{PRINT} {printf("PRINT\n");numcolunas+=yyleng;}
{PARSEINT} {printf("PARSEINT\n");numcolunas+=yyleng;}
{FUNC} {printf("FUNC\n");numcolunas+=yyleng;}
{CMDARGS} {printf("CMDARGS\n");numcolunas+=yyleng;}
{PACKAGE} {printf("PACKAGE\n");numcolunas+=yyleng;} 
{alfa}+({numero}|{alfa})* {printf("ID(%s)\n",&yytext[0]);numcolunas+=yyleng;flag_semicolon=1;}
{REALLIT} {printf("REALLIT(%s)\n",yytext);numcolunas+=yyleng;flag_semicolon=1;}
{INTLIT} {printf("INTLIT(%s)\n",yytext);numcolunas+=yyleng;flag_semicolon=1;}



"/*" {BEGIN COMENTARIO;}
<COMENTARIO>.	;
<COMENTARIO>"\n" {numcolunas=1;}
<COMENTARIO><<EOF>> {printf("Line %d, colummn %d: unterminated comment\n",yylineno,numcolunas);BEGIN 0;}
<COMENTARIO>"*/" {BEGIN 0;}


"//" {BEGIN COMENTARIO_2;}
<COMENTARIO_2>.	;
<COMENTARIO_2>"\n" {numcolunas=1;if(flag_semicolon==1){printf("SEMICOLON\n");flag_semicolon=0;}BEGIN 0;}

"\"" {BEGIN STRLITT;}
<STRLITT>[^("|"\n")]* {printf("STRLIT(\"%s\")\n",&yytext[0]);numcolunas+=yyleng;flag_semicolon=1;}
<STRLITT>"\n" {printf("Line %d, colummn %d: unterminated string literal\n",yylineno-1,numcolunas);BEGIN 0;}
<STRLITT>"\"" {BEGIN 0;}

. {printf("Line %d, colummn %d: illegal character (%s)\n",yylineno,numcolunas,&yytext[0]);}



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

