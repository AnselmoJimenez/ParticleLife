#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "glad/glad.h"

#include "../include/shaders.h"

#define INFOLOGSIZE 512


// shader_compilation : Checks for a successful compilation
static int shader_compilation(unsigned int shader, char const *filepath) {
    int success;
    char info_log[INFOLOGSIZE];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    // check for success
    if (!success) {
        glGetShaderInfoLog(shader, INFOLOGSIZE, NULL, info_log);
        printf("%s compilation FAILURE:\n\t%s", filepath, info_log);
        return 0;
    }

    printf("%s compilation SUCCESSFUL\n", filepath);
    return 1;
}

// create_shader : Creates a shader of the given filepath type
static unsigned int create_shader(char const *filepath) {
    unsigned int shader;
    if (strstr(filepath, ".vert"))      shader = glCreateShader(GL_VERTEX_SHADER);
    else if (strstr(filepath, ".geom")) shader = glCreateShader(GL_GEOMETRY_SHADER);
    else if (strstr(filepath, ".frag")) shader = glCreateShader(GL_FRAGMENT_SHADER);
    else if (strstr(filepath, ".comp")) shader = glCreateShader(GL_COMPUTE_SHADER);
    else {
        printf("Unknown shader file type %s\n");
        return 0;
    }

    return shader;
}

// read_contents : reads a shader's contents
static char *read_contents(FILE *fp) {
    fseek(fp, 0, SEEK_END);     // move to end of file
    long int fsize = ftell(fp); // Get position
    fseek(fp, 0, SEEK_SET);     // Move to beginning of file
    
    char *contents = (char) malloc((fsize + 1) * sizeof(char));
    if (contents == NULL) 
        return NULL;
    fread(contents, sizeof(char), fsize, fp);
    contents[fsize] = '\0';
    
    return contents;
}

// load_shader: loads a shader of the given filepath
unsigned int load_shader(char const *filepath) {
    FILE *fp;
    if ((fp = fopen(filepath, "r")) == NULL) {
        printf("Unable to open %s", filepath);
        return 0;
    }

    printf("Compiling Shader: %s\n");
    char const *shader_contents = (char const *) read_contents(fp);
    if (shader_contents == NULL) return 0;
    fclose(fp);

    unsigned int shader;
    if ((shader = create_shader(filepath)) == 0) return 0;

    // compile and check compilation status
    glShaderSource(shader, 1, &shader_contents, NULL);
    glCompileShader(shader);
    free(shader_contents);
    if (!shader_compilation(shader, filepath))
        return 0;

    return shader;
}

static int linking_state(unsigned int program) {
    int success;
    char info_log[INFOLOGSIZE];
    glGetShaderiv(program, GL_LINK_STATUS, &success);

    // check for success
    if (!success) {
        glGetProgramInfoLog(program, INFOLOGSIZE, NULL, info_log);
        printf("Shader Linking FAILURE:\n\t%s", info_log);
        return 0;
    }

    printf("Shader linking SUCCESSFUL\n");
    return 1;
}

// link_shaders : Links shaders to create an OpenGL Program
unsigned int link_shaders(unsigned int count, ...) {
    va_list args;
    va_start(args, count);

    unsigned int program = glCreateProgram();

    // Attach and delete shader
    for (int i = 0; i < count; i++) {
        unsigned int shader = va_arg(args, unsigned int);
        glAttachShader(program, shader);
        glDeleteShader(shader);
    }
    va_end(args);

    glLinkProgram(program);
    if (!linking_state(program))
        return 0;
    
    return program;
}