/*This file includes functions for surfacing an iso-surface. This means that given a function in space we construct a mesh over its iso surface.*/

#include<cmath>
#include"Surfacing.hpp"
#include"Auxiliary_functions.hpp"

using std::sqrt; using std::floor;
using std::cout; using std::endl;

const float dist_x = sqrt(2.0);
const float dist_y = 0.5;
const float dist_z = 1/sqrt(2.0);

list<Tetrahedral> find_tetrahedral(Vector3 pt,float reso){
	/*This function returns two tetrahedrals, one on left and one on right of the provided point. reso is the resolution of the mesh, it is basically the scaling factor for all the distances in the mesh.*/
	float del_x = 1/sqrt(2);
	float del_y = 0.5;
	float del_z = 1/sqrt(2);
	list<Vector3> left_points;
	list<Vector3> right_points;
	list<Vector3> down_left_points;
	list<Vector3> down_right_points;
	list<Vector3> diag_left_points;
	list<Vector3> diag_right_points;
	
	Vector3 v1(pt.x()-reso*del_x,pt.y()+reso*del_y,pt.z());
	left_points.push_back(v1);
	Vector3 v2(pt.x()-reso*del_x,pt.y()-reso*del_y,pt.z());
	left_points.push_back(v2);
	Vector3 v3(pt.x()-reso*del_x,pt.y(),pt.z()+reso*del_z);
	left_points.push_back(v3);
	left_points.push_back(pt);
	
	Vector3 v4(pt.x()+reso*del_x,pt.y()+reso*del_y,pt.z());
	right_points.push_back(v4);
	Vector3 v5(pt.x()+reso*del_x,pt.y()-reso*del_y,pt.z());
	right_points.push_back(v5);
	Vector3 v6(pt.x()+reso*del_x,pt.y(),pt.z()+reso*del_z);
	right_points.push_back(v6);
	right_points.push_back(pt);

	// I wish there was a better way of initializing a list
	down_left_points.push_back(v1);
	down_left_points.push_back(v2);
	Vector3 v7(pt.x()-reso*del_x,pt.y(),pt.z()-reso*del_z);
	down_left_points.push_back(v7);
	down_left_points.push_back(pt);

	down_right_points.push_back(v4);
	down_right_points.push_back(v5);
	Vector3 v8(pt.x()+reso*del_x,pt.y(),pt.z()-reso*del_z);
	down_right_points.push_back(v8);
	down_right_points.push_back(pt);

	Vector3 v9(pt.x(),pt.y()+reso*del_y,pt.z()+reso*del_z);
	diag_left_points.push_back(v9);
	Vector3 v10(pt.x()-reso*del_x,pt.y(),pt.z()+reso*del_z);
	diag_left_points.push_back(v10);	
	diag_left_points.push_back(v1);
	diag_left_points.push_back(pt);

	diag_right_points.push_back(v9);
	Vector3 v11(pt.x()+reso*del_x,pt.y(),pt.z()+reso*del_z);
	diag_right_points.push_back(v11);	
	diag_right_points.push_back(v4);
	diag_right_points.push_back(pt);
	
	Tetrahedral left_tetra(left_points);
	Tetrahedral right_tetra(right_points);
	Tetrahedral down_left_tetra(down_left_points);
	Tetrahedral down_right_tetra(down_right_points);
	Tetrahedral diag_left_tetra(diag_left_points);
	Tetrahedral diag_right_tetra(diag_right_points);
	list<Tetrahedral> tetra_list;
	tetra_list.push_back(left_points);
	tetra_list.push_back(right_points);
	tetra_list.push_back(down_left_points);
	tetra_list.push_back(down_right_points);
	tetra_list.push_back(diag_left_points);
	tetra_list.push_back(diag_right_points);	
	
	return tetra_list;
}

