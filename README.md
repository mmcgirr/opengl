# OpenGL - educational repo

## Starting Folder Structure

```pre
opengl
 \_ext
 | \_ glfw (submodule)
 | |_ ... (other submodules)
 |
 |_00_glfw
 |  \_ build_c.sh
 |  |_ main.c
 |  |_ readme.md
 |
 |_Other nn_foo folders
 |
 |_ .git
 |_ .gitmodules
 |_ .gitignore
 |_ README.md
```

Each project is self-contained.
Each project should have a build_c.sh and a build_cpp.sh file

The general initial workflow is:

- Get glfw squared away
  - Compile a simple test program [See here](./00_glfw/readme.md)

- Get glad squared away
  - Compile another test program [See here](./01_glad/readme.md)

- Get a glfw window up
  - Compile test program [See here](./02_glfw-window/readme.md)


