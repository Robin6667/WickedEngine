#pragma once
#include "CommonInclude.h"

#include <vector>

namespace wiSceneComponents
{
	struct Mesh;
	struct Object;
}

class PHYSICS
{
public:
	struct PhysicsTransform{
		XMFLOAT4 rotation;
		XMFLOAT3 position;
		PhysicsTransform(){
			rotation=XMFLOAT4(0,0,0,1);
			position=XMFLOAT3(0,0,0);
		}
		PhysicsTransform(const XMFLOAT4& newRot, const XMFLOAT3& newPos){
			rotation=newRot;
			position=newPos;
		}
	};
	static int softBodyIterationCount;
	static bool rigidBodyPhysicsEnabled, softBodyPhysicsEnabled;
protected:
	std::vector<PhysicsTransform*> transforms;
	bool firstRunWorld;
	int registeredObjects;
public:
	void FirstRunWorld(){firstRunWorld=true;}
	void NextRunWorld(){firstRunWorld=false;}
	int getObjectCount(){return registeredObjects+1;}

	virtual void Update(float dt)=0;
	virtual void MarkForRead()=0;
	virtual void UnMarkForRead()=0;
	virtual void MarkForWrite()=0;
	virtual void UnMarkForWrite()=0;
	virtual void ClearWorld()=0;
	virtual void CleanUp()=0;

	virtual void addWind(const XMFLOAT3& wind)=0;
	
	virtual void addBox(const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1, bool kinematic=false)=0;
	virtual void addSphere(float rad, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1, bool kinematic=false)=0;
	virtual void addCapsule(float rad, float hei, const XMFLOAT4& rot, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1, bool kinematic=false)=0;
	virtual void addConvexHull(const std::vector<XMFLOAT4>& vertices, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1, bool kinematic=false)=0;
	virtual void addTriangleMesh(const std::vector<XMFLOAT4>& vertices, const std::vector<unsigned int>& indices, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1, bool kinematic=false)=0;

	
	virtual void addSoftBodyTriangleMesh(const wiSceneComponents::Mesh* mesh, const XMFLOAT3& sca, const XMFLOAT4& rot, const XMFLOAT3& pos
		, float newMass=1, float newFriction=1, float newRestitution=1, float newDamping=1)=0;
	
	virtual void connectVerticesToSoftBody(wiSceneComponents::Mesh* const mesh, int objectI)=0;
	virtual void connectSoftBodyToVertices(const wiSceneComponents::Mesh* const mesh, int objectI)=0;
	virtual void transformBody(const XMFLOAT4& rot, const XMFLOAT3& pos, int objectI)=0;

	virtual PhysicsTransform* getObject(int index)=0;

	// add object to the simulation
	virtual void registerObject(wiSceneComponents::Object* object) = 0;
	// remove object from simulation
	virtual void removeObject(wiSceneComponents::Object* object) = 0;
};
