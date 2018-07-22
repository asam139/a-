//----------------------------------------------------------------------------
//                                                        _   ________  __
//  Copyright VIU 2018                                   | | / /  _/ / / /
//  Author: Ivan Fuertes <ivan.fuertes@campusviu.es>     | |/ // // /_/ /
//                                                       |___/___/\____/
//----------------------------------------------------------------------------

#ifndef __WORLD_H__
#define __WORLD_H__ 1

#include <mathlib/vec2.h>

#include <cstdio>
#include <agent.h>
#include <vector>
#include <memory>


using MathLib::Vec2;

class World {
public:
    World();
    ~World();

    void update(const float dt);
    void render();

    Agent* target();
    Agent* ia();

    void setAISteering(Body::SteeringMode steering);

    uint8_t (*getCostMap())[COST_MAP_WIDTH][COST_MAP_WIDTH] {
        return &_costMap;
    }
private:
    Sprite _mapSprite;

    std::vector< std::shared_ptr< Agent > > _agentArray;
    Agent target_, ia_;


    //  Tile Map
    uint8_t _costMap[COST_MAP_WIDTH][COST_MAP_HEIGHT];
    void LoadCostMap();
};

#endif