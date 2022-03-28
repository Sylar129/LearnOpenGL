#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "stb_image.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// �Զ��庯��
void ProcessInput(GLFWwindow* window);

int main() {
    // ��ʼ��glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ͼƬ�ߵ�
    stbi_set_flip_vertically_on_load(true);

    // ����һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ע�ᴰ�ڴ�С�ص�����
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // ��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ����Shader����
    Shader shader("res/shaders/VertexShader.glsl", "res/shaders/FragmentShader.glsl");

    // ���嶥������
    float vertices[] = {
        //       λ��       //       ��ɫ      //  ��������
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,     // ����
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // ����
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,     // ����
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f      // ����
    };

    // ������������
    unsigned int indices[] = {
        0, 1, 3,    // ��һ��������
        1, 2, 3     // �ڶ���������
    };

    // ���ɶ����������(Vertex Array Objects, VAO)
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);

    // ���ɶ��㻺�����(Vertex Buffer Objects, VBO)
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    // ���������������(Index Buffer Object,IBO/Element Buffer Object, EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // ���������
    glBindVertexArray(VAO);

    // �󶨶��㻺�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // �������������
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // �߿�ģʽ����ѡ��
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ��������
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // �����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ����ͼƬ
    int width, height, channels;
    unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &channels, 0);

    // ��������
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture1" << std::endl;
    }

    // �ͷ��ڴ�
    stbi_image_free(data);


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // �����������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ����ͼƬ
    data = stbi_load("res/textures/awesomeface.png", &width, &height, &channels, 0);

    // ��������
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture2" << std::endl;
    }

    // �ͷ��ڴ�
    stbi_image_free(data);

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    // ��Ⱦѭ��(Rnder Loop)
    while (!glfwWindowShouldClose(window)) {
        // ��������
        ProcessInput(window);

        // ��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.Use();

        // ��VAO
        glBindVertexArray(VAO);

        // ����������
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ��鲢�����¼�����������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();

    // �ͷ���Դ
    glfwTerminate();
    return 0;
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
