#pragma once

// Enemy action states
#include "combatactionstates.h"
#include "stats.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/JSONFile.h>
#include <Urho3D/Resource/JSONValue.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Model.h>

// Create a base class for enemy AI routine action states
class CASEnemyAI : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyAI, CombatActionState);
	public:
	CASEnemyAI(Context *context) : CombatActionState(context){}

};

// Create a state for enemies too far from the player
class CASEnemyInactive : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyInactive, CombatActionState);
	public:
	CASEnemyInactive(Context *context);

	virtual void End(CombatController *actor) override;
	virtual void Start(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
};

class CASEnemyIdle : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyIdle, CombatActionState);
	public:
	CASEnemyIdle(Context *context);
	virtual void End(CombatController *actor) override;
	virtual void Start(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
	virtual bool HandleAgentReposition(CombatController *actor, Vector3 velocity, float dt) override;
};

class CASEnemyApproachTarget : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyApproachTarget, CombatActionState);
	public:
	CASEnemyApproachTarget(Context *context);
	virtual void End(CombatController *actor) override;
	virtual void Start(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;

	void SetApproachDistance(float dist);
	void SetApproachState(CombatActionState *state);
	void SetApproachTarget(Node *target);
	void SetTimeout(float timeout);  // Set a time to bail out, if desired. 0 is no timeout

	protected:
	float distance_;
	WeakPtr<Node> target_;
	CombatActionState *tostate_;
	float timeout_;
	float time_;
};

class CASEnemyMovePosition : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyMovePosition, CombatActionState);
	public:
	CASEnemyMovePosition(Context *context);

	virtual void End(CombatController *actor) override;
	virtual void Start(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
	void SetApproachDistance(float dist);
	void SetApproachState(CombatActionState *state);
	void SetApproachPosition(Vector3 pos);
	void SetTimeout(float timeout);

	protected:
	float distance_;
	Vector3 target_;
	CombatActionState *tostate_;
	float timeout_;
	float time_;
};

class CASEnemyKick : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyKick, CombatActionState);
	public:
	CASEnemyKick(Context *context);
	virtual void Start(CombatController *actor) override;
	virtual void End(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
	virtual void HandleTrigger(CombatController *actor, String animname, unsigned int value) override;
};

class CASEnemyAttack : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyAttack, CombatActionState);
	public:
	CASEnemyAttack(Context *context);
	virtual void Start(CombatController *actor) override;
	virtual void End(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
	virtual void HandleTrigger(CombatController *actor, String animname, unsigned int value) override;

	void SetAnimation(const String anim);
	void SetAttackStats(CombatController *actor, const String path);

	void SetTargetNode(Node *n) {target_=n;}

	protected:
	String animation_;
	StatSet attackstats_;
	WeakPtr<Node> target_;
};

/// Assign an attack upon a set location, rather than a target node. For telegraphed slam attacks, etc... that should be dodged.
// Captures the position of target node in Start. Must specify an area as well.
class CASEnemyAttackPosition : public CombatActionState
{
	URHO3D_OBJECT(CASEnemyAttackPosition, CombatActionState);
	public:
	CASEnemyAttackPosition(Context *context);
	virtual void Start(CombatController *actor) override;
	virtual void End(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
	virtual void HandleTrigger(CombatController *actor, String animname, unsigned int value) override;
	virtual bool HandleAgentReposition(CombatController *actor, Vector3 velocity, float dt) override;

	void SetAnimation(const String anim);
	void SetAttackStats(CombatController *actor, const String path);

	void SetTargetNode(Node *n) {target_=n;}
	void SetTargetRadius(float r) { radius_=r;}

	protected:
	String animation_;
	StatSet attackstats_;

	Vector3 position_;
	float radius_;
	WeakPtr<Node> target_;

	Node* targetcircle_;
};


class CASUserEnemyAI : public CASEnemyAI
{
	URHO3D_OBJECT(CASUserEnemyAI, CASEnemyAI);
	public:
	CASUserEnemyAI(Context *context);

	virtual void Start(CombatController *actor) override;
	virtual void End(CombatController *actor) override;
	virtual CombatActionState *Update(CombatController *actor, float dt) override;
};

/*
extern CASEnemyIdle g_enemyidle;
extern CASEnemyChase g_enemychase;
extern CASEnemyKick g_enemykick;
*/
