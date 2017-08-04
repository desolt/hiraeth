#ifndef HIRAETH_ENGINE_WINDOW_HPP
#define HIRAETH_ENGINE_WINDOW_HPP

#include <string>
#include <boost/signals2.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hiraeth::engine {

    class window {
    public:
        window(const std::string &title, int width, int height);
        virtual ~window();

        int get_width() const noexcept;
        int get_height() const noexcept;
        bool should_close() const noexcept;

        void update();

        // signal callbacks
        void on_key(const boost::function<void (int, int, int, int)> &func);
        void on_resize(const boost::function<void (int, int)> &func);

    private:
        GLFWwindow *m_handle;

        std::string m_title;
        int m_width, m_height;

        boost::signals2::signal<void (int, int, int, int)> m_key_sig;
        boost::signals2::signal<void (int, int)> m_resize_sig;

        static void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods);
        static void size_callback(GLFWwindow *handle, int width, int height);
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_WINDOW_HPP
