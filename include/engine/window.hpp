#ifndef HIRAETH_ENGINE_WINDOW_HPP
#define HIRAETH_ENGINE_WINDOW_HPP

#include <string>
#include <GLFW/glfw3.h>

namespace hiraeth::engine {

    class window {
    public:
        window(const std::string &title, int width, int height);
        virtual ~window();

        bool should_close() const noexcept;
        void update();

    private:
        GLFWwindow *m_handle;

        std::string m_title;
        int m_width, m_height;
    };

} // namespace hiraeth::engine

#endif //HIRAETH_ENGINE_WINDOW_HPP
