# Creating a window

So, you want a window?  Alright then. We'll do that, and then a little more quality of life items as well.

## The basics of this program

To create a window, you can:

- Establish a couple of convenient defines  (Optional)
- Prototype for an glfw error 'handler', instead of calling fprintf(...) all the time from within a check. (Optional, but good to have)

- Register the error callback (glfwInit can fail, we want to catch this) (Optional, but good to have)

- Initialize glfw (mandatory)
- Set the minimum GL api version we require (e.g. 3.3) (Optional)
  - Your particular gpu driver may have a higher version available - all we're doing is telling the system what minimum version and profile we want)

- Create the window (mandatory)
  - Set the width, height, title (UTF-8), monitor for fullscreen mode (NULL for windowed), the 'other' window the created one should share it's objects with (NULL for none)

- Make the window the current OpenGL context (mandatory)
- Use glad to load OpenGL function pointers (optional, BUT if you don't do this, _you_ have to set up all the OpenGL function pointers manually)

- Enter the main loop
  - Basic: clear the framebuffer color, set the type of clear (color_buffer) (Optional)
  - Swap the back with the front buffer (Mandatory)
  - Poll for window events and such (Mandatory)

- Clean up after ourselves when the program exits
  - Things are allocating memory.  Now, while this is just a simple app, and the OS will collect all the garbage laying around when your app closes,
    it's just a good habit - in manual memory languages (like C) - to ensure you properly destory / deallocate / clean-up any memory you've allocated.

- Exit the program - if all went well, return 0.

## More on Contexts

A window object contains both the top-level window and an OpenGL or OpenGL ES context.

OpenGL is a state machine.  The window (and active context) is the way OpenGL knows what state should be active in the current thread.

glfwCreateWindow()  is what is responsible for creating this context.   The window handle is _also_ the context handle. 
As you can see, the window is of type GLFWWindow* 

The context is everything opengl needs to 'remember', like:
  - Current shader program
  - Bound buffers
  - Texture bindings
  - Render state
  - Active framebuffer
  - Capability limits
  - Error state(s)

It lives in the GPU driver.
Contexts are thread local.  
Only _one_ context can be current in the current thread.  
You can switch contexts, but you must deactivate the 'old' and activate the 'new'.

When you do something like:
```c
glClearColor(...);
glClear(GL_COLOR_BUFFER_BIT);
```
You are acting on the current OpenGL context and associated framebuffer.  The framebuffer is the thing that maps to the window surface.  
If you didn't do glfwMakeContextCurrent(window) - OpenGL wouldn't know what 'bag of state' to operate with, or on _what_ to operate.

**Simple thought**: the context is the *current rendering target*, and GLFW connects that target to a specific window's framebuffer.


