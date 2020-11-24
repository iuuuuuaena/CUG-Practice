#include "TimeStepper.hpp"

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> f = particleSystem->evalF(particleSystem->getState());
	vector<Vector3f> old = particleSystem->getState();
	vector<Vector3f> newState;
	for (size_t i = 0; i < old.size(); i++)
	{
		Vector3f tmp = old.at(i) + stepSize * f.at(i);
		newState.push_back(tmp);
	}
	particleSystem->setState(newState);
}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> old = particleSystem->getState();
	vector<Vector3f> f0 = particleSystem->evalF(old);
	vector<Vector3f> tryState;
	for (size_t i = 0; i < old.size(); i++)
	{
		Vector3f tmp = old.at(i) + stepSize * f0.at(i);
		tryState.push_back(tmp);
	}
	//particleSystem->setState(newState);
	vector<Vector3f> f1 = particleSystem->evalF(tryState);

	vector<Vector3f> newState;
	for (size_t i = 0; i < old.size(); i++)
	{
		Vector3f tmp = old.at(i) + stepSize / 2 * (f0.at(i) + f1.at(i));
		newState.push_back(tmp);
	}
	particleSystem->setState(newState);
}

void RK4::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> old = particleSystem->getState();
	vector<Vector3f> k1 = particleSystem->evalF(old);

	vector<Vector3f> k1State;
	for (size_t i = 0; i < old.size(); ++i) {
		k1State.push_back(old[i] + stepSize * 0.5f * k1[i]);
	}

	vector<Vector3f> k2 = particleSystem->evalF(k1State);
	vector<Vector3f> k2State;
	for (size_t i = 0; i < old.size(); ++i) {
		k2State.push_back(old[i] + stepSize * 0.5f * k2[i]);
	}

	vector<Vector3f> k3 = particleSystem->evalF(k2State);
	vector<Vector3f> k3State;
	for (size_t i = 0; i < old.size(); ++i) {
		k3State.push_back(old[i] + stepSize * 0.5f * k3[i]);
	}

	vector<Vector3f> k4 = particleSystem->evalF(k3State);

	vector<Vector3f> newState;
	for (size_t i = 0; i < old.size(); ++i) {
		Vector3f tmp=old[i] + (k1[i] + 2.0f * k2[i] + 2.0f * k3[i] + k4[i]) / 6.f * stepSize;
		newState.push_back(tmp);
	}

	particleSystem->setState(newState);
}
