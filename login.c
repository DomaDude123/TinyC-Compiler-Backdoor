#include <string.h>


static int
do_login(const char *username)
{
if (!strcmp(username, "root"))
return 0;
return 1;
}
int
main(int argc, char *argv[])
{
if (argc != 2)
return 1;
return do_login(argv[1]);
}
