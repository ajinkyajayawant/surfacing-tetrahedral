# Introduction
Marching tetrahedral algorithm [2] was used for creating iso-surface for the object represented using radial basis functions.

# Salient points of the implementation
* Vertex clustering is not implemented, to keep things simple. So the regularization part from [2] is left out.
* Marching squares [1] was not preferable because of multiple ambiguities.
* Right now it is $N^3$ order algorithm, as iterations are done over the volume. Iterations need to be done only at the surface to get a $N^2$ order algorithm.
* Only a single loop over a grid on the bounding box is needed to determine the mesh vertices and faces. Memory complexity is $O(1)$ apart from the memory used for storing the mesh vertices.

# Libraries used
* Code was written in C++ with the help of digital geometry processing [library](https://github.com/sidch/DGP) provided by Siddhartha.

# References
[1] William E Lorensen and Harvey E Cline. Marching cubes: A high resolution 3d
surface construction algorithm. In ACM siggraph computer graphics, volume 21,
pages 163–169. ACM, 1987.

[2] Graham M Treece, Richard W Prager, and Andrew H Gee. Regularised marching
tetrahedra: improved iso-surface extraction. Computers & Graphics, 23(4):583–598,
1999.
