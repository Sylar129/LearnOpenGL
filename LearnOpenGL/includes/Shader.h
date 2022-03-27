#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // ʹ��/�������
    void Use();

    // ɾ������
    void Delete();

    // uniform���ߺ���
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetFloat4(const std::string& name, float value1, float value2, float value3, float value4) const;
private:
    // ����ID
    unsigned int m_ID = 0;
    bool m_Deleted = true;
};
