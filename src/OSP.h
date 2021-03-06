#pragma once


#include <Urho3D/Container/RefCounted.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Physics/RigidBody.h>

#include "PlanetWrenderer.h"

using namespace Urho3D;

namespace osp {

class AstronomicalBody;
class PlanetTerrain;

class LongVector
{
    int64_t m_x, m_y, m_z;
    Vector3 m_fraction;
};

/**
 * @brief Base class for anything orbiting or landed on an AstronomicalBody.
 * This should contain orbital data.
 */
class Satellite : public LogicComponent
{
    URHO3D_OBJECT(Satellite, LogicComponent)

public:
    Satellite(Context* context) : LogicComponent(context) {}

    LongVector m_position;
    WeakPtr<AstronomicalBody> orbiting;

};

/**
 * @brief Base class for adding functionality to parts, like rockets
 */
class Machine : public LogicComponent
{
    URHO3D_OBJECT(Machine, LogicComponent)

public:
    Machine(Context* context) : LogicComponent(context) {}

};

/**
 * @brief Class containing data describing an astronomical body (star, planet, asteroid), and their properties (size, water level, mass)
 */
class AstronomicalBody : public Satellite
{
    URHO3D_OBJECT(AstronomicalBody, Satellite)

public:
    AstronomicalBody(Context* context);

    static void RegisterObject(Context* context);

    virtual void FixedUpdate(float timeStep);

    void Initialize(Context* context);

private:

    WeakPtr<PlanetTerrain> m_terrain;
};

/**
 * @brief Anything in the universe that has physics, like a space craft
 */
class Entity : public Satellite
{

    URHO3D_OBJECT(Entity, Satellite)

public:
    Entity(Context* context);

    static void RegisterObject(Context* context);

    virtual void FixedUpdate(float timeStep);

    Vector3 m_staticCoM;
    float m_staticMass;

//private:

};

/**
 * @brief LOD Planet terrain that could be rendered
 */
class PlanetTerrain : public StaticModel
{
    URHO3D_OBJECT(PlanetTerrain, StaticModel)

public:
    PlanetTerrain(Context* context);

    static void RegisterObject(Context* context);

    void Initialize();
    PlanetWrenderer* GetPlanet() { return &m_planet; }

private:
    bool m_first;
    PlanetWrenderer m_planet;
    WeakPtr<RigidBody> m_collider;
};


/**
 * @brief A (singleton) class that handles many in-game functions
 */
class SystemOsp : public Object
{
    SharedPtr<Scene> m_hiddenScene;
    SharedPtr<Node> m_parts;
    //Vector<OspPart>
    // list of countried, manufacturers, and other stuff

    URHO3D_OBJECT(SystemOsp, Object)
public:
    SystemOsp(Context* context);

    Scene* get_hidden_scene() { return m_hiddenScene; }
    void debug_function(StringHash which);
    void make_craft(Node* node);
};

}
