/* 
;==========================================
; Autor: Duarte André Teresa Guerreiro 
; Número: 2016231778
; Autor: Francisco Miguel Almeida Monteiro
; Número: 2016241480
;==========================================
*/
%X COMENTARIO STRLITT
espaco " "
alfam [a-zA-Z_0-9]
STRLIT \"{alfam}*\"
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
{alfam}* {printf("id(%s)\n",&yytext[0]);}
"\n" ;
{STRLIT} {printf("STRLIT\n");}
{espaco}+ ;
"/*" {BEGIN COMENTARIO;}
<COMENTARIO>.	;
<COMENTARIO>"\n" ;
<COMENTARIO>"*/" {BEGIN 0;}
"//".*"\n" ;
"\"" {BEGIN STRLITT;}
<STRLITT>. {printf("STRLIT\n");}
<STRLITT>"\n" {printf("STRLIT\n");}
<STRLITT>"\"" {BEGIN 0;}




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

