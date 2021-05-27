#include "ve_window.hpp"
#include <stdexcept>

namespace ve {

	VeWindow::VeWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	}

	VeWindow::~VeWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void VeWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}

	void VeWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto veWindow = reinterpret_cast<VeWindow*>(glfwGetWindowUserPointer(window));
		veWindow->frameBufferResized = true;
		veWindow->width = width;
		veWindow->height = height;
	}

	bool VeWindow::shouldClose() {
		return glfwWindowShouldClose(window);
	}

	VkExtent2D VeWindow::getExtent()
	{
		return {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};
	}

	void VeWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed");
		}
	}

	bool VeWindow::wasWindowResized()
	{
		return frameBufferResized;
	}

	void VeWindow::resetWindowResizedFlag()
	{
		frameBufferResized = false;
	}
}