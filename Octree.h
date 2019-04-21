#include "nodeOctree.h"
#include <GL/glut.h>

class Octree
{
public:
	Octree(pointOctree,pointOctree,pointOctree,int);
	bool insertar(pointOctree);
	bool buscar(pointOctree, nodeOctree*&);
	nodeOctree *root;
	int maxPoints;
	void division(nodeOctree*&);
	void dibujar();
	void _dibujar(nodeOctree*);
	~Octree();
};
