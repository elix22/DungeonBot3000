#include "scenetools.h"

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Engine/Console.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Core/Timer.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Container/Str.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/AnimatedModel.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/Resource/Image.h>
#include <Urho3D/Navigation/DynamicNavigationMesh.h>
#include <Urho3D/Navigation/CrowdManager.h>
#include <Urho3D/Navigation/Navigable.h>
#include <Urho3D/Graphics/DebugRenderer.h>


#include "lightingcamera.h"

SharedPtr<Scene> CreateLevel(Context *context, String levelpath, unsigned int level)
{
	SharedPtr<Scene> scene(new Scene(context));
	scene->CreateComponent<Octree>();
	auto dbg=scene->CreateComponent<DebugRenderer>();
	auto nav=scene->CreateComponent<DynamicNavigationMesh>();
	scene->CreateComponent<Navigable>();
	scene->CreateComponent<CrowdManager>();

	nav->SetAgentHeight(1.0);
	nav->SetAgentRadius(2.0f);
	nav->SetAgentMaxClimb(0.01);
	nav->SetCellSize(1.0);
	nav->SetCellHeight(0.5);
	nav->SetTileSize(64);

	LoadLightingAndCamera(scene, levelpath);
	return scene;
}
