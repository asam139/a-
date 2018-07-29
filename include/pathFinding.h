//
// Created by Saul Moreno Abril on 29/07/2018.
//

#ifndef A_PATHFINDING_H
#define A_PATHFINDING_H

#import <defines.h>
#include <mathlib/vec2.h>

class World;

class PathFinding {
public:
    PathFinding();
    ~PathFinding();

    enum class HeuristicMode {
        Manhattan,
        Diagonal,
        Euclidean
    };

    void Init(World* world);

    void SetHeuristicMode(HeuristicMode mode);

    void CalculateWalk(tiledPosition startTiledPosition,
                       tiledPosition endTiledPosition,
                       tiledPosition* tiledPositions,
                       unsigned int *usedLenght);
    void DrawNodes() const;

private:
    World* _world;
    HeuristicMode _heuristicMode;

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


    void InitNodes();
    void PrintNode(const Node &node) const;

    uint16_t heuristic(const Node& node, const Node& goal);
    uint16_t heuristicManhattan(const Node& node, const Node& goal);
    uint16_t heuristicDiagonal(const Node& node, const Node& goal);
    uint16_t heuristicEuclidean(const Node& node, const Node& goal);
};


#endif //A_PATHFINDING_H
