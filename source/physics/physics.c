#include <3ds.h>

#include "physics/physics.h"
#include "physics/physicsThread.h"

physicsThread_s physicsThread;

void initPhysics()
{
	initOBBs();
	initAARs();

	initPhysicsThread(&physicsThread);
}

void exitPhysics()
{
	exitPhysicsThread(&physicsThread);
}

void physicsCreateObb(OBB_s** out, vect3Df_s position, vect3Df_s size, float mass, float angle)
{
	svcWaitSynchronization(physicsThread.requestMutex, U64_MAX);
	queueRequest(&physicsThread.requestList, createRequestCreateObb(out, position, size, mass, angle));
	svcReleaseMutex(physicsThread.requestMutex);
}

void physicsCreateAar(AAR_s** out, vect3Df_s position, vect3Df_s size, vect3Df_s normal)
{
	svcWaitSynchronization(physicsThread.requestMutex, U64_MAX);
	queueRequest(&physicsThread.requestList, createRequestCreateAar(out, position, size, normal));
	svcReleaseMutex(physicsThread.requestMutex);
}

void physicsGenerateGrid()
{
	svcWaitSynchronization(physicsThread.requestMutex, U64_MAX);
	queueRequest(&physicsThread.requestList, createRequestGenerateGrid());
	svcReleaseMutex(physicsThread.requestMutex);
}
