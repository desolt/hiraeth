#include "engine/window.hpp"

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

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glViewport(0, 0, width, height);

        glfwSetWindowUserPointer(m_handle, this);
        glfwSetWindowSizeCallback(m_handle, size_callback);
    }

    window::~window()
    {
        glfwDestroyWindow(m_handle);
    }

    int window::get_width() const noexcept
    {
        return m_width;
    }

    int window::get_height() const noexcept
    {
        return m_height;
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

    void window::on_resize(const boost::function<void(int, int)> &func)
    {
        m_resize_sig.connect(func);
    }

    void window::size_callback(GLFWwindow *handle, int width, int height)
    {
        window *win = reinterpret_cast<window *>(glfwGetWindowUserPointer(handle));

        win->m_width = width;
        win->m_height = height;

        glViewport(0, 0, width, height);

        win->m_resize_sig(width, height);
    }

} // namespace hiraeth::engine
