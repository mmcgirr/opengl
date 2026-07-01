# Getting glfw set up

First things first - let's get glfw setup and operational.

We'll be compiling it from source, and then including it into our projects

## Requirements

You'll need cmake on your system - doesn't really matter what version for the purposes of this exercise.

You may need development libraries that support glfw - see the glfw docs: [glfw_docs](https://www.glfw.org/docs/latest/compile_guide.html)

However, most of this should be pretty self-contained

## GLFW - from source

- Add glfw source tree as submodule

  ```bash
  $ cd oopengl  # this is the project root directory
  $ mkdir ext
  $ git submodule add https://github.com/glfw/glfw
  ```
- Compile glfw (static lib)

```bash
$ cd ext/glfw
$ cmake -S . -B build
$ cd build
$ make
```

## Compile a test app

Let's create a little test app and build script now that we've got glfw compiled. 

It's a simple hello world that includes glfw.

We need to link against system-provided gl and math libraries (-lGL and -lm in the build script)

- The test file
```pre
       │ File: main.c
───────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
   1   │ #include <GLFW/glfw3.h>
   2   │
   3   │ #include <stdio.h>
   4   │
   5   │ int main() {
   6 ~ │
   7 ~ │     glfwInit();
   8 ~ │
   9   │     printf("Hello opengl\n");
  10   │     return 0;
  11   │ }
```

- The build script
```pre
       │ File: build_c.sh
───────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
   1   │ #!/usr/bin/env bash
   2   │
   3   │ set -xe
   4   │
   5 ~ │ gcc -I../ext/glfw/include -o main main.c  ../ext/glfw/build/src/libglfw3.a -lGL -lm
```

- Change build script to executable, compile main.c

```bash
$ chmod u+x build_c.sh
$ ./build.sh && ./main
```

If all goes well, you should see hello world.  Move on to the next test [02_glad](../02_glad/readme.md)
