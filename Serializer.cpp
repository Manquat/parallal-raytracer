//
// Created by gautier on 04.06.16.
//

#include "Serializer.h"
#include <iostream>

Serializer::Serializer() {
    // creation of the mpi_sphere data type
    constexpr int numberOfItemsSphere = 2 + 4;
    int blockLengthsSphere[numberOfItemsSphere] = {VECTOR_SIZE, 1, COLOR_SIZE,
                                       COLOR_SIZE, COLOR_SIZE, COLOR_SIZE};
    MPI_Datatype typesSphere[numberOfItemsSphere] = {MPI_FLOAT, MPI_FLOAT, MPI_FLOAT,
                                         MPI_FLOAT, MPI_FLOAT, MPI_FLOAT};

    MPI_Aint offsetsSphere[numberOfItemsSphere];
    offsetsSphere[0] = 0;
    offsetsSphere[1] = sizeof(float) * VECTOR_SIZE;
    offsetsSphere[2] = offsetsSphere[1] + sizeof(float);
    offsetsSphere[3] = offsetsSphere[2] + sizeof(float) * COLOR_SIZE;
    offsetsSphere[4] = offsetsSphere[3] + sizeof(float) * COLOR_SIZE;
    offsetsSphere[5] = offsetsSphere[4] + sizeof(float) * COLOR_SIZE;

    MPI_Type_create_struct(numberOfItemsSphere, blockLengthsSphere, offsetsSphere, typesSphere, &mpi_sphere_);
    MPI_Type_commit(&mpi_sphere_);

	// creation of the mpi_light data type
	constexpr int numberOfItemsLight = 2;
	int blockLengthsLight[numberOfItemsLight] = { VECTOR_SIZE, COLOR_SIZE};
	MPI_Datatype typesLight[numberOfItemsLight] = { MPI_FLOAT, MPI_FLOAT };

	MPI_Aint offsetsLight[numberOfItemsLight];
	offsetsLight[0] = 0;
	offsetsLight[1] = sizeof(float) * VECTOR_SIZE;

	MPI_Type_create_struct(numberOfItemsLight, blockLengthsLight, offsetsLight, typesLight, &mpi_light_);
	MPI_Type_commit(&mpi_light_);
}

Serializer::~Serializer() {
    MPI_Type_free(&mpi_sphere_);
}

void Serializer::send(Sphere const &sphere, int const &destination, int const &tag) const {
    Sphere::sSphere s_sphere = Sphere::sphereToStruct(sphere);
    MPI_Send(&s_sphere, 1, mpi_sphere_, destination, tag, MPI_COMM_WORLD);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "The node " << rank << ": send a sphere to " << destination << std::endl;
}

void Serializer::send(Light const& ligth, int const& destination, int const& tag) const {
	Light::sLight s_light = Light::lightToStruct(ligth);
	MPI_Send(&s_light, 1, mpi_light_, destination, tag, MPI_COMM_WORLD);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "The node " << rank << ": send a light to " << destination << std::endl;
}


void Serializer::send(Scene const &scene, int const& destination, int const& tag) const {
	int numberOf[2] = { scene.getNumberOfPrimitive(), scene.lights_.size() };
	MPI_Send(&numberOf, 2, MPI_INT, destination, MPI_SIZE_TAG, MPI_COMM_WORLD);

	for (Primitive* primitive : scene.primitives_)
	{
		send(*static_cast<Sphere*>(primitive), destination, tag);
	}
	
	for (Light* light : scene.lights_)
	{
		send(*light, destination, tag);
	}
}

Sphere *Serializer::receiveSphere(int const &source, const int &tag) const {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "The node " << rank << ": receive a sphere from " << source << std::endl;

    Sphere::sSphere s_sphere;
    MPI_Status status;

    MPI_Recv(&s_sphere, 1, mpi_sphere_, source, tag, MPI_COMM_WORLD, &status);

    Sphere *sphere = Sphere::structToSphere(s_sphere);
    return sphere;
}

Light* Serializer::receiveLight(int const &source, const int &tag) const {
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "The node " << rank << ": receive a light from " << source << std::endl;

	Light::sLight s_light;
	MPI_Status status;

	MPI_Recv(&s_light, 1, mpi_light_, source, tag, MPI_COMM_WORLD, &status);

	Light *light = Light::structToLight(s_light);
	return light;
}

Scene* Serializer::receiveScene(int const& source, int const& tag) const {
	int numberOf[2];
	MPI_Status status;

	MPI_Recv(&numberOf, 2, MPI_INT, source, MPI_SIZE_TAG, MPI_COMM_WORLD, &status);

	unsigned int numberOfSphere(static_cast<unsigned int>(numberOf[0]));
	unsigned int numberOfLight(static_cast<unsigned int>(numberOf[1]));

	Scene* scene = new Scene();

	for (unsigned int i(0); i < numberOfSphere; i++)
	{
		 scene->addPrimitive(receiveSphere(source, tag));
	}

	for (unsigned int i(0); i < numberOfLight; i++)
	{
		scene->addLight(receiveLight(source, tag));
	}

	return scene;
}










