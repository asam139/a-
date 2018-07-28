//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __BODY_H__
#define __BODY_H__ 1

#include <sprite.h>
#include <defines.h>
#include <mathlib/vec2.h>
#include <vector>

using MathLib::Vec2;

class Agent;

class Body {
  public:
    enum class Color {
        Green,
        Blue,
        Purple,
        Red,
    };

    enum class Type {
        Autonomous,
        Manual,
        PathFinding
    };

    enum class SteeringMode {
        Kinematic_Seek,         //1       Kinematics
        Kinematic_Flee,         //2
        Kinematic_Arrive,       //3
        Kinematic_Wander,       //4
        Seek,                   //q       Steering Basics
        Flee,                   //w
        Arrive,                 //e
        Align,                  //r
        Velocity_Matching,      //t
        Pursue,                 //a       Steering Delegated
        Face,                   //s
        LookGoing,              //d
        Wander,                 //f
    };

    Body() {};
    ~Body() {};

    void init(const Color color, const Type type, Agent *agent);
    void update(const float dt);
    void render() const;

    void setTarget(Agent* target);
    void setSteering(const SteeringMode steering) { _steering_mode = steering; };

    void setAgentGroup(std::vector<std::shared_ptr<Agent>>* agentGroup) {
        _agentGroup = agentGroup;
    }
    std::vector<std::shared_ptr<Agent>>*  getAgentGroup() {
        return _agentGroup;
    }

    const KinematicStatus* getKinematic() const { return &_state; }
    KinematicStatus* getKinematic() { return &_state; }

    void SetFinalPosition(Vec2 finalPosition);

  private:
    void updateManual(const float dt);
    void updateAutonomous(const float dt);
    void updatePathFinding(const float dt);
    void setOrientation(const MathLib::Vec2& direction);
    void keepInSpeed();
    void keepInBounds();

    void updateKinematic(const float dt, const KinematicSteering& steering);

    void update_kinematic_seek(const float dt);
    void update_seek(const float dt);
    void update_kinematic_flee(const float dt);
    void update_flee(const float dt);
    void update_kinematic_arrive(const float dt);
    void update_arrive(const float dt);
    void update_kinematic_wander(const float dt);
    void update_align(const float dt);
    void update_velocity_matching(const float dt);
    void update_pursue(const float dt);
    void update_face(const float dt);
    void update_lookgoing(const float dt);
    void update_wander(const float dt);

    Sprite _sprite;
    Type _type;
    Color _color;
    SteeringMode _steering_mode;
    Agent* _agent = nullptr;
    Agent* _target = nullptr;
    std::vector< std::shared_ptr<Agent>> *_agentGroup = nullptr;

    const float _maxSpeed { 5.f };
    const float _maxAcceleration { 1.0f};
    const float _maxRotation = { M_PI_4 };
    const float _maxAngularSpeed = { 1.0f };

    const float _minDistance { 5.0f }; //squared radius
    const float _slowRadius { 100.0f };
    const float _slowAngle { M_PI / 8.0f };
    const float _fixedTime { 5.f };
    const float _maxPrediction { 5.0f };

    const float _wanderOffset { 50.0f };
    const float _wanderRadius { 20.0f };
    const float _wanderRate { 2.0f };

    const float _flockingRadius { 25.0f };
    const float _alignmentWeight { 1.0f };
    const float _cohesionWeight { 0.5f };
    const float _separationWeight { 2.0f };

    struct {
      struct {
        Vec2 pos;
        Vec2 v;
      } green, red, blue;
    } dd;

    KinematicStatus _state;
    KinematicSteering _steering;

    MathLib::Vec2 _finalPosition = {0.0f, 0.0f};

    struct tiledPosition {
        int x;
        int y;
    };
    unsigned int _tiledWallLenght = 0;
    tiledPosition _tiledWall[MAX_PATH_SIZE];
    int _nextTiled = -1;

    struct  Node { //struct to hold nodes on location list
        tiledPosition position;
        unsigned int state; //is in open or closed list
        tiledPosition parent; //position on tilemap of his parent (x,y)
        unsigned int G; //G cost
    };
    // Array of nodes in its physical position
    Node _nodes[COST_MAP_HEIGHT][COST_MAP_WIDTH];

    //
    struct stateValue {
        unsigned int opened;
        unsigned int closed;
        unsigned int resolved;
    };
    stateValue currentStateValue;

    void CalculateWalk(tiledPosition startTiledPosition, tiledPosition endTiledPosition);
    void DrawNodes() const;
    void InitNodes();
    void PrintNode(const Node &node) const;

    uint16_t heuristicManhattan(const Node& node, const Node& goal);
    uint16_t heuristicDiagonal(const Node& node, const Node& goal);
    uint16_t heuristicEuclidean(const Node& node, const Node& goal);
};

#endif
