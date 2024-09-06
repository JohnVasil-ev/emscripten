#include <iostream>
#include <cmath>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

struct RenderStats {
	int fps = 0;
	double prevTime = 0;
};

RenderStats renderStats;

void mainLoop(void* mainLoopArg) {
	double currentTime = emscripten_performance_now() * 0.001;
	double deltaTime = currentTime - renderStats.prevTime;
	renderStats.prevTime = currentTime;
	renderStats.fps = std::round(1 / deltaTime);

	emscripten_run_script(("document.getElementById('fps').innerHTML = 'FPS: " + std::to_string(renderStats.fps) + '\'').c_str());
	emscripten_run_script(("document.getElementById('delta').innerHTML = 'Delta: " + std::to_string(deltaTime) + '\'').c_str());
}

int main(int argc, char** argv) {
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(mainLoop, (void*)argv, 0, true);
#else
	while(true) {
		mainLoop((void*)argv);
	}
#endif
}
