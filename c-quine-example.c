
#include <stdio.h>
char*s="#include <stdio.h>%cchar*s=%c%s%c;%cint main(void){printf(s,10,34,s,34,10,10);}%c";
int main(void){printf(s,10,34,s,34,10,10);}



/*
*
*
* trigger code
* char *payload = trigger + %cchar *payload = %c%s%c + code_backdoor %c"
* backdoor code
*
*
*
*
*
*
*/



