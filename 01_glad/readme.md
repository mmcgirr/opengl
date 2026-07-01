# Getting glad

Glad is a small library that loads OpenGL function pointers.  Most systems have only the oldest OpenGL header file, and GLFW is not responsible for loading these functions.

There are 2 ways to use glad: 1) a webservice, or 2) from the system command line (e.g. linux).  I prefer the system command line so that's what I'll use.

Functionally (for now, since we're not using OpenGL extensions yet), all you need to specify is:

- The language you want glad to generate for
- The specification (e.g. OpenGL)
- The api level of the specification (e.g. 3.3)
- The profile type (e.g. Compatibility or Core)
- Any extensions you want included (we'll skip this for now)

## Webservice glad

The web service is [here](https://glad.dav1d.de/) in case you want to try it

If you use the web service, you need to specify the items we mentioned above:

- Language (c/c++)
- Specification (OpenGL)
- API (gl 3.3)
- Profile (Core)
- Extensions (leave this empty for now)
- Check 'generate a loader'
- click 'Generate'

You will then be directed to a download.  Grab the .zip file, and put it in the 01_glad folder.  Then, follow the [A little restructure] section.

## Command line glad

For the command line:

- Make sure you've got the glad command on your system
  ```bash
  $ glad --version
  ```

  If you don't have it, use your package manager to find and install it.  In my case (cachyos):
  ```bash
  $ pacman -Ss glad      # returns a few items, extra/glad 2.0.8-3 being one of them.
  $ sudo pacman -S glad  # installs glad system wide
  ```

- Once you've got it installed, migrate to the 02_glad folder and execute the following (note, the repo has already done this for you.  If you're starting from scratch do this.)
  ```bash
  $ glad --out-path=build --api="gl:core=3.3" c
  ```

  This will:
    - Create a 'build' folder in the 02_glad directory 
    - Generate OpenGL, Core profile, v3.3 files for
    - The c language

## A litte restructure

We've got things in ext/, and now we've got this build/ folder with glad includes and a c source file.  Let's restructure things a bit.

We're going to create two folders: opengl/lib and opengl/inc for libraries and includes, respectively.
```bash
$ pwd
~/prj/opengl/01_glad
$ mkdir ../inc ../lib
```

This is the folder structure before the move
```pre
├── 00_glfw
│   ├── build_c.sh
│   ├── main.c
│   └── readme.md
├── 01_glad
│   ├── build
│   │   ├── include
│   │   │   ├── glad
│   │   │   │   └── gl.h
│   │   │   └── KHR
│   │   │       └── khrplatform.h
│   │   └── src
│   │       └── gl.c
│   ├── build_c.sh
│   ├── gl.c
│   ├── main.c
│   └── readme.md
├── inc
├── lib
└── README.md
```

Let's copy all the stuff in build/include into inc, and let's copy src/gl.c into the root directory of this folder (this will be in every folder from now on)
```bash
$ pwd
~/prj/opengl/01_glad
$ mv ./build/include/* ../inc/
$ mv ./build/src/gl.c ./
```

The overall folder structure should look like this now:
```pre
├── 00_glfw
│   ├── build_c.sh
│   ├── main.c
│   └── readme.md
├── 01_glad
│   ├── build
│   │   ├── include
│   │   └── src
│   ├── build_c.sh
│   ├── **gl.c**
│   ├── main.c
│   └── readme.md
├── ext
├── inc
│   ├── **glad**
│   │   └── gl.h
│   ├── GLFW
│   │   ├── glfw3.h
│   │   └── glfw3native.h
│   └── KHR
│       └── khrplatform.h
├── lib
│   └── libglfw3.a
└── README.md
```

We don't need the build folder anymore (you can generate it at any time later...)
```bash
$ pwd
~/prj/opengl/01_glad
$ rm -rf ./build
```

## A little more restructure

### GLFW lib and include copy

Now that we've got that squared away, let's:

- Move necessary glfw things into lib and inc, respectively
  - The static library we built in 00_glfw is in `ext/glfw/build/src/libglfw3.a`
  - The include files for glfw are in `ext/glfw/include/GLFW`
    ```bash 
    $ pwd
    ~/prj/opengl/01_glad
    $ cp ../ext/glfw/build/src/libglfw3.a ../lib
    $ cp -r ../ext/glfw/include/GLFW ../inc
    ```
  - So now:
    ```pre
    ├── 00_glfw
    │   ├── build_c.sh
    │   ├── main.c
    │   └── readme.md
    ├── 01_glad
    │   ├── build_c.sh
    │   ├── gl.c
    │   ├── main.c
    │   └── readme.md
    ├── ext
    ├── inc
    │   ├── glad
    │   │   └── gl.h
    │   ├── **GLFW**
    │   │   ├── glfw3.h
    │   │   └── glfw3native.h
    │   └── KHR
    │       └── khrplatform.h
    ├── **lib**
    │   └── libglfw3.a
    └── README.md
    ```

### Modify the build_c.sh script for the new paths

- Modify the build script for the new paths
```bash
#!/usr/bin/env bash
set -xe

gcc  main.c gl.c -o main -I../inc ../lib/libglfw3.a -lGL -lm
```

### Test program

- Create a little c program to test glad / glfw

```c
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int main() {
    
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    return 0;
}
```

- Compile the test program and run it

If all goes well, you should have output in the command line similar to:
```bash
/prj/opengl/01_glad
❯ ./build_c.sh
+ gcc main.c gl.c -o main -I../inc ../lib/libglfw3.a -lGL -lm

~/prj/opengl/01_glad
❯ ./main
OpenGL version: 4.6 (Compatibility Profile) Mesa 26.1.3-arch3.1
```

Congrats if you've got this far!
