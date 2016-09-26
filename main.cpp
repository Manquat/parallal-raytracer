#include <iostream>
#include <mpi.h>
#include "Screen.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

using namespace std;

int main(int argc, char* argv[]) {

    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    unsigned int ray_per_recursion(20);
    unsigned int max_levels(3);

    unsigned int height(1000);
    unsigned int width(1000);

    if (argc > 1) {
        ray_per_recursion = std::abs(stoi(argv[1]));
        std::cout << "ray :" << ray_per_recursion << std::endl;
    }
    if (argc > 2) {
        max_levels = std::abs(stoi(argv[2]));
        std::cout << "levels :" << max_levels << std::endl;
    }
    if (argc > 3) {
        height = std::abs(stoi(argv[3]));
        width = height;
        std::cout << "height :" << height << std::endl;
    }

    /*{
		Scene scene;
		scene.addPrimitive(new Sphere(Point(5, 0, -17), 5));
		scene.addLight(new Light(Point(15, 10, 0), 500 * Color::Ones()));
        
		Serializer serializer;


        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if (size < 2) {
            return -size;
        }

        if (rank == 0) {
            std::cout << "Sending scene : " << scene << std::endl;
            serializer.send(scene, 1);
        }

        Scene *recev_scene = nullptr;
        if (rank == 1) {
            recev_scene = serializer.receiveScene();
            std::cout << "Received scene : " << *recev_scene << std::endl;
        }
    }*/

    /*Parser parser("default.config");

    parser.readFile();*/

    /*Scene* scene;

    Generator generator;
    scene = generator.generate(10,0);*/

	{
		Serializer serializer;
		int rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		int mpi_size;
		MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

		Scene* scene;

		if (rank == 0)
		{
			scene = new Scene();
			scene->addPrimitive(new Sphere(Point(0, 0, -10), 5));

			Material material(Color(255, 0, 0));

			Sphere *sphere = new Sphere(Point(5, 0, -17), 5);
			material.setPhong(Color(255, 255, 255), 0, 10, 10);
			sphere->setMaterial(material);
			scene->addPrimitive(sphere);

			sphere = new Sphere(Point(0, 5, -16), 5);
			material.setPhong(Color(0, 0, 255), 0, 10, 10);
			sphere->setMaterial(material);
			scene->addPrimitive(sphere);

			sphere = new Sphere(Point(-5, 5, -10), 5);
			material.setPhong(10 * Color::Ones(), 1, 10, 100);
			sphere->setMaterial(material);
			scene->addPrimitive(sphere);

			sphere = new Sphere(Point(-10, -5, 15), 10);
			material.setPhong(Color(0, 255, 255), 0, 10, 100);
			sphere->setMaterial(material);
			scene->addPrimitive(sphere);


			scene->addLight(new Light(Point(15, 10, 0), 500 * Color::Ones()));
			scene->addLight(new Light(Point(-30, 0, 0), 500 * Color::Ones()));

			for (int i(1); i < mpi_size; i++)
			{
				serializer.send(*scene, i);
			}
		}
		else
		{
			scene = serializer.receiveScene();
		}


		Screen screen(height, width);

		Camera camera(scene, width, height, 25, 25, 1,
			Point::Zero(),
			-Vector::UnitZ(),
			Vector::UnitY()
		);

		camera.setRecursiveParameter(ray_per_recursion, max_levels);

		camera.draw(screen);

		screen.writeInFile("test.tga");
	}

    MPI_Finalize();

    return 0;
}
