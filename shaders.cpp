#include <stdio.h>
#include <assert.h>
#include "shaders.h"
#include <glad/glad.h>


int ReadShader(const char* name, char* shader_text)
{
    assert(name);
    assert(shader_text);

    char file_name[100] = {};
    snprintf(file_name, sizeof(file_name), "%s%s", "Shaders/", name);
    FILE* file = fopen(file_name,"r");

    if (file == NULL)
    {
        printf("Couldnt find shader %s", name);
        return -1;
    }

    char ch = 0;
    int ind = 0;

    while ((ch = fgetc(file)) != EOF && ind < 9999)
    {
        shader_text[ind] = ch;
        ind += 1;
    }
    shader_text[ind] = 0;

    fclose(file);

    return 0;
}

unsigned int CompileShader(const char* shader_text, int shader_type)
{
    assert(shader_text);

    unsigned int Shader;   //GL_..._SHADER
    Shader = glCreateShader(shader_type);

    glShaderSource(Shader, 1, &shader_text, NULL);
    glCompileShader(Shader);

    int success;
    char infoLog[512];

    //Get shader compilation errors
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);
        printf("Failed to compile shader\n%s\n", infoLog);
    }

    return Shader;
}

unsigned int GetShader(const char* shader_name, int shader_type)
{
    char shader_text[10000] = {};
    if (ReadShader(shader_name, shader_text) != 0)
    {
        return 0;
    }

    unsigned int shdr = 0;
    printf("Starting to compile shader -- %s\n", shader_name);
    shdr = CompileShader(shader_text, shader_type);

    return shdr;
}
