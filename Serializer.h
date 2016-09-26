//
// Created by gautier on 04.06.16.
//

#ifndef RAYTRACER_SERIALIZER_H
#define RAYTRACER_SERIALIZER_H

#include <mpi.h>
#include "Sphere.h"
#include "Scene.h"

class Sphere;
class Ligth;

class Serializer {
public:
    Serializer();

    ~Serializer();

    void send(Sphere const& sphere, int const& destination, int const &tag = 0) const;
	void send(Light const& ligth, int const& destination, int const& tag = 0) const;
    void send(Scene const& scene, int const& destination, int const& tag = 0) const;

    Sphere* receiveSphere(int const& source = MPI_ANY_SOURCE, int const& tag = MPI_ANY_TAG) const;
	Light* receiveLight(int const& source = MPI_ANY_SOURCE, int const& tag = MPI_ANY_TAG) const;
	Scene* receiveScene(int const& source = MPI_ANY_SOURCE, int const& tag = MPI_ANY_TAG) const;

private:

    MPI_Datatype mpi_sphere_;
	MPI_Datatype mpi_light_;

	constexpr static int MPI_SIZE_TAG = 10;
};


#endif //RAYTRACER_SERIALIZER_H
