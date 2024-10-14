# OpenGL Triangle on MacOS

This is a modified sample project from [Aleksander Denisiuk's Computer Graphics course](http://users.pja.edu.pl/~denisjuk/gk) ([original source code](http://users.pja.edu.pl/~denisjuk/gk/wyklady/g10-podstawyOpenGL.zip)).

The original project has a Makefile setup for Windows with MinGW and Linux, but not for MacOS.

Developing OpenGL applications on modern MacOS versions is a bit tricky because it's an API deprecated in favor of a newer one called Metal. OpenGL runs as a compatibility layer on top of Metal and it's limited to version 4.1.

## Prerequisites

Install Xcode (from the App Store) and setup the default toolchain:
```sh
xcode-select --install
```
If Xcode and its toolchain were correctly installed, several frameworks for working with OpenGL should now be available.

Install glfw3, glew and make:
```sh
brew install glfw3 glew make
```

Additional dependencies - not needed for this example, but will be required for other courses:
```sh
brew install jpeg libpng argtable
```

## Build & Run

```sh
make run
```

You'll see `glDebugMessageCallback not available` in the console. It's an API introduced in OpenGL 4.3 and we're using OpenGL 4.1.

You should also see `OpenGL initialized: OpenGL version: 4.1 Metal - xx.x GLSL version: 4.10` in the console.

## Troubleshooting

If for some reason glfw from homebrew doesn't work, try compiling it from source:
```sh
brew uninstall glfw

git clone https://github.com/glfw/glfw.git && \
cd glfw && \
cmake -DCMAKE_OSX_ARCHITECTURES=arm64 . && \
make && \
sudo make install
```

## Resources

- https://carette.xyz/posts/opengl_and_cpp_on_m1_mac/
- https://github.com/k0pernicus/opengl-explorer/tree/0e311828fb34b272809432254307e8561e951335
- https://www.glfw.org/docs/latest/build_guide.html#build_link_pkgconfig
