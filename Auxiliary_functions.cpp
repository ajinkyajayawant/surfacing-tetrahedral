/*These functions are neither tetrahedral functions nor are surfacing functions. These are helper functions.*/

#include "Auxiliary_functions.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include<cmath>

using std::list;
using namespace DGP;
using std::lexicographical_compare;
using std::ofstream;
using std::endl;using std::cout;
using std::string;
using std::abs;
using std::max;

list<float> evaluate_surface(Tetrahedral tetra){
	/*This function will evaluate the function on points on the tetrahedral and return the values.*/
	list<Vector3> points = tetra.get_sample_points();
	list<float> vals(points.size(),0.0);

	list<Vector3>::iterator it_p = points.begin();
	list<float>::iterator it_v = vals.begin();
	for(;it_p!=points.end() && it_v!=vals.end();++it_p,++it_v)
		*it_v = evaluate_fn(*it_p);

	return vals;
}

float evaluate_fn(Vector3 pt){
	float x1 = pt.x();
	float y1 = pt.y();	
	float z1 = pt.z();	

	//Sphere
	//float val = x1*x1+y1*y1+z1*z1 - 25.0;
	//Klein bottle
	//float val = (x1*x1+y1*y1+z1*z1+2*y1-1)*((x1*x1+y1*y1+z1*z1-2*y1-1)*(x1*x1+y1*y1+z1*z1-2*y1-1)-8*z1*z1)+16*x1*z1*(x1*x1+y1*y1+z1*z1-2*y1-1);
	// Cube
	float val = max(max(abs(x1),abs(y1)),abs(z1))-4.0;
	
	return val;
}

bool less_than(float a, float b){
	/*This function does a basic check whether a+eps<b. We do not just want two very similar numbers like 2.33 2.34 to be unequal. This function will be used for sorting the points according to their x, y, z coordinates in lexicographical order. If x coordinates are almost similar, we want the points to be compared with respect to their y and z coordinates. Epsilon is hardcoded in this function because this function is used in the lexicographical compare function which only accepts a compare function taking two arguments. Ths function was abandoned when I realized that duplicate vertices are fine.*/
	float eps = 0.1;
	bool is_less = (a+eps<b);
	return is_less;	
}

bool compare_points(Vector3 p1, Vector3 p2){
	/*This function is wrote with the sole purpose of using in the sorting function. The lexicographical_function did not support the suitable arguments as needed by the sort function. Ths function was abandoned when I realized that duplicate vertices are fine.*/
		return lexicographical_compare(p1.begin(),p1.end(),p2.begin(),p2.end(),less_than);
}

void save_mesh(list<list<Vector3>> const *p_verts,string filename){
	ofstream off_file;
	list<list<unsigned int>> indexes;
	unsigned int no_faces = p_verts->size();
	unsigned int no_vertices = 0;

	cout<<"Printing size of vertices list "<<p_verts->size()<<"\n";


	for(auto it_v=p_verts->begin();it_v!=p_verts->end();++it_v){		
		unsigned int i=0;
		unsigned int no_vert=it_v->size();
		list<unsigned int> ind_v;
		
		for(;i<no_vert;++i)
			ind_v.push_back(no_vertices+i);		
		indexes.push_back(ind_v);
		
		no_vertices += no_vert;
	}
	unsigned int no_edges = no_vertices;
	
	off_file.open(filename);
	off_file<< "OFF\n";
	off_file<< no_vertices<<" "<<no_faces<<" "<<no_edges<<" "<<endl;
	//next line and the following parts from for loop for debugging
	//unsigned int i = 1;	
	for(auto it_vs=p_verts->begin();it_vs!=p_verts->end();++it_vs){			
		for(auto it_v=it_vs->begin();it_v!=it_vs->end();++it_v){
			//off_file<<i<<" ";
			off_file<< it_v->x()<<" "<<it_v->y()<<" "<<it_v->z()<<" "<<endl;
		}
		//debugging
		//off_file<<"\n";
	}
	cout<<"Size of indexes is "<<indexes.size()<<endl;
	for(auto it_inds=indexes.begin();it_inds!=indexes.end();++it_inds){
off_file<<it_inds->size()<<" ";
		for(auto it_ind=it_inds->begin();it_ind!=it_inds->end();++it_ind){
			off_file<<*it_ind<<" ";
		}
		off_file<<endl;
	}
	
	off_file.close();	
	
	return;
}
