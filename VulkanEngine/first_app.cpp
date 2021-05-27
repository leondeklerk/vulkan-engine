#include "first_app.hpp"
#include "simple_render_system.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

namespace ve {
	FirstApp::FirstApp()
	{
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		SimpleRenderSystem simpleRenderSystem{ veDevice, veRenderer.getSwapChainRenderPass() };
		while (!veWindow.shouldClose()) {
			glfwPollEvents();

			if (auto commandBuffer = veRenderer.beginFrame()) {
				veRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				veRenderer.endSwapChainRenderPass(commandBuffer);
				veRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(veDevice.device());
	}

	void FirstApp::loadGameObjects()
	{
		std::vector<VeModel::Vertex> vertices{
			//{{0.0f, 0.05f }, {1.0f, 0.0f, 0.0f}}, // Bottom
			//{{0.25f, 0.55f}, {0.0f, 1.0f, 0.0f}},
			//{{-0.25f, 0.55f}, {0.0f, 0.0f, 1.0f}},

			//{{0.0f, -0.05f }, {1.0f, 0.0f, 0.0f}}, // Top
			//{{0.25f, -0.55f}, {0.0f, 1.0f, 0.0f}},
			//{{-0.25f, -0.55f}, {0.0f, 0.0f, 1.0f}},

			//{{-0.05f, 0.0f }, {1.0f, 0.0f, 0.0f}}, // Left
			//{{-0.55f, -0.25f}, {0.0f, 1.0f, 0.0f}},
			//{{-0.55f, 0.25f}, {0.0f, 0.0f, 1.0f}},

			//{{0.05f, 0.0f }, {1.0f, 0.0f, 0.0f}}, // Right
			//{{0.55f, -0.25f}, {0.0f, 1.0f, 0.0f}},
			//{{0.55f, 0.25f}, {0.0f, 0.0f, 1.0f}}
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

		auto veModel = std::make_shared<VeModel>(veDevice, vertices);

		auto triangle = VeGameObject::createGameObject();
		triangle.model = veModel;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}
}