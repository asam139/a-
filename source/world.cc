//
// Created by Saul Moreno Abril on 21/07/2018.
//
#import "world.h"


World::World() {
    target_.init(this, Body::Color::Red, Body::Type::Manual);
    //target_.getKinematic()->position = Vec2(WINDOW_HALF_WIDTH * 0.25f, WINDOW_HALF_HEIGHT * 0.25f);
    target_.getKinematic()->position = Vec2(0, 0);

    //ia_.init(this, Body::Color::Green, Body::Type::Autonomous);
    //ia_.getKinematic()->position = Vec2(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*for (int i = 0; i < 20; ++i) {
        auto agent_ptr = std::shared_ptr<Agent>(new Agent());

        agent_ptr->init(this, Body::Color::Blue, Body::Type::Autonomous);
        agent_ptr->getKinematic()->position = Vec2(_w  + randomFloat(-1, 1) * 10, _h + randomFloat(-1, 1) * 10);
        agent_ptr->setAgentGroup(&_agentArray);
        _agentArray.push_back(agent_ptr);
    }*/

    _mapSprite.loadFromFile(MAP_PATH);
    LoadCostMap();
};

World::~World() {
    target_.shutdown();
    //ia_.shutdown();
    for (auto a : _agentArray) {
        a->shutdown();
    }
};


void World::update(const float dt) {
    target_.update(dt);
    //ia_.update(dt);

    for (auto a : _agentArray) {
        a->update(dt);
    }
}
void World::render() {
    _mapSprite.render();

    target_.render();
    //ia_.render();

    for (auto a : _agentArray) {
        a->render();
    }
}

Agent* World::target() {
    return &target_;
}

Agent* World::ia() {
    return &ia_;
}

void World::setAISteering(Body::SteeringMode steering) {
    //ia()->setSteering(steering);
    for (auto a : _agentArray) {
        a->setSteering(steering);
    }
}


void World::LoadCostMap() {
    SDL_Surface* map_image = SDL_LoadBMP(COST_MAP_PATH);
    if (map_image == nullptr) {
        return;
    }

    SDL_LockSurface(map_image);

    uint8_t stride = map_image->pitch >> 2;
    uint32_t* pixels = (uint32_t*)map_image->pixels;
    for (int i = 0; i < COST_MAP_HEIGHT; ++i) {
        uint32_t* step_pixels = pixels;
        for (int j = 0; j < COST_MAP_WIDTH; ++j) {
            if ((*step_pixels & 0x00ffffff) == 0) {
                _costMap[j][i] = 1;     //no walkable
            }
            else {
                _costMap[j][i] = 0;      //walkable
            }

            step_pixels++;
        }
        pixels += stride;
    }

    SDL_UnlockSurface(map_image);
}

