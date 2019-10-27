#include "Mesh.h"

using namespace std;

void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces

	// Add your code here.
	FILE *file = fopen(filename, "r");
	if (file==NULL)
	{
		printf("load Error,can't open the file:%s\n",filename);
		return;
	}
	char flag; 
	while (fscanf(file,"%c", &flag)!=EOF)
	{
		if (flag=='v')
		{
			float x, y, z;
			fscanf(file, "%f %f %f",&x,&y,&z);
			Vector3f v(x, y, z);
			bindVertices.push_back(v);
		}
		if (flag=='f')
		{
			int a, b, c;
			fscanf(file, "%d %d %d", &a, &b, &c);
			Tuple3u f(a, b, c);
			faces.push_back(f);
		}
	}
	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;
}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".
	glBegin(GL_TRIANGLES);
	for each (Tuple3u face in faces)
	{
		//printf("face:%d %d %d\n", face[0], face[1], face[2]);
		Vector3f v1 = currentVertices[face[0] - 1];
		Vector3f v2 = currentVertices[face[1] - 1];
		Vector3f v3 = currentVertices[face[2] - 1];
		Vector3f normal = Vector3f::cross((v2 - v1),(v3 - v2));
		glNormal3fv(normal);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
	}
	glEnd();
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("loadAttachments Error,can't open the file:%s\n", filename);
		return;
	}
	float attach;
	while (fscanf(file,"%f",&attach)!=EOF)
	{
		std::vector<float> row;
		row.push_back(attach);
		for (size_t i = 0; i < 16; i++)
		{
			if (fscanf(file, "%f", &attach) != EOF)
			{
				row.push_back(attach);
			}
		}
		attachments.push_back(row);
	}
}
