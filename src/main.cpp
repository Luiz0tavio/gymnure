#include <memory>
#include <chrono>
#include "../gymnure.h"

int main(int argc, char** argv) {

	const unsigned windowWidth  = 800;
	const unsigned windowHeight = 600;

	{
		auto gymnure = std::make_unique<Gymnure>(windowWidth, windowHeight);

		auto room2 = GymnureData{};
		room2.path_texture 	= "../../assets/room2.png";
		room2.path_obj 		= "../../assets/room2.obj";
		gymnure->addObject(room2);

		auto chalet = GymnureData{};
		chalet.path_texture = "../../assets/chalet.jpg";
		chalet.path_obj 	= "../../assets/chalet.obj";
		gymnure->addObject(chalet);

		auto cube = GymnureData{};
		cube.path_obj 		= "../../assets/cube.obj";
		cube.path_texture 	= "../../assets/sky.jpg";
		cube.obj_mtl 		= const_cast<char *>(std::string("../../assets/cube.mtl").data());
		gymnure->addSkybox(cube);

		gymnure->prepare();

		while(true) {

            auto start = std::chrono::high_resolution_clock::now();

			if (!gymnure->draw()) break;

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            auto fps = 1.f / (static_cast<float>(duration) * 0.000001);

            std::cout << fps << std::endl;
        }
	}

	return EXIT_SUCCESS;
}
