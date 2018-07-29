//
// Created by Saul Moreno Abril on 29/07/2018.
//

#include "pathFinding.h"
#include <debug_draw.h>
#include <world.h>


PathFinding::PathFinding() : _nodeBH(COST_MAP_WIDTH * COST_MAP_WIDTH) {

}

PathFinding::~PathFinding() {

}

void PathFinding::Init(World *world) {
    _world = world;
    _heuristicMode = HeuristicMode::Manhattan;


    InitNodes();
    ResetCurrentStateValue();
}
void PathFinding::SetHeuristicMode(HeuristicMode mode) {
    _heuristicMode = mode;
}

void PathFinding::InitNodes() {
    for (int i = 0; i < COST_MAP_WIDTH; ++i) {
        for (int j = 0; j < COST_MAP_HEIGHT; ++j) {
            Node *node = &_nodes[i][j];
            node->position.x = i;
            node->position.y = j;
            node->parent = {0, 0};
            node->G = 0;
            node->F = 0;
            node->state = 0;
        }
    }
}

void PathFinding::ResetCurrentStateValue() {
    currentStateValue.opened = rand() % 100 + 1;
    currentStateValue.closed = currentStateValue.opened * 10;
    currentStateValue.resolved = currentStateValue.closed * 100;
}

void PathFinding::CalculateWalk(tiledPosition startTiledPosition,
                                tiledPosition endTiledPosition,
                                tiledPosition *tiledPositions,
                                unsigned int *usedLenght) {
    if (_world == nullptr) {
        printf("PathFinding is not initialized");
        return;
    }

    clock_t start_t, end_t;

    ResetCurrentStateValue();

    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);

    InitNodes();

    Node *initNode = &_nodes[startTiledPosition.x][startTiledPosition.y];
    initNode->state = 0;
    initNode->parent = startTiledPosition;
    initNode->G = 0;
    initNode->F = 0;
    //PrintNode(*initNode);

    Node *endNode = &_nodes[endTiledPosition.x][endTiledPosition.y];
    //PrintNode(*endNode);

    // 1º Add first node to opened list
    initNode->state = currentStateValue.opened;

    // 2º Loop
    bool founded = false;
    bool finished = false;
    do {
        // A: Search node with minimum F inside opened list
        unsigned int minF = UINT_MAX;
        Node *nextNode = nullptr;
        for (int i = 0; i < COST_MAP_WIDTH; i++) {
            for (int j = 0; j < COST_MAP_HEIGHT; j++) {
                Node *node = &_nodes[i][j];
                if (node->state != currentStateValue.opened) {
                    continue;
                }

                unsigned int F = node->F;
                if (F < minF) {
                    minF = F;
                    nextNode = node;
                }
            }
        }


        if (nextNode != nullptr) {
            //PrintNode(*nextNode);

            // B: Move to closed list
            nextNode->state = currentStateValue.closed;

            // C: Search to 8 adjacent nodes
            tiledPosition nextTiledPos = nextNode->position;
            int nextG = nextNode->G;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (j == 0 && i == 0) {
                        continue;
                    }

                    tiledPosition tiledPos = {0, 0};
                    tiledPos.x = nextTiledPos.x + i;
                    tiledPos.y = nextTiledPos.y + j;
                    if (tiledPos.x < 0 || tiledPos.x >= COST_MAP_WIDTH ||
                        tiledPos.y < 0 || tiledPos.y >= COST_MAP_WIDTH) {
                        continue;
                    }

                    // Check if adjacent node was closed
                    Node* adjacentNode = &_nodes[tiledPos.x][tiledPos.y];
                    if (adjacentNode->state == currentStateValue.closed) {
                        continue;
                    }

                    // Check if node is walkable/no walkable

                    uint8_t cost = _world->getCostMapFor(tiledPos.x, tiledPos.y);
                    if (cost == 1) {
                        continue;
                    }

                    int isDiagonal = abs(i) + abs(j) == 2;
                    int costG = isDiagonal ? 14 : 10;

                    int newG = nextG + costG;

                    bool recalculateF = false;
                    if (adjacentNode->state == currentStateValue.opened) {
                        // Node already in opened list
                        if (adjacentNode->G > newG) {
                            adjacentNode->parent = nextTiledPos;
                            adjacentNode->G = newG;
                            recalculateF = true;
                        }
                    } else {
                        // Move to opened list
                        adjacentNode->state = currentStateValue.opened;
                        adjacentNode->parent = nextTiledPos;
                        adjacentNode->G = newG;

                        recalculateF = true;
                    }

                    if (recalculateF) {
                        unsigned int H = heuristic(*adjacentNode, *endNode);
                        adjacentNode->F = adjacentNode->G + H;
                    }

                }
            }


            // D: End node to closed list
            if (nextNode == endNode) {
                finished = true;
                founded = true;
            }

        } else {
            // D: it does not exist a wall
            finished = true;
        }

    } while (!finished);


    *usedLenght = 0;
    if (founded) {
        Node* node = endNode;
        do {
            node->state = currentStateValue.resolved;
            tiledPositions[*usedLenght] = node->position;
            (*usedLenght)++;

            tiledPosition tiledPosition = node->parent;
            node = &_nodes[tiledPosition.x][tiledPosition.y];
        } while (node != initNode);
    }
    printf("Wall Lenght: %d\n", *usedLenght);

    end_t = clock();
    printf("End of the big loop, end_t = %ld\n", end_t);

    double endTime = (double)(end_t - start_t) / (double)CLOCKS_PER_SEC;
    printf("Total time taken by CPU: %f\n", endTime);
}

