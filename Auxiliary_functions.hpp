#ifndef AUXILIARY_FUNCTIONS_H
#define AUXILIARY_FUNCTIONS_H

#include"DGP/Vector3.hpp"
#include<list>
#include"Tetrahedral.hpp"
#include<string>

using std::list;
using namespace DGP;
using std::string;

list<float> evaluate_surface(Tetrahedral);

float evaluate_fn(Vector3);

bool less_than(float,float);

bool compare_points(Vector3,Vector3);

void save_mesh(list<list<Vector3>> const *,string);

#endif
