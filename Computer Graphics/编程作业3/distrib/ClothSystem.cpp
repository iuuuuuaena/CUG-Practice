#include "ClothSystem.h"

//TODO: Initialize here
ClothSystem::ClothSystem(){}

ClothSystem::ClothSystem(int _n) {
	this->n = _n;
	m_numParticles = n * n;
	r = 0.1f;
	mass = 0.025f;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			m_vVecState.push_back(Vector3f((float)i*r, 0, (float)j * r));
			m_vVecState.push_back(Vector3f::ZERO);
		}
	}
}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	//for (size_t i = 0; i < state.size(); i++)
	//{
	//	f.push_back(Vector3f::ZERO);
	//}
	float k_resistance = 2.0f;//阻尼系数
	float k_structural = 20.f;//结构弹簧弹性系数
	float k_shear = 10.f;//抗剪弹簧弹性系数
	float k_flex = 200.f;//抗弯弹簧弹性系数
	float g = 9.8f;
	//int n = sqrt(m_numParticles);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			f.push_back(state.at(indexOf(i, j) + 1));
			//---------------------------------------
			Vector3f currentPos = state.at(indexOf(i, j));
			Vector3f gravity(0, -g*mass, 0);//重力
			Vector3f resistance = -k_resistance * state.at(indexOf(i, j) + 1);//粘性阻尼力
			Vector3f structural = Vector3f::ZERO, shear = Vector3f::ZERO, flex = Vector3f::ZERO;//三个弹簧的弹力
			Vector3f res=Vector3f::ZERO;
			//结构弹簧
			Vector3f structural_left, structural_right, structural_top, structural_bottom;
			//抗剪弹簧
			Vector3f shear_left_top, shear_left_bottom, shear_right_top, shear_right_bottom;
			//抗弯弹簧
			Vector3f flex_left, flex_right, flex_top, flex_bottom;
			//左上和右上的粒子固定
			if ((i == 0 && j == 0)||(i==n-1&&j==0)) {
				f.push_back(res);
				continue;
			}
			//结构弹簧
			if (i > 0) {
				structural_left = generateElasticity(state.at(indexOf(i - 1, j)), currentPos, k_structural,r);
			}
			if (i < n - 1) {
				structural_right = generateElasticity(state.at(indexOf(i + 1, j)), currentPos, k_structural,r);
			}
			if (j > 0) {
				structural_top = generateElasticity(state.at(indexOf(i, j - 1)), currentPos, k_structural,r);
			}
			if (j < n - 1) {
				structural_bottom = generateElasticity(state.at(indexOf(i, j + 1)), currentPos, k_structural,r);
			}
			//抗剪弹簧
			if (i > 0 && j > 0) {
				shear_left_top = generateElasticity(state.at(indexOf(i - 1, j - 1)), currentPos, k_shear, sqrt(2.f)*r);
			}
			if (i > 0 && j < n - 1) {
				shear_left_bottom = generateElasticity(state.at(indexOf(i - 1, j + 1)), currentPos, k_shear, sqrt(2.f)*r);
			}
			if (i < n - 1 && j>0) {
				shear_right_top = generateElasticity(state.at(indexOf(i + 1, j - 1)), currentPos, k_shear, sqrt(2.f)*r);
			}
			if (i < n - 1 && j < n - 1) {
				shear_right_bottom = generateElasticity(state.at(indexOf(i + 1, j + 1)), currentPos, k_shear, sqrt(2.f)*r);
			}
			//抗弯弹簧
			if (i > 1) {
				 flex_left= generateElasticity(state.at(indexOf(i - 2, j)), currentPos, k_structural, 2 * r);
			}
			if (i < n - 2) {
				flex_right = generateElasticity(state.at(indexOf(i + 2, j)), currentPos, k_structural, 2 * r);
			}
			if (j > 1) {
				flex_top = generateElasticity(state.at(indexOf(i, j - 1)), currentPos, k_structural, 2 * r);
			}
			if (j < n - 2) {
				flex_bottom = generateElasticity(state.at(indexOf(i, j + 1)), currentPos, k_structural, 2 * r);
			}
			structural = structural_left + structural_right + structural_top + structural_bottom;
			shear = shear_left_top + shear_left_bottom + shear_right_top + shear_right_bottom;
			flex = flex_left + flex_right + flex_top + flex_bottom;
			Vector3f elasticity = structural + shear + flex;
			res = gravity + resistance + elasticity;
			//res = res / mass;
			f.push_back(res);
		}
	}


	return f;
}

///TODO: render the system (ie draw the particles)
void ClothSystem::draw()
{
	//for (int i = 0; i < m_numParticles; i++) {
	//	Vector3f pos = m_vVecState.at(i * 2);//  position of particle i. YOUR CODE HERE
	//	glPushMatrix();
	//	glTranslatef(pos[0], pos[1], pos[2]);
	//	glutSolidSphere(0.05f, 10.0f, 10.0f);
	//	glPopMatrix();
	//}
	Vector3f pos = m_vVecState.at(indexOf(n - 1, 0));//  position of particle i. YOUR CODE HERE
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(0.1f, 10.0f, 10.0f);
	glPopMatrix();
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < n-1; i++)
	{
		for (size_t j = 0; j < n-1; j++)
		{
			int a1 = indexOf(i, j);
			int a2 = indexOf(i + 1, j);
			int b1 = indexOf(i, j + 1);
			int b2 = indexOf(i + 1, j + 1);
			draw(a1, b1, a2);
			draw(b1, b2, a2);
		}
	}
	glEnd();
}

void ClothSystem::draw(int i1, int i2, int i3) {
	Vector3f v1 = getState().at(i1);
	Vector3f v2 = getState().at(i2);
	Vector3f v3 = getState().at(i3);
	Vector3f normal = Vector3f::cross((v2 - v1), (v3 - v2));
	glNormal3fv(normal);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
}

int ClothSystem::indexOf(int i, int j)
{
	int n = sqrt(m_numParticles);
	return 2 * (i * n + j);
}

//v1对v2的力
Vector3f ClothSystem::generateElasticity(Vector3f v1, Vector3f v2,float k_elasticity,float _r) {
	float x = v2.x() - v1.x();
	float y = v2.y() - v1.y();
	float z = v2.z() - v1.z();
	float len = sqrt(x * x + y * y + z * z);
	float composition = -k_elasticity * (len - _r);
	Vector3f res(composition / len * x, composition / len * y, composition / len * z);
	return res;
}