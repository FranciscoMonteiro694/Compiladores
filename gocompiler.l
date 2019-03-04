/* 
;==========================================
; Autor: Duarte André Teresa Guerreiro 
; Número: 2016231778
; Autor: Francisco Miguel Almeida Monteiro
; Número: 2016241480
;==========================================
*/

alfam [a-zA-Z_ 0-9]

%%
package	{printf("PACKAGE\n");} 
{alfam}* {printf("id(%s)",&yytext[1]);}

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

