/* 
;==========================================
; Autor: Duarte André Teresa Guerreiro 
; Número: 2016231778
; Autor: Francisco Miguel Almeida Monteiro
; Número: 2016241480
;==========================================
*/

alfam [a-zA-Z_0-9]
espaco " "
%%
package	{printf("PACKAGE\n");} 
{alfam}* {printf("id(%s)",&yytext[0]);}
{espaco} ;

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

