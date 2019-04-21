#include "Octree.h"



Octree::Octree(pointOctree _x, pointOctree _y, pointOctree _z, int pointNumero)
{
	root = new nodeOctree(_x, _y, _z);
	maxPoints = pointNumero;
}

bool Octree::buscar(pointOctree point, nodeOctree*& P)
{
	int lehijo;
	P = root;
	double medioX, medioY, medioZ;
	medioX = (P->valuesX.coords[0] + P->valuesX.coords[1]) / 2;
	medioY = (P->valuesY.coords[0] + P->valuesY.coords[1]) / 2;
	medioZ = (P->valuesZ.coords[0] + P->valuesZ.coords[1]) / 2;

	for (P = root; P->hoja != true; P = P->hijos[lehijo])
	{
		if (point.coords[0] > medioX)
		{
			if (point.coords[1] > medioY)
			{
				if (point.coords[2] > medioZ)
				{
					lehijo = 1;
				}
				else
				{
					lehijo = 5;
				}
			}

			else if (point.coords[2] > medioZ)
			{
				lehijo = 3;
			}
			else
			{
				lehijo = 7;
			}

		}
		else if (point.coords[1] > medioY)
		{
			if (point.coords[2] > medioZ)
			{
				lehijo = 0;
			}
			else
			{
				lehijo = 4;
			}
		}
		else if (point.coords[2] > medioZ)
		{
			lehijo = 2;
		}
		else
		{
			lehijo = 6;
		}

	}

	for (int i = 0; i < P->vectorPuntos.size(); i++)
	{
		if (P->vectorPuntos[i].coords[0] == point.coords[0] and P->vectorPuntos[i].coords[1] == point.coords[1] and P->vectorPuntos[i].coords[2] == point.coords[2])
		{
			return 1;
		}
	}

	return 0;


}

bool Octree::insertar(pointOctree point)
{
	nodeOctree *P;
	if (buscar(point, P))
	{
		return 0;
	}
	P->vectorPuntos.push_back(point);
	if (P->vectorPuntos.size() > maxPoints)
	{
		division(P);
	}

	return 1;
}

void Octree::division(nodeOctree*& P)
{
	int lehijo;
	P->hoja = false;
	double medioX, medioY, medioZ;
	medioX = (P->valuesX.coords[0] + P->valuesX.coords[1]) / 2;
	medioY = (P->valuesY.coords[0] + P->valuesY.coords[1]) / 2;
	medioZ = (P->valuesZ.coords[0] + P->valuesZ.coords[1]) / 2;

	//inicializacion de los hijos
	P->hijos[0] = new nodeOctree(pointOctree(P->valuesX.coords[0], medioX), pointOctree(medioY, P->valuesY.coords[1]), pointOctree(P->valuesZ.coords[0], medioZ));
	P->hijos[1] = new nodeOctree(pointOctree(medioX, P->valuesX.coords[1]), pointOctree(medioY, P->valuesY.coords[1]), pointOctree(P->valuesZ.coords[0], medioZ));
	P->hijos[2] = new nodeOctree(pointOctree(P->valuesX.coords[0], medioX), pointOctree(P->valuesY.coords[0], medioY), pointOctree(P->valuesZ.coords[0], medioZ));
	P->hijos[3] = new nodeOctree(pointOctree(medioX, P->valuesX.coords[1]), pointOctree(P->valuesY.coords[0], medioY), pointOctree(P->valuesZ.coords[0], medioZ));
	P->hijos[4] = new nodeOctree(pointOctree(P->valuesX.coords[0], medioX), pointOctree(medioY, P->valuesY.coords[1]), pointOctree(medioZ, P->valuesZ.coords[1]));
	P->hijos[5] = new nodeOctree(pointOctree(medioX, P->valuesX.coords[1]), pointOctree(medioY, P->valuesY.coords[1]), pointOctree(medioZ, P->valuesZ.coords[1]));
	P->hijos[6] = new nodeOctree(pointOctree(P->valuesX.coords[0], medioX), pointOctree(P->valuesY.coords[0], medioY), pointOctree(medioZ, P->valuesZ.coords[1]));
	P->hijos[7] = new nodeOctree(pointOctree(medioX, P->valuesX.coords[1]), pointOctree(P->valuesY.coords[0], medioY), pointOctree(medioZ, P->valuesZ.coords[1]));

	//asignacion de puntos en los hijos
	for (int i = 0; i < P->vectorPuntos.size(); i++)
	{
		if (P->vectorPuntos[i].coords[0] > medioX)
		{
			if (P->vectorPuntos[i].coords[1] > medioY)
			{
				if (P->vectorPuntos[i].coords[2] > medioZ)
				{
					lehijo = 1;
				}
				else
				{
					lehijo = 5;
				}
			}
			else if (P->vectorPuntos[i].coords[2] > medioZ)
			{
				lehijo = 3;
			}
			else
			{
				lehijo = 7;
			}
		}
		else if (P->vectorPuntos[i].coords[1] > medioY)
		{
			if (P->vectorPuntos[i].coords[2] > medioZ)
			{
				lehijo = 0;
			}
			else
			{
				lehijo = 4;
			}
		}
		else if (P->vectorPuntos[i].coords[2] > medioZ)
		{
			lehijo = 2;
		}
		else
		{
			lehijo = 6;
		}

		P->hijos[lehijo]->vectorPuntos.push_back(P->vectorPuntos[i]);
	}

	P->vectorPuntos.clear(); //limpieza del vector de puntos del nodo dividido 


	//si se sobrecarga de puntos otra vez un mismo nodo
	for (int j = 0; j < 8; j++)
	{
		if (P->vectorPuntos.size() > maxPoints)
		{
			division(P->hijos[j]);
			break;
		}
	}
	
}

