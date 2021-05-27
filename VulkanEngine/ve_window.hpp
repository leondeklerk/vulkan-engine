#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace ve {
	class VeWindow {
	public:
		VeWindow(int w, int h, std::string name);
		~VeWindow();

		VeWindow(const VeWindow&) = delete;
		VeWindow& operator=(const VeWindow&) = delete;

		bool shouldClose();

		VkExtent2D getExtent();

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

		bool wasWindowResized();

		void resetWindowResizedFlag();
	private:
		int width;
		int height;
		bool frameBufferResized = false;

		std::string windowName;

		GLFWwindow* window;

		void initWindow();
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	};
}