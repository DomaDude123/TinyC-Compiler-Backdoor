
### Overview
This repository demonstrates a self-propagating compiler backdoor implemented in TinyCC. A backdoored compiler is able to:

1. Inject a hidden authentication backdoor into specific programs at compile time.
2. Reproduce itself when compiling a _clean_ copy of the compiler source, even when the source code contains no backdoor.

The result is a compiler that appears clean but continues to propagate malicious behavior.

This was in part inspired by Ken Thompson's Turing Award lecture on trust and the possibility of this attack.

---

### Prerequisites
- A system-installed, trusted C compiler (e.g. GCC or Clang)
- Linux environment

---

### Directory Structure

This repo contains two copies of the [Tiny C Compiler](https://github.com/TinyCC/tinycc), one which has been tampered with, and the other which is completely clean.

As of 01/24/2026, this was working with the current state of tcc. Feel free to clone the clean tcc source yourself.

---

### Step-by-Step Reproduction
#### 1. Build the backdoored compiler with a trusted system compiler
```
cd tinyccBUGGED 
./configure 
make clean && make
```

This produces a backdoored `tcc` binary.

---

#### 2. Move the backdoored compiler into the clean source tree
```
mv ./tcc ../tinycc/tccBUGGED 
cd ../tinycc
```

At this point:
- Source code is clean
- Compiler binary is malicious

---

#### 3. Compile the clean compiler using the backdoored compile
The clean source is compiled using clean runtime dependencies from when we just compiled the malicious compiler. Important to note that these dependencies are **completely clean**.

```
./configure
make clean
make tcc CC="./tccBUGGED -B../tinyccBUGGED -I../tinyccBUGGED"
```

This produces a new `tcc` binary that:
- Appears clean
- Still contains the compiler backdoor

---

#### 4. Demonstrate self-reproduction (quine behavior)
Replace the compiler with the newly built one and repeat the build, again using the completely clean runtime dependencies from building the bugged compiler:

```
mv ./tcc ./tccBUGGED
make clean
make tcc CC="./tccBUGGED -B../tinyccBUGGED -I../tinyccBUGGED"
```

Repeat this step as many times as desired.  
Each generation continues to reproduce the backdoor without any malicious source code present.

---

#### 5. Compile a benign login program
Compile a simple login program in the root of this repository using the infected compiler and **clean** runtime dependencies from the compilation of the bugged compiler eariler:

```
./tinycc/tcc login.c -BtinyccBUGGED -ItinyccBUGGED/include -o login
```

###### `login.c` (clean source)
```
#include <string.h>
#include <stdio.h>
static int do_login(const char *username){
	if (!strcmp(username, "root"))
		return 0;
	return 1; 
	}
int main(int argc, char *argv[]){
	if (argc != 2)
		return 1;
	if (!do_login(argv[1])) {
		printf("Login successful\n");
		return 0;
	}
	printf("Login failed\n");
	return 1; 
}
```

---

#### 6. Observe injected behavior
Despite the source code allowing **only `root`** as a valid login, the compiled program accepts an additional, backdoored credential:

```
$ ./login backdoor 
Login successful
```

---

### Result
- The login backdoor is **not present in the source code**
- The compiler injects malicious behavior at compile time
- The compiler reproduces its own backdoor when compiling clean source
- Manual source inspection is insufficient to establish trust

---

### How?
The only changes made to the clean source were in `libtcc.c` in the function
`ST_FUNC int tcc_add_file_internal(TCCState *s1, const char *filename, int flags)

To understand how this behavior is possible, take a look at this [Wikipedia article](https://en.wikipedia.org/wiki/Quine_(computing)) and the file `c-quine-example.c` in the root of this repository, which implements a short but famous quine in C.


