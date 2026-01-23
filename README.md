### Overview
This repo contains the implementation of a Tiny C compiler quine that will inject a backdoor into a sample login program. I decided to implement our quine in tinycc (because we aren't insane). There are two versions of tinycc in this repository, ```tinyccBUGGED``` which contains the source code for the quine, and the development steps required to get to that point, and ```tinycc``` which is the original untampered source code.

The actual changes all take place in 

```ST_FUNC int tcc_add_file_internal(TCCState *s1, const char *filename, int flags)```

in libtcc.c. This function is the step before compiling and allows proceeding to the compilation and allows passing the source code as a string buffer instead of a file. To inject the backdoor, the entire source file is read into a buffer, the backdoor is inserted into it, and the buffer is paed to the compilation function.

The backdoor username is ```backdoor```


### Development Process
- The development process can be followed by viewing each ```tinyccBUGGED/libtcc-step*.c``` which are ordered by the time of their development. 

1. Initial backdoor proof of concept - Ensure that we can inject the login backdoor into a binary. Also tests the 'trigger' mechanism.

2. Now we inject the backdoor which is the login backdoor to implant the backdoor - now we have depth 2.

3. Finally, inject a backdoor that can inject itsself.

### Running Instructions
- This assums that you have a clean tinycc/ and a tinyccBUGGED/ in the root of this repo.

1. CD into tinyccBUGGED:
```
cd tinyccBUGGED
```
2. Compile the infected binary to make compiler A:
```
/configure && make clean && make```
```
3. Move A into the clean source and follow it:
```
mv ./tcc ../tinycc/tccBUGGED && cd ../tinycc
```
4. Compile the clean source with A to get compiler B:
```
./configure && make clean && make CC=./tccBUGGED
cd ..
```
5. Now we compile login.c with compiler B:
```
./tinycc/tcc login.c -o login
```
6. Run the new binary with the backdoor login:
```
./login.out backdoor
```
7. Check the exit code of the binary ( should be 0 ):
```
echo $?
```

Note that for step 2 you could also use a clean tinycc to compile compiler A
