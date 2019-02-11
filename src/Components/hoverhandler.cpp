#include "hoverhandler.h"
#include "thirdpersoncamera.h"

#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Core/StringUtils.h>
#include <Urho3D/IO/Log.h>


void HoverHandler::RegisterObject(Context *context)
{
	context->RegisterFactory<HoverHandler>();
}

HoverHandler::HoverHandler(Context *context) : LogicComponent(context)
{
	SetUpdateEventMask(USE_UPDATE);
}

String Vector3ToString(const Vector3 &vec)
{
	return String("(") + String(vec.x_) + "," + String(vec.y_) + "," + String(vec.z_) + ")";
}

void HoverHandler::Update(float dt)
{
	static PODVector<RayQueryResult> result;
	auto cam=node_->GetScene()->GetChild("Camera");
	auto scene=node_->GetScene();

	if(hovered_ && !hovered_.Expired())
	{
		Log::Write(LOG_INFO, String("Unhover: ") + String((int)hovered_->GetID()));
		VariantMap vm;
		static StringHash unhover("UnHover");
		hovered_->SendEvent(unhover,vm);
		hovered_=nullptr;
	}

	if(cam)
	{
		auto tpcam=cam->GetComponent<ThirdPersonCamera>();
		if(tpcam)
		{
			auto octree=scene->GetComponent<Octree>();
			if(octree)
			{
				Ray ray=tpcam->GetMouseRay();
				result.Clear();
				RayOctreeQuery query(result, ray, RAY_TRIANGLE, 500.0f, DRAWABLE_GEOMETRY);
				octree->Raycast(query);

				Log::Write(LOG_INFO, String("Ray: ") + Vector3ToString(ray.origin_) + String("->") + Vector3ToString(ray.direction_));
				if(result.Size()==0) return;

				for(unsigned int i=0; i<result.Size(); ++i)
				{
					Log::Write(LOG_INFO, String("distance: ") + String(result[i].distance_));
					if(result[i].distance_>=0)
					{
						//Node *n=tpcam->TopLevelNode(result[i].drawable_, scene);
						Node *n=result[i].drawable_->GetNode();
						auto pos=n->GetWorldPosition();
						Log::Write(LOG_INFO, String("pos: ") + String(pos.x_) + " " + String(pos.z_));
						bool hoverable=n->GetVar("hoverable").GetBool();
						if(hoverable)
						{
							hovered_=n;
							if(hovered_ && !hovered_.Expired())
							{
								Log::Write(LOG_INFO, String("Hover: ") + String((int)hovered_->GetID()));
								VariantMap vm;
								static StringHash hover("Hover");
								hovered_->SendEvent(hover,vm);
							}
							return;
						}
					}
				}
			}
		}
	}
}
