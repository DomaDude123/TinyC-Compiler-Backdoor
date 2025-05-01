
#define AFF_TYPE_BIN 1

int tcc_add_binary( int s1, int flags, int filename, int fd ){
   return 0;
}

int main(){
   int flags = 0;
   int s1 = 0;
   int filename = 0;
   int fd = 0;
   // Testing the trigger mechanism on a much smaller file */


    if (flags & AFF_TYPE_BIN)
        return tcc_add_binary(s1, flags, filename, fd);

   return 0;
}

