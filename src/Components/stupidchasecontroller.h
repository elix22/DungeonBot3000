#pragma once

// Stupid chase controller

#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Navigation/CrowdAgent.h>

#include "enemyai.h"
#include "../playerdata.h"

using namespace Urho3D;

float rollf(float,float);

class CombatActionState;

class StupidChaseController : public EnemyAI
{
	URHO3D_OBJECT(StupidChaseController, EnemyAI);

	public:
	static void RegisterObject(Context *context)
	{
		context->RegisterFactory<StupidChaseController>("Logic");
	}

	StupidChaseController(Context *context) : EnemyAI(context)
	{
	}

	virtual CombatActionState *Callback(CombatActionState *state) override
	{
		if(state==&g_enemyidle)
		{
			return &g_enemychase;
		}

		if(state==&g_enemychase)
		{
			auto pd = GetSubsystem<PlayerData>();
			auto playerpos = pd->GetPlayerNode()->GetWorldPosition();
			Vector3 delta = playerpos - node_->GetWorldPosition();
			if(delta.Length() < 4)
			{
				return &g_enemykick;
			}
		}
		return nullptr;
	}
};
