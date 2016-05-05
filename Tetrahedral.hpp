#ifndef TETRAHEDRAL_H
#define TETRAHEDRAL_H
#include "DGP/Common.hpp"
#include "DGP/Vector3.hpp"
#include <list>

using namespace DGP;
using std::list;

class Tetrahedral{
private:
	std::list<Vector3> samp_pts;
public:
	Tetrahedral();
	Tetrahedral(list<Vector3>);
	~Tetrahedral();
	void print_tetra(void);
	list<Vector3> get_vertices(list<float>,float);
	list<Vector3> get_sample_points(void);
};

#endif
