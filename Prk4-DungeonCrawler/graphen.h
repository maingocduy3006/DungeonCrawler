#ifndef GRAPHEN_H
#define GRAPHEN_H

#include "level.h"
#include "tile.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

struct Node{
    struct MapSorter{
        bool operator()(const Node* lhs, const Node* rhs) const{
            if(lhs->tile->getRow() == rhs->tile->getRow()){
                return lhs->tile->getCol() < rhs->tile->getCol();
            }
            else{
                return lhs->tile->getRow() < rhs->tile->getRow();
            }
        }
    };
    Tile* tile;
    std::map<Node*, double, MapSorter> adjListe;
    bool operator==(const Node& other) const{
        return tile == other.tile;
    }
    bool operator!=(const Node& other) const{
        return tile != other.tile;
    }
};

class Graphen
{
private:
    Level* level;
    vector<vector<Node*>> nodeField;
public:
    Graphen();
    ~Graphen();

    void initGraphen(Level* lvl);
    double caculateDistance(int, int, int, int);
    void addNeighbourNode(Node*, int, int);

    Node* findNode(Tile* tile);
    vector<Node*> shortestPathGraph(Tile *srcTile, Tile *desTile);
};

#endif // GRAPHEN_H
