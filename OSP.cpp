#include <Urho3D/Physics/CollisionShape.h>

#include "OSP.h"



AstronomicalBody::AstronomicalBody(Context* context) : LogicComponent(context) {
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



OspPart::OspPart(Context* context) : LogicComponent(context) {
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void OspPart::RegisterObject(Context* context) {

    context->RegisterFactory<OspPart>();

}

void OspPart::FixedUpdate(float timeStep) {
    RigidBody* a = static_cast<RigidBody*>(node_->GetComponent("RigidBody"));
    Vector3 planetPos = node_->GetScene()->GetChild("Planet")->GetPosition();
    // Gravity equation, probably not very precise and efficient here

    // Try getting 9.8 at the surface
    // Planet radius: 3000;
    // 9.8 = something / 3000^2     --ignore gravitational constant and mass for now
    // something = 9.8 * 3000^2
    // something = 88200000         --divide by G to get mass o

    float moon = 88200000;
    Vector3 gravity = (planetPos - node_->GetPosition());
    float r = gravity.Length();
    //gravity.x_ = moon / (gravity.x_ * gravity.x_);
    //gravity.y_ = moon / (gravity.y_ * gravity.y_);
    //gravity.z_ = moon / (gravity.z_ * gravity.z_);
    gravity = gravity / r;
    gravity *= moon / (r * r);
    printf("gravity: (%f, %f, %f)\n", gravity.x_, gravity.y_, gravity.z_);
    a->SetGravityOverride(gravity);
}

