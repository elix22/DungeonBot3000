// Combat Controller
#pragma once

#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Navigation/CrowdAgent.h>
#include <Urho3D/Container/Vector.h>

#include "../combatactionstates.h"
#include "../playeractionstates.h"
#include "../enemyactionstates.h"

#include <Urho3D/Container/HashMap.h>

class Cooldowns
{
	public:
	Cooldowns(){}

	void SetCooldown(StringHash which, float value)
	{
		cooldowns_[which]=value;
	}

	float GetCooldown(StringHash which)
	{
		//return cooldowns_[which];
		if(cooldowns_.Find(which)==cooldowns_.End()) cooldowns_[which]=0.0f;
		return cooldowns_[which];
	}

	void Tick(float dt)
	{
		for(auto i=cooldowns_.Begin(); i!=cooldowns_.End(); ++i)
		{
			i->second_ -= dt;
		}
	}

	protected:
	HashMap<StringHash, float> cooldowns_;
};

using namespace Urho3D;

class CombatController : public LogicComponent
{
	URHO3D_OBJECT(CombatController, LogicComponent);

	public:
	static void RegisterObject(Context *context);
	CombatController(Context *context);

	void SetObjectPath(String op);
	const String GetObjectPath() const;
	void SetAnimPath(String ap);
	const String GetAnimPath() const;
	void SetAIState(String s);
	const String GetAIState() const;
	void SetStartState(String s);
	const String GetStartState() const;

	void MoveTo(Vector3 target);
	void SetPushiness(NavigationPushiness pushy);

	bool SetCombatActionState(CombatActionState *state);
	CombatActionState *GetState(StringHash type);
	template <class T> T *GetState();
	template <class T> T *GetDerivedState();

	void FaceNodeMotion(float timeStep);
	void SetCooldown(StringHash which, float value)
	{
		cooldowns_.SetCooldown(which,value);
	}

	float GetCooldown(StringHash which)
	{
		return cooldowns_.GetCooldown(which);
	}

	protected:
	virtual void Update(float dt) override;
	virtual void DelayedStart() override;
	void HandleCrowdAgentReposition(StringHash eventType, VariantMap &eventData);
	void HandleAnimationTrigger(StringHash eventType, VariantMap &eventData);

	CombatActionState *currentstate_, *nextstate_;
	Vector<SharedPtr<CombatActionState>> states_;

	String objectpath_, animpath_;
	String aistate_, startstate_;

	Cooldowns cooldowns_;
};

template <class T> T *CombatController::GetState(){return static_cast<T*>(GetState(T::GetTypeStatic()));}
template <class T> T* CombatController::GetDerivedState()
{
    for (Vector<SharedPtr<CombatActionState> >::ConstIterator i = states_.Begin(); i != states_.End(); ++i)
    {
        auto* state = dynamic_cast<T*>(i->Get());
        if (state)
            return state;
    }
	Log::Write(LOG_ERROR, String("Error: controller does not have state derived from ") + T::GetTypeNameStatic());
	return nullptr;
}