void find_grid(AxisAlignedBox3 bbox, float reso,vector<unsigned int> *no_planes){
	/*This function finds the number of x, y and z planes that can fit in a given bounding box. The resolution(scaling factor) needed for the grid is specified as reso. This function fills up the no_planes vector by the number of x,y and z planes which will be able to fit in the bounding box. Assuming that th vector that will be passed to this function will be already initialized to length three. Since the bounding box is not to be treated too seriously to the point of one extra sample in one dimension, we will not specify two different fields for x direction size in no_planes.*/
	Vector3 lengths= bbox.getExtent();
	cout<<no_planes->size()<<endl;
	assert(no_planes->size()==3);

	(*no_planes)[0] = (unsigned int)floor(lengths[0]/(dist_x*reso));
	(*no_planes)[1] = (unsigned int)floor(lengths[1]/(dist_y*reso));
	(*no_planes)[2] = (unsigned int)floor(lengths[2]/(dist_z*reso));

	return;
}

void create_iterator(AxisAlignedBox3 bbox, float reso, vector<unsigned int> no_planes, vector<vector<float>> *grid_lines){
	/*This function creates four lists and puts them in a vector. The first list is a list of valid x coordinates. The second list is also a list of valid x coordinates. You see, the second list of valid x coordinates is shifted by 1/sqrt(2) from the first list. The third contains valid y coordinates. The third list contains valid z coordinates. All these lists are in the gid_lines vector.*/
	Vector3 start = bbox.getLow();	

	vector<float> x1 (no_planes[0]);
	vector<float> y1 (no_planes[1]);
	vector<float> z1 (no_planes[2]);
	(*grid_lines)[0] = x1;
	(*grid_lines)[1] = x1;
	(*grid_lines)[2] = y1;
	(*grid_lines)[3] = z1;

	for(unsigned int i=0;i<no_planes[0];++i)
		(*grid_lines)[0][i] = start.x()+reso*dist_x*i;
	for(unsigned int i=0;i<no_planes[0];++i)
		(*grid_lines)[1][i] = start.x()+reso*dist_x/2+reso*dist_x*i;
	for(unsigned int i=0;i<no_planes[1];++i)
		(*grid_lines)[2][i] = start.y()+reso*dist_y*i;
	for(unsigned int i=0;i<no_planes[2];++i)
		(*grid_lines)[3][i] = start.z()+reso*dist_z*i;

	return;
}

void iterate_all(vector<vector<float>> const *grid_lines, float reso, AxisAlignedBox3 bbox,list<list<Vector3>> *vertices){
	/*This function iterates over the grid lines and prints the tetrahedrals associates inside the bounding box associated with the points of the grid lines.*/
	vector<float> x1_cords = (*grid_lines)[0];
	vector<float> x2_cords = (*grid_lines)[1];
	vector<float> y_cords = (*grid_lines)[2];
	vector<float> z_cords = (*grid_lines)[3];
	vector<float> x_cords;

	bool x1=true;
	for(auto it_z=z_cords.begin();it_z!=z_cords.end();++it_z){
		bool x2=x1;
		for(auto it_y=y_cords.begin();it_y!=y_cords.end();++it_y){
			if(x2)				
				x_cords = x1_cords;
			else
				x_cords = x2_cords;
			
			for(auto it_x=x_cords.begin();it_x!=x_cords.end();++it_x){
				Vector3 v(*it_x,*it_y,*it_z);
				list<Tetrahedral> four_tetras = find_tetrahedral(v,reso);

				assert(four_tetras.size()==6);

				for(int i=0;i<6;++i){
					Tetrahedral te = four_tetras.front();
					if(is_tetra_inside(te,bbox)){
						list<Vector3> vert_intersect = te.get_vertices(evaluate_surface(te),reso);
						if(!vert_intersect.empty())
							(*vertices).push_back(vert_intersect);
					}
					four_tetras.pop_front();
				}
			}
			x2=!x2;
		}
		x1=!x1;
	}
	return;
}




bool is_tetra_inside(Tetrahedral tetra, AxisAlignedBox3 bbox){
	assert(bbox.isNull()!=true);

	list<Vector3> points = tetra.get_sample_points();
	bool is_inside=false;

	assert(points.size()==4);

	for(auto it_pt= points.begin();it_pt!=points.end();++it_pt)
		is_inside = is_inside || bbox.contains(*it_pt);

	return is_inside;
}
