#ifndef SURFACING_H
#define SURFACING_H

#include<list>
#include<vector>
#include"DGP/Vector3.hpp"
#include"Tetrahedral.hpp"
#include"DGP/AxisAlignedBox3.hpp"

using std::list;
using std::vector;
using namespace DGP;

list<Tetrahedral> find_tetrahedral(Vector3,float);

void find_grid(AxisAlignedBox3, float, vector<unsigned int> *);

void create_iterator(AxisAlignedBox3, float, vector<unsigned int>, vector<vector<float>> *);

void iterate_all(vector<vector<float>> const *,float, AxisAlignedBox3,list<list<Vector3>>*);

bool is_tetra_inside(Tetrahedral,AxisAlignedBox3);

#endif
