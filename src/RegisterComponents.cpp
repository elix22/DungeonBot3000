#include <Urho3D/Urho3D.h>
#include "RegisterComponents.h"

#include "Components/thirdpersoncamera.h"
#include "Components/rotationsmoothing.h"
#include "Components/combatcontroller.h"
#include "Components/vitals.h"
#include "Components/lifebubbleui.h"
#include "Components/enemylifebar.h"
#include "Components/burnindicator.h"
#include "Components/enemyondeath.h"
#include "Components/timeddeath.h"
#include "Components/projectile.h"
#include "Components/areaburn.h"
#include "Components/burnpayload.h"
#include "Components/itemnametag.h"
#include "Components/dropitem.h"
#include "Components/scenefader.h"
#include "Components/enemynameplate.h"
#include "Components/hoverhandler.h"
#include "Components/enemymodifiers.h"
#include "Components/lootdrop.h"
#include "Components/levelchanger.h"
#include "Components/weaponequipper.h"
#include "Components/mobnamer.h"
#include "Components/mainmenu.h"
#include "Components/playerdeath.h"

#include "Enemies/jbadams.h"
#include "Enemies/khawk.h"

void RegisterCustomComponents(Context *context)
{
	ThirdPersonCamera::RegisterObject(context);
	CombatCameraController::RegisterObject(context);
	RotationSmoothing::RegisterObject(context);
	CombatController::RegisterObject(context);
	PlayerVitals::RegisterObject(context);
	EnemyVitals::RegisterObject(context);
	LifeBubbleUI::RegisterObject(context);
	EnemyLifeBar::RegisterObject(context);
	BurnIndicator::RegisterObject(context);
	EnemyOnDeath::RegisterObject(context);
	TimedDeath::RegisterObject(context);
	Projectile::RegisterObject(context);
	AreaBurn::RegisterObject(context);
	BurnPayload::RegisterObject(context);
	DropItemContainer::RegisterObject(context);
	ItemNameTag::RegisterObject(context);
	SceneFader::RegisterObject(context);
	EnemyNameplate::RegisterObject(context);
	HoverHandler::RegisterObject(context);
	EnemyModifiers::RegisterObject(context);
	LootDrop::RegisterObject(context);
	LevelChanger::RegisterObject(context);
	WeaponEquipper::RegisterObject(context);
	MobNamer::RegisterObject(context);
	MainMenu::RegisterObject(context);
	PlayerDeath::RegisterObject(context);

	context->RegisterFactory<CASPlayerIdle>();
	context->RegisterFactory<CASPlayerMove>();
	context->RegisterFactory<CASPlayerSpinAttack>();
	context->RegisterFactory<CASPlayerLaserBeam>();
	context->RegisterFactory<CASPlayerLoot>();
	context->RegisterFactory<CASPlayerStairs>();
	context->RegisterFactory<CASPlayerDead>();

	context->RegisterFactory<CASEnemyInactive>();
	context->RegisterFactory<CASEnemyIdle>();
	context->RegisterFactory<CASEnemyApproachTarget>();
	context->RegisterFactory<CASEnemyMovePosition>();
	context->RegisterFactory<CASEnemyKick>();
	context->RegisterFactory<CASEnemyAttack>();
	context->RegisterFactory<CASEnemyAttackPosition>();

	context->RegisterFactory<CASUserEnemyAI>();
	context->RegisterFactory<CASjbadamsEnemyAI>();
	context->RegisterFactory<CASjbadamsLeap>();

	context->RegisterFactory<CASKHawkEnemyAI>();
	context->RegisterFactory<CASKHawkEnemyShootFire>();
}
