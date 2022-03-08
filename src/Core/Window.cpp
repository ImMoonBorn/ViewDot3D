#include "pch.h"
#include "Window.h"

namespace Core
{
    GLFWwindow* Window::m_GLWindow;
    std::string Window::m_Name;
    uint32_t Window::m_Width;
    uint32_t Window::m_Height;
    
    int Window::Create(std::string name, uint32_t width, uint32_t height)
    {
        m_Name = name;
        m_Width = width;
        m_Height = height;
    
        if (!glfwInit())
            return -1;
    
        m_GLWindow = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
        
        if (!m_GLWindow)
        {
            glfwTerminate();
            return -1;
        }
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(m_GLWindow, (vidmode->width - m_Width) / 2, (vidmode->height - m_Height) / 2);

        glfwMakeContextCurrent(m_GLWindow);
        glfwSetWindowSizeCallback(m_GLWindow, window_size_callback);
        glfwSetFramebufferSizeCallback(m_GLWindow, framebuffer_size_callback);
        glfwSetScrollCallback(m_GLWindow, Input::ScrollCallback);
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glfwSwapInterval(1);
    
        if (glewInit() != GLEW_OK)
            DebugErr("Error GLEW");
    
        DebugNor(glGetString(GL_VERSION));
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_PROGRAM_POINT_SIZE);
        return 1;
    }
    
    void Window::window_size_callback(GLFWwindow* window, int width, int height)
    {
        Window::m_Width = width;
        Window::m_Height = height;
    }
    
    void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        WindowResizeEvent event{ width, height };
        Application::DeployEvent(event);
    }
    
    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_GLWindow);
        glfwPollEvents();
    }
}
