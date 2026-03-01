#ifndef SHADERS_H
#define SHADERS_H

// load_shader: loads a shader of the given filepath
unsigned int load_shader(char const *filepath);

// link_shaders : Links shaders to create an OpenGL Program
unsigned int link_shaders(unsigned int count, ...);

#endif