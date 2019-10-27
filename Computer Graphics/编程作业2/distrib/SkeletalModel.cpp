#include "SkeletalModel.h"

#include <FL/Fl.H>

using namespace std;

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
	loadSkeleton(skeletonFile);

	m_mesh.load(meshFile);
	m_mesh.loadAttachments(attachmentsFile, m_joints.size());

	computeBindWorldToJointTransforms();
	updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
	// draw() gets called whenever a redraw is required
	// (after an update() occurs, when the camera moves, the window is resized, etc)

	m_matrixStack.clear();
	m_matrixStack.push(cameraMatrix);

	if( skeletonVisible )
	{
		drawJoints();

		drawSkeleton();
	}
	else
	{
		// Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
		glLoadMatrixf(m_matrixStack.top());

		// Tell the mesh to draw itself.
		m_mesh.draw();
	}
}

void SkeletalModel::loadSkeleton( const char* filename )
{
	// Load the skeleton from file here.
	FILE *file = fopen(filename, "r");
	if (file==NULL)
	{
		printf("loadSkeleton Error,can't open the file:%s\n",filename);
		return;
	}
	float x, y, z;
	int parent;
	while (fscanf(file,"%f %f %f %d", &x, &y, &z,&parent)!=EOF)
	{
		//printf("%f %f %f %f\n", x, y, z, parent);
		Joint *joint = new Joint;
		joint->transform = Matrix4f::translation(x, y, z);
		if (parent==-1)
		{
			m_rootJoint = joint;
		}
		else
		{
			m_joints[parent]->children.push_back(joint);
		}
		m_joints.push_back(joint);
	}
	fclose(file);
}

void SkeletalModel::drawJoints( )
{
	// Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
	//
	// We recommend using glutSolidSphere( 0.025f, 12, 12 )
	// to draw a sphere of reasonable size.
	//
	// You are *not* permitted to use the OpenGL matrix stack commands
	// (glPushMatrix, glPopMatrix, glMultMatrix).
	// You should use your MatrixStack class
	// and use glLoadMatrix() before your drawing call.
	//MatrixStack *stack = new MatrixStack();
	this->dfsJoint(m_rootJoint, &m_matrixStack);
}

void SkeletalModel::dfsJoint(Joint *joint, MatrixStack *stack) {
	stack->push(joint->transform);
	//stack->top().print();
	glLoadMatrixf(stack->top());
	glutSolidSphere(0.025f, 12, 12);
 	for each (Joint* child in joint->children)
 	{
 		this->dfsJoint(child, stack);
 	}
	stack->pop();
}

void SkeletalModel::drawSkeleton( )
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
	dfsSkeleton(m_rootJoint, &m_matrixStack);
}

void SkeletalModel::dfsSkeleton(Joint *joint, MatrixStack *stack) {
	stack->push(joint->transform);
	for each (Joint* child in joint->children)
	{
		dfsSkeleton(child, stack);
		//stack->push(child->transform);

		//translate
		Matrix4f translate = Matrix4f::translation(0, 0, 0.5);
		//scale
		float l = child->transform.getCol(3).xyz().abs();
		Matrix4f scale = Matrix4f::scaling(0.05f, 0.05f, l);
		//RotateZ
		Vector3f offsetParent = child->transform.getCol(3).xyz();
		Vector3f z = offsetParent.normalized();
		Vector3f rnd(0, 0, 1);
		Vector3f y = Vector3f::cross(z, rnd).normalized();
		Vector3f x = Vector3f::cross(y, z).normalized();
		Matrix4f rotate = Matrix4f::rotation(Quat4f::fromRotationMatrix(Matrix3f(x, y, z)));
		//rotate.print();
		//stack->push(rotate);
		//stack->push(scale);
		//stack->push(translate);
		stack->push(rotate*scale*translate);
		glLoadMatrixf(stack->top());
		glutSolidCube(1.0f);
		stack->pop();
		//stack->pop();
		//stack->pop();
		//stack->pop();
	}
	stack->pop();
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
	Matrix4f X = Matrix4f::rotateX(rX);
	Matrix4f Y = Matrix4f::rotateY(rY);
	Matrix4f Z = Matrix4f::rotateZ(rZ);
	Matrix4f all = X * Y * Z;
	all.setCol(3, m_joints[jointIndex]->transform.getCol(3));
	m_joints[jointIndex]->transform = all;
}

void SkeletalModel::computeBindWorldToJointTransforms()
{
	// 2.3.1. Implement this method to compute a per-joint transform from
	// world-space to joint space in the BIND POSE.
	//
	// Note that this needs to be computed only once since there is only
	// a single bind pose.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
	MatrixStack *stack = new MatrixStack;
	dfscomputeBindWorldToJointTransforms(m_rootJoint, stack);
	delete stack;
}

void SkeletalModel::dfscomputeBindWorldToJointTransforms(Joint *joint, MatrixStack *stack)
{
	stack->push(joint->transform);
	joint->bindWorldToJointTransform = stack->top().inverse();
	for each (Joint *child in joint->children)
	{
		dfscomputeBindWorldToJointTransforms(child, stack);
	}
	stack->pop();
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
	// 2.3.2. Implement this method to compute a per-joint transform from
	// joint space to world space in the CURRENT POSE.
	//
	// The current pose is defined by the rotations you've applied to the
	// joints and hence needs to be *updated* every time the joint angles change.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.
	MatrixStack *stack = new MatrixStack;
	dfsupdateCurrentJointToWorldTransforms(m_rootJoint, stack);
	delete stack;
}

void SkeletalModel::dfsupdateCurrentJointToWorldTransforms(Joint *joint, MatrixStack *stack)
{
	stack->push(joint->transform);
	joint->currentJointToWorldTransform = stack->top();
	for each (Joint *child in joint->children)
	{
		dfsupdateCurrentJointToWorldTransforms(child, stack);
	}
	stack->pop();
}

void SkeletalModel::updateMesh()
{
	// 2.3.2. This is the core of SSD.
	// Implement this method to update the vertices of the mesh
	// given the current state of the skeleton.
	// You will need both the bind pose world --> joint transforms.
	// and the current joint --> world transforms.
	m_mesh.currentVertices.clear();
	for (size_t i = 0; i < m_mesh.bindVertices.size(); i++)
	{
		Vector4f newV=Vector4f();
		for (size_t j = 0; j < m_mesh.attachments[i].size(); j++)
		{
			//±ä»»¾ØÕó
			Matrix4f transform = m_joints[j+1]->currentJointToWorldTransform*m_joints[j+1]->bindWorldToJointTransform;
			newV = newV + (m_mesh.attachments[i][j] * (transform*Vector4f(m_mesh.bindVertices[i],1.0f)));
		}
		m_mesh.currentVertices.push_back(newV.xyz());
	}
}

