#pragma once
struct GLFWwindow;
namespace aie
{
	class context
	{
		GLFWwindow* window;

	public:
		bool init(int width, int height, const char* title);
		void tick();
		void clear();
		void term();

		bool shouldClose() const;
	};
}
