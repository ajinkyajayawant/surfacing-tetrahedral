#include "Tetrahedral.hpp"
#include <list>
#include <cmath>

using std::cout; using std::cin; using std::endl;
using std::abs;

Tetrahedral::Tetrahedral(){}

Tetrahedral::Tetrahedral(list<Vector3> samp_in){
	std::list<Vector3>::iterator pt_in;
	std::list<Vector3>::iterator pt;
	pt = samp_pts.begin();
	
	for(pt_in=samp_in.begin();pt_in!=samp_in.end();++pt_in)
		samp_pts.insert(pt,*pt_in);
}

Tetrahedral::~Tetrahedral(){}

void Tetrahedral::print_tetra(){
	std::list<Vector3>::iterator pt;
	pt = samp_pts.begin();
	
	cout<< "The list of points are" << *pt++ << ", " << *pt++ << ", " << *pt++<< ", " << *pt++ << endl;
	return;
}

list<Vector3> Tetrahedral::get_vertices(list<float> surf_vals,float iso_val){
	/*This function gives the vertices on the edges of the tetrahedral where the iso surface intesects the tetrahedral. Arguments to the function involve values of the surface at the points in the tetrahedral. Value of the iso surface also needs to be given. It is assumed that the surface values are given in the order p_1, p_2, p_3, p_4. Vertices list is constructed by pushing in the front and the back alternatively so that in case of four vertices where the surface intersects the tetrahedral, we get those vertices in cyclic order from which a quad face can be constructed.*/
	list<Vector3> vertices;
	list<Vector3> less_than_iso;
	list<Vector3> more_than_iso;
	list<float> less_val;
	list<float> more_val;

	assert(surf_vals.size()==4);

	list<float>::iterator it_surf=surf_vals.begin();
	list<Vector3>::iterator it_samp=samp_pts.begin();
	for(;it_surf!=surf_vals.end() && it_samp!=samp_pts.end();++it_surf,++it_samp){
		if(*it_surf<iso_val){
			less_than_iso.push_back(*it_samp);
			less_val.push_back(*it_surf);
		}
		else{
			more_than_iso.push_back(*it_samp);
			more_val.push_back(*it_surf);
		}
	}

	list<Vector3>::iterator it_l=less_than_iso.begin();
	list<float>::iterator it_lval=less_val.begin();	
	for(;it_l!=less_than_iso.end() && it_lval!=less_val.end();++it_l,++it_lval){
		int i=0;
		list<Vector3>::iterator it_m=more_than_iso.begin();
		list<float>::iterator it_mval=more_val.begin();
		for(;it_m!=more_than_iso.end() && it_mval!=more_val.end();++it_m,++it_mval,++i){	
			Vector3 v1 = *it_l;
			Vector3 v2 = *it_m;			
			Vector3 new_vertex;
			float diff_tot = abs(*it_lval-*it_mval);
			float diff_1 = abs(*it_lval-iso_val);
			float diff_2 = abs(*it_mval-iso_val);

			new_vertex = (v1*diff_2 + v2*diff_1)/diff_tot;
			if(i%2==0)
				vertices.push_front(new_vertex);
			else
				vertices.push_back(new_vertex);
		}
	}
	
	return vertices;
}

list<Vector3> Tetrahedral::get_sample_points(){
	/*This function returns the points of the tetrahedral in the order p_1, p_2, p_3, p_4. This function will return the sample points, on which the surface can be evaluated by some other function.*/
	return samp_pts;
}
