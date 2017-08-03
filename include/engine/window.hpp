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
        void on_resize(const boost::function<void (int, int)> &func);

    private:
        GLFWwindow *m_handle;

        std::string m_title;
        int m_width, m_height;

        boost::signals2::signal<void (int, int)> m_resize_sig;

        static void size_callback(GLFWwindow *win, int width, int height);
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_WINDOW_HPP
