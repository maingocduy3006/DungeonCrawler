#include "graphen.h"
#include "door.h"
#include "cmath"
#include "levelchanger.h"
#include <queue>

#define INF 0xFFFFFFF
using std::priority_queue;

Graphen::Graphen(): level(nullptr)
{

}

Graphen::~Graphen()
{
    auto row = level->getBreite();
    auto col = level->getHohe();
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            delete nodeField[i][j];
        }
    }
}

void Graphen::initGraphen(Level *lvl)
{
    if(level != nullptr){
        for (int i=0; i<level->getBreite(); i++){
            for (int j=0; j<level->getHohe(); j++){
                delete nodeField[i][j];
            }
        }
    }

    level = lvl;
    auto row = level->getBreite();
    auto col = level->getHohe();

    nodeField.resize(row, vector<Node*>(col));
    for (int i=1; i<=row; i++){
        for (int j=1; j<=col; j++){
            Node* tmp = new Node{level->getTile(i,j)};
            if(tmp != nodeField[i-1][j-1]){
                nodeField.at(i-1).at(j-1) = tmp;
            }
        }
    }

    for (int i=1; i<=row; i++){
        for (int j=1; j<=col; j++){
            //Node tmp {level->getTile(i,j)};
            addNeighbourNode(nodeField.at(i-1).at(j-1),i-1,j-1);
        }
    }
}

double Graphen::caculateDistance(int Row1, int Col1, int Row2, int Col2)
{
    return sqrt(pow(Row1-Row2,2) + pow(Col1-Col2,2));
}

void Graphen::addNeighbourNode(Node *node, int currRow, int currCol)
{
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            bool checkRow = (currRow+i >= 0) && (currRow+i < level->getBreite());
            bool checkCol = (currCol+j >= 0) && (currCol+j < level->getHohe());
            if(!(checkCol&&checkRow)){
                continue;
            }
            auto tmpNode = nodeField[currRow+i][currCol+j];
            Tile* tmpTile = tmpNode->tile;
            double distance = caculateDistance(currRow, currCol, currRow+i, currCol+j);

            if((typeid(*tmpTile) == typeid(LevelChanger)) || (typeid(*node->tile) == typeid(LevelChanger))){
                continue;
            }

            bool canEnter = tmpTile->CheckOnEnter(node->tile) != nullptr;
            bool canLeave = node->tile->CheckOnLeave(tmpTile) != nullptr;


            auto desTile = tmpTile->CheckOnEnter(node->tile);
            auto desNode = findNode(desTile);

            if((node != tmpNode) && canEnter && canLeave){
                node->adjListe.insert({desNode,distance});
            }
        }
    }
}

Node* Graphen::findNode(Tile *tile)
{
    for (int i=0; i<level->getBreite(); i++){
        for (int j=0; j<level->getHohe(); j++){
            if(tile == nodeField[i][j]->tile){
                return nodeField[i][j];
            }
        }
    }
    return nullptr;
}

std::vector<Node*> Graphen::shortestPathGraph(Tile *srcTile, Tile *desTile)
{
    typedef std::pair<double, Node*> Element;
    auto compare = [](Element elem1, Element elem2){ return elem1.first < elem2.first;};

    priority_queue<Element, vector<Element>,decltype(compare)> PriorQueue(compare);

    std::map<Node*, std::pair<double, std::vector<Node*>>,Node::MapSorter> distance;

    auto srcNode = findNode(srcTile);
    if(srcNode == nullptr){
        return std::vector<Node*>{};
    }

    PriorQueue.push(std::make_pair(0,srcNode));
    distance.insert({srcNode, std::make_pair(0, std::vector<Node*>{})});

    while(!PriorQueue.empty()){
        Node* u = PriorQueue.top().second;
        PriorQueue.pop();

        for(auto i = u->adjListe.begin(); i != u->adjListe.end(); i++){
            Node* v = i->first;
            double weight = i->second;

            if(distance.find(v) == distance.end()){
                distance[v] = std::make_pair(INF, std::vector<Node*>{});
            }

            if(distance[v].first > distance[u].first + weight){
                distance[v].first = distance[u].first + weight;
                distance[v].second = distance[u].second;
                distance[v].second.push_back(u);
                PriorQueue.push(std::make_pair(distance[v].first,v));
            }
        }
    }

    auto destNode = findNode(desTile);
    if(destNode == nullptr){
        return std::vector<Node*>{};
    }
    auto iter = distance.find(destNode);
    if(iter != distance.end()){
        (*iter).second.second.push_back(destNode);
        return (*iter).second.second;
    }
    return std::vector<Node*>{};
}









