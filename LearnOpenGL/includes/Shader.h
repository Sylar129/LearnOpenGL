#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // 构造器读取并构建着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // 使用/激活程序
    void Use();

    // 删除程序
    void Delete();

    // uniform工具函数
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetFloat4(const std::string& name, float value1, float value2, float value3, float value4) const;
private:
    // 程序ID
    unsigned int m_ID = 0;
    bool m_Deleted = true;
};
