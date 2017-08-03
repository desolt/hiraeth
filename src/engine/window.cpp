#include "engine/window.hpp"
#include <stdexcept>

namespace hiraeth::engine {

    window::window(const std::string &title, int width, int height)
            : m_title(title),
              m_width(width),
              m_height(height)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if (m_handle == nullptr)
            throw std::runtime_error("engine::window: could not create the window.");
        glfwMakeContextCurrent(m_handle);
    }

    window::~window()
    {
        glfwDestroyWindow(m_handle);
    }

    bool window::should_close() const noexcept
    {
        return glfwWindowShouldClose(m_handle);
    }

    void window::update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_handle);
    }

} // namespace hiraeth::engine
