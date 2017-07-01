#include "Window.hpp"
#include "Debug.hpp"
#include "Logger.hpp"

std::map <GLFWwindow *, gl::Window *> gl::window_reference;

void glfw::error_callback(int error, const char* description) {
#ifndef NDEBUG
  Logger::Error("[GLFW] code %i msg: %s\n", error, description);
#endif
}

void glfw::keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  gl::window_reference[window]->KeyboardEvent(key, scancode, action, mods);
}

void glfw::size_callback(GLFWwindow *window, int new_width, int new_height) {
  gl::window_reference[window]->Resize((float)new_width, (float)new_height);
}

void glfw::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
  double m_x, m_y;
  glfwGetCursorPos(window, &m_x, &m_y);
  gl::window_reference[window]->MouseClick(m_x, m_y, button, action, mods);
}

void glfw::mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  gl::window_reference[window]->MouseScroll(xoffset, yoffset);
}
