#pragma once

// Vitals component
// Handle life

#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Scene/Node.h>

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/LogicComponent.h>

#include "../stats.h"
#include "../combat.h"

#include <unordered_map>
#include <list>

using namespace Urho3D;

struct BurnDoT
{
	double ttl_;
	double counter_;
	double dps_;
	WeakPtr<Node> owner_;
	//StatSetCollectionSnapshot ownerstats_;
};

struct HealHoT
{
	double ttl_;
	double counter_;
	double hps_;
	//StatSetCollectionSnapshot ownerstats_;
};

class BaseVitals : public LogicComponent
{
	URHO3D_OBJECT(BaseVitals, LogicComponent);
	public:
	static void RegisterObject(Context *context);
	BaseVitals(Context *context);

	virtual const StatSetCollection &GetVitalStats() const=0;
	double GetCurrentLife();
	double GetMaximumLife();
	//void ApplyDamageList(Node *attackernode, const StatSetCollection &attackerstats, const DamageValueList &dmg);
	void ApplyDamageList(BaseVitals *attackervitals, const StatSetCollection &attackerstats, const DamageValueList &dmg, bool reflectable=true);
	void ApplyHealing(double h);
	void ApplyHoT(double h, double ttl);

	protected:
	double currentlife_, maximumlife_;

	//std::unordered_map<unsigned int, BurnDoT> dots_;
	std::list<BurnDoT> dots_;
	std::list<HealHoT> hots_;

	virtual void Update(float dt) override;
	virtual void DelayedStart() override;
	void UpdateDoTs(float dt);
	void UpdateHoTs(float dt);
};

class PlayerVitals : public BaseVitals
{
	URHO3D_OBJECT(PlayerVitals, BaseVitals);
	public:
	static void RegisterObject(Context *context);
	PlayerVitals(Context *context);

	double GetEnergy();
	virtual const StatSetCollection &GetVitalStats() const override;

	protected:
	virtual void Update(float dt) override;
};


// Enemy vitals work differently, in that they own the StatSets for the enemy.
// Base stat set, buffs/debuffs, and skill stat sets.
// Skill stat sets are derived from elsewhere, a thing for later.

class EnemyVitals : public BaseVitals
{
	URHO3D_OBJECT(EnemyVitals, BaseVitals);
	public:
	static void RegisterObject(Context *context);
	EnemyVitals(Context *context);

	void SetBaseStatsFilename(const String &filename);
	const String GetBaseStatsFilename() const;
	void SetLevel(unsigned int level);

	virtual const StatSetCollection &GetVitalStats() const override {return basestatscollection_;}

	StatSet &GetBaseStats(){return basestats_;}

	protected:
	StatSet basestats_;
	StatSetCollection basestatscollection_;
	String basestatsfilename_;
};
