#include<iostream>
#include "DGP/Vector3.hpp"
#include "DGP/Common.hpp"
#include"DGP/AxisAlignedBox3.hpp"
#include "Tetrahedral.hpp"
#include"Surfacing.hpp"
#include"Auxiliary_functions.hpp"
#include <list>
#include<algorithm>//lexicographical_compare

using std::cout; using std::cin; using std::endl;
using std::lexicographical_compare;
using std::sort;

// This main function is for testing my marcing tetrahedral function
int main(){
	// Testing the tetrahedral object
	Vector3 v1(0.0,0.0,0.0);
	Vector3 v2(1.0,0.0,0.0);
	Vector3 v3(0.0,1.0,0.0);
	Vector3 v4(0.0,0.0,1.0);	
	list<Vector3> verts1;
	verts1.push_back(v1);
	verts1.push_back(v2);
	verts1.push_back(v3);
	verts1.push_back(v4);
	Tetrahedral try_tetra(verts1);
	
	try_tetra.print_tetra();
	list<Vector3> vert_list = try_tetra.get_sample_points();
	cout<< "Printing the tetrahedral vertices"<<endl;
	for(auto it_vert=vert_list.begin();it_vert!=vert_list.end();++it_vert)
		cout<<*it_vert<<endl;
	list<float> surf_vals;
	surf_vals.push_back(-2.0);
	surf_vals.push_back(-3.0);
	surf_vals.push_back(4.0);
	surf_vals.push_back(5.0);
	list<Vector3> vert2_list = try_tetra.get_vertices(surf_vals,0.0);
	cout<<"Printing the vertices where iso surface intersects"<<endl;
	for(auto it_vert=vert2_list.begin();it_vert!=vert2_list.end();++it_vert)
		cout<<*it_vert<<endl;	

	//Testing is_inside function	
	Vector3 lo(-6.0,-6.0,-6.0);
	Vector3 hi(6.0,6.0,6.0);
	AxisAlignedBox3 bb(lo,hi);
	cout<<"The tetrahedral";
	try_tetra.print_tetra();
	cout<<" is inside="<<is_tetra_inside(try_tetra,bb)<<"\n"<<bb.getLow()<<bb.getHigh()<<endl;	

	// Testing the find_tetrahedral function
	float reso = 0.2;
	list<Tetrahedral> two_tetras = find_tetrahedral(lo,reso);
	(two_tetras.front()).print_tetra();
	(two_tetras.back()).print_tetra();

	//Testing the find_grid function
	vector<unsigned int> no_planes(3,0);

	find_grid(bb,reso,&no_planes);
	cout<< "The number of planes in the x, y and z dimensions are "<< no_planes[0]<<" ,"<< no_planes[1]<<" ,"<< no_planes[2]<<endl;

	//Testing create_iterator function
	vector<float> v;
	vector<vector<float>> grid_lines(4,v);

	create_iterator(bb,reso,no_planes,&grid_lines);
	
	cout<<"Grid lines for x1: ";
	for(auto it = grid_lines[0].begin();it!=grid_lines[0].end();++it)
		cout<<*it<<",";
	cout<<"\n"<<endl;
	cout<<"Grid lines for x2: ";
	for(auto it = grid_lines[1].begin();it!=grid_lines[1].end();++it)
		cout<<*it<<",";
	cout<<"\n"<<endl;
	cout<<"Grid lines for y: ";
	for(auto it = grid_lines[2].begin();it!=grid_lines[2].end();++it)
		cout<<*it<<",";
	cout<<"\n"<<endl;
	cout<<"Grid lines for z: ";
	for(auto it = grid_lines[3].begin();it!=grid_lines[3].end();++it)
		cout<<*it<<",";
	cout<<endl;

	//Testing the iterate_all function
	//iterate_all(&grid_lines,reso,bb);

	//Testing the iterate_all function after adding the vertices functionality
	list<list<Vector3>> vertices;
	iterate_all(&grid_lines,reso,bb,&vertices);

	//Testing the less_than function
	// float a1 = 4.9;
	// float a2 = 5.0;
	// cout<<"The statement that "<<a1<<" is less that "<<a2<<" is "<<less_than(a1,a2)<<endl;

	//testing the lexicographical compare function
	// Vector3 p1(-3.4,4.4,10.5);
	// Vector3 p2(-3.5,5.4,6.5);

	// cout << std::boolalpha;
	// cout<< "Comparing the two points "<< p1<< " and "<<p2<<" for less than using lexicographical compare results in ";
	// cout<< lexicographical_compare(p1.begin(),p1.end(),p2.begin(),p2.end(),less_than)<<std::noboolalpha<<endl;

	//testing the sorting function
	// dont need to sort and all, abandoning this
	// sort(verts1.begin(),verts1.end(),compare_points);
	// cout<< "Printing the sorted vertices"<<endl;
	// for(auto it=verts1.begin();it!=verts1.begin();++it)
	// 	cout<<*it<<" ,";
	// cout<<endl;

	save_mesh(&vertices,"sphere.off");

	return 0;
}