void Octree::dibujar()
{
	nodeOctree *P = root;
	if (P->hoja)
	{
		for (int i = 0; i < P->vectorPuntos.size(); i++)
		{
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glColor3d(255, 255, 0);
			glVertex3d(P->vectorPuntos[i].coords[0], P->vectorPuntos[i].coords[1], P->vectorPuntos[i].coords[2]);
			glEnd();
		}

		glBegin(GL_LINES);
		//lineas horizontales
		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[0]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[0]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[1]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[1]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[1]);

		//lineas verticales
		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[0]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[0]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[1]);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[1]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[1]);

		//lineas diagonales
		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], P->valuesZ.coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], P->valuesZ.coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], P->valuesZ.coords[1]);

		glColor3d(255, 0, 0);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[0]);
		glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], P->valuesZ.coords[1]);

		glEnd();

	}
}

void Octree::_dibujar(nodeOctree *P)
{
	if (P->hoja)
	{
		for (int i = 0; i < P->vectorPuntos.size(); i++)
		{
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glColor3d(255, 0, 0);
			glVertex3d(P->vectorPuntos[i].coords[0], P->vectorPuntos[i].coords[1], P->vectorPuntos[i].coords[2]);
			glEnd();

		}
		return;
	}
	double medioX, medioY, medioZ;
	medioX = (P->valuesX.coords[0] + P->valuesX.coords[1]) / 2;
	medioY = (P->valuesY.coords[0] + P->valuesY.coords[1]) / 2;
	medioZ = (P->valuesZ.coords[0] + P->valuesZ.coords[1]) / 2;

	//lineas horizontales

	glBegin(GL_LINES);
	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], medioZ);
	glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], medioZ);
	glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], medioY, P->valuesZ.coords[0]);
	glVertex3d(P->valuesX.coords[1], medioY, P->valuesZ.coords[0]);

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], medioY, medioZ);
	glVertex3d(P->valuesX.coords[1], medioY, medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], medioY, P->valuesZ.coords[1]);
	glVertex3d(P->valuesX.coords[1], medioY, P->valuesZ.coords[1]);


	//lineas verticales

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], P->valuesY.coords[0], medioZ);
	glVertex3d(P->valuesX.coords[0], P->valuesY.coords[1], medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[1], P->valuesY.coords[0], medioZ);
	glVertex3d(P->valuesX.coords[1], P->valuesY.coords[1], medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(medioX, P->valuesY.coords[1], P->valuesZ.coords[0]);
	glVertex3d(medioX, P->valuesY.coords[0], P->valuesZ.coords[0]);
	
	glColor3d(255, 0, 0);
	glVertex3d(medioX, P->valuesY.coords[0], medioZ);
	glVertex3d(medioX, P->valuesY.coords[1], medioZ);

	glColor3d(255, 0, 0);
	glVertex3d(medioX, P->valuesY.coords[0], P->valuesZ.coords[1]);
	glVertex3d(medioX, P->valuesY.coords[1], P->valuesZ.coords[1]);

	//lineas diagonales

	glColor3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[0], medioY, P->valuesZ.coords[0]);
	glVertex3d(P->valuesX.coords[0], medioY, P->valuesZ.coords[1]);

	glVertex3d(255, 0, 0);
	glVertex3d(P->valuesX.coords[1], medioY, P->valuesZ.coords[0]);
	glVertex3d(P->valuesX.coords[1], medioY, P->valuesZ.coords[1]);

	glColor3d(255, 0, 0);
	glVertex3d(medioX, P->valuesY.coords[0], P->valuesZ.coords[0]);
	glVertex3d(medioX, P->valuesY.coords[0], P->valuesZ.coords[1]);

	glVertex3d(255, 0, 0);
	glVertex3d(medioX, P->valuesY.coords[1], P->valuesZ.coords[0]);
	glVertex3d(medioX, P->valuesY.coords[1], P->valuesZ.coords[1]);
	glEnd();

	for (int i = 0; i < 8; i++)
	{
		_dibujar(P->hijos[i]);
	}

}



Octree::~Octree()
{
}
