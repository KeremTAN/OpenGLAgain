#include "shaderprogram.hpp"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(){
    m_ProgramId = glCreateProgram();
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(m_ProgramId);
}

void ShaderProgram::link(){
    glLinkProgram(m_ProgramId);
    // Check the COMPILE proccessing of SHADER
    int isLinked;
    char log[512];
    glGetShaderiv(m_ProgramId, GL_COMPILE_STATUS, &isLinked);
    if(!isLinked){
        glGetProgramInfoLog(m_ProgramId,512,0,log);
        std::cout<<"ERROR -> Program Linking:"<<std::endl<<log<<std::endl;
    }
}
void ShaderProgram::use(){
    glUseProgram(m_ProgramId);
}

void ShaderProgram::attachShader(const char* fileName, unsigned int shaderType){
    unsigned int shaderId = glCreateShader(shaderType);
    std::string sourceCode = getShaderFromFile(fileName);
    const char* souceCodePtr = &sourceCode[0];
    glShaderSource(shaderId, 1, &souceCodePtr,0);
    glCompileShader(shaderId);
    // Check the COMPILE proccessing of SHADER
    int isCompiled;
    char log[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled){
        glGetShaderInfoLog(shaderId,512,0,log);
        std::cout<<"ERROR -> Shader Type: "<<shaderType<<std::endl<<log<<std::endl;
    }
    glAttachShader(m_ProgramId,shaderId);
    glDeleteShader(shaderId);
}
std::string ShaderProgram::getShaderFromFile(const char* fileName){
    std::ifstream file(fileName);
    std::string data;
    if (file.is_open())
    {
        char readChar;
        while ((readChar=file.get())!=EOF)
        {
            data+=readChar;
        }
        file.close();    
    }
    return data; 
}