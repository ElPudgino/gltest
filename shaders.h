#ifndef SHADERS_H
#define SHADERS_H

int ReadShader(const char* name, char* shader_text);

unsigned int CompileShader(const char* shader_text, int shader_type);

unsigned int GetShader(const char* shader_name, int shader_type);

#endif
