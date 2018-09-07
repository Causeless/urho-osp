#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/RigidBody.h>

#include "OSP.h"



AstronomicalBody::AstronomicalBody(Context* context) : Sattelite(context) {
    SetUpdateEventMask(USE_FIXEDUPDATE);

}

void AstronomicalBody::RegisterObject(Context* context) {

    context->RegisterFactory<AstronomicalBody>("AstronomicalBody");

}

void AstronomicalBody::FixedUpdate(float timeStep) {
    if (planet_.IsReady()) {
        Vector3 dir(GetScene()->GetChild("Camera")->GetPosition() - GetScene()->GetChild("planet")->GetPosition());
        float dist = dir.Length();
        dir /= dist;
        planet_.Update(dist, dir);
    }
}

void AstronomicalBody::Initialize(Context* context, double size) {
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    planet_.Initialize(context, size, GetScene(), cache);
    node_->SetPosition(Vector3(0,-size / 2, 0));
    node_->SetScale(Vector3(size / 2,size / 2,size / 2));
    collider_ = node_->CreateComponent<RigidBody>();
    CollisionShape* sphere = node_->CreateComponent<CollisionShape>();
    //sphere->SetSphere(size / 2);
    sphere->SetSphere(2);
    //collider_->SetMass(1.0f);
    collider_->SetFriction(0.75f);

}



Entity::Entity(Context* context) : Sattelite(context) {
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void Entity::RegisterObject(Context* context) {

    context->RegisterFactory<Entity>();

}

void Entity::FixedUpdate(float timeStep) {
    //RigidBody* a = static_cast<RigidBody*>(node_->GetComponent("RigidBody"));
    //Vector3 planetPos = node_->GetScene()->GetChild("Planet")->GetPosition();
    // Gravity equation, probably not very precise and efficient here

    //float moon = 88200000;
    //Vector3 gravity = (planetPos - node_->GetPosition());
    //float r = gravity.Length();
    //gravity = gravity / r;
    //gravity *= moon / (r * r);
    //printf("gravity: (%f, %f, %f)\n", gravity.x_, gravity.y_, gravity.z_);
    //a->SetGravityOverride(gravity);
    //printf("AAAA\n");

}

SystemOsp::SystemOsp(Context* context) : Object(context)
{
    m_hiddenScene = new Scene(context);
    m_hiddenScene->SetUpdateEnabled(false);
    m_hiddenScene->SetEnabled(false);
    // Parts holds
    m_parts = m_hiddenScene->CreateChild("Parts");
    Node* category = m_parts->CreateChild("dbg");
    category->SetVar("DisplayName", "Debug Parts");
    for (uint i = 0; i < 20; i ++)
    {
        Node* aPart = category->CreateChild("dbg_" + String(i));
        aPart->SetVar("Country", "Canarda");
        aPart->SetVar("Description", "A simple oddly shaped cube");
        aPart->SetVar("Manufacturer", "Gotzietec Industries");
        aPart->SetVar("DisplayName", "Cube "  + String(i));
        aPart->SetScale(0.05f * (i + 1));
        aPart->SetEnabled(false);

        StaticModel* model = aPart->CreateComponent<StaticModel>();
        model->SetCastShadows(true);
        model->SetModel(GetSubsystem<ResourceCache>()->GetResource<Model>("Models/Box.mdl"));

        RigidBody* rb = aPart->CreateComponent<RigidBody>();
        rb->SetMass(0.05f * (i + 1));
        rb->SetEnabled(false);
        CollisionShape* shape = aPart->CreateComponent<CollisionShape>();

    }
}

void SystemOsp::make_craft(Node* node)
{
    node->CreateComponent<Entity>();
}