void PathFinding::DrawNodes() const {
    for (int i = 0; i < COST_MAP_WIDTH; ++i) {
        for (int j = 0; j < COST_MAP_HEIGHT; ++j) {
            const Node *node = &_nodes[i][j];
            if (node->state == currentStateValue.opened) {
                Vec2 fPos;
                fPos.x() = node->position.x * TILED_SIZE;
                fPos.y() = node->position.y * TILED_SIZE;
                DebugDraw::drawRect(fPos, TILED_SIZE, TILED_SIZE, 0xFF, 0x00, 0x00, 0x80);
            } else if (node->state == currentStateValue.closed) {
                Vec2 fPos;
                fPos.x() = node->position.x * TILED_SIZE;
                fPos.y() = node->position.y * TILED_SIZE;
                DebugDraw::drawRect(fPos, TILED_SIZE, TILED_SIZE, 0x00, 0xFF, 0x00, 0x80);
            } else if (node->state == currentStateValue.resolved) {
                Vec2 fPos;
                fPos.x() = node->position.x * TILED_SIZE;
                fPos.y() = node->position.y * TILED_SIZE;
                DebugDraw::drawRect(fPos, TILED_SIZE, TILED_SIZE, 0x00, 0x00, 0xFF, 0x80);
            }
        }
    }
}

void PathFinding::PrintNode(const Node &node) const {
    printf("Node: position(%d, %d)\n", node.position.x, node.position.y);
}

uint16_t PathFinding::heuristic(const Node& node, const Node& goal) {
    switch (_heuristicMode) {
        case HeuristicMode::Manhattan:
            return heuristicManhattan(node, goal);
        case HeuristicMode::Diagonal:
            return heuristicDiagonal(node, goal);
        case HeuristicMode::Euclidean:
            return heuristicEuclidean(node, goal);
    }
}

uint16_t PathFinding::heuristicManhattan(const Node& node, const Node& goal) {
    const uint16_t xDist = abs(node.position.x - goal.position.x);
    const uint16_t yDist = abs(node.position.x - goal.position.y);
    return 10 * (xDist + yDist);
}

uint16_t PathFinding::heuristicDiagonal(const Node& node, const Node& goal) {
    const uint16_t xDist = abs(node.position.x - goal.position.x);
    const uint16_t yDist = abs(node.position.y - goal.position.y);
    return (10 * (xDist + yDist)) + ((14 - (10 * 2)) * std::min(xDist, yDist));
}

uint16_t PathFinding::heuristicEuclidean(const Node& node, const Node& goal) {
    const uint16_t xDist = abs(node.position.x - goal.position.x);
    const uint16_t yDist = abs(node.position.y - goal.position.y);
    return 10 * sqrt((xDist * xDist) + (yDist * yDist));
}