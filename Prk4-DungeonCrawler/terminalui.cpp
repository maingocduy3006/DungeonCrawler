#include <iostream>
#include "terminalui.h"

using namespace std;

TerminalUI::TerminalUI(): AbstraktUI(), Controller()
{
}

void TerminalUI::draw(Level* level)
{
    for (int i = 0; i < level->Breite+2; i++){
        //cout << "|" ;
        for (int j = 0; j < level->Hohe+2; j++){
            Tile* currentTile = level->Spielfeld[i][j];
            if (currentTile->hasCharacter()){
                auto character = currentTile->getCharacter();
                if(character->getTexture() == "Zombie"){
                    cout << " Z ";
                }
                else if(character->getTexture() == "ZombieGuard"){
                    cout << " G ";
                }
                else if(character->getTexture() == "ZombieAttack"){
                    cout << " A ";
                }
                else {
                    cout << " X ";
                }
            }
            else if (currentTile->getTexture() == "Floor"){
                cout << " . ";
            }
            else if (currentTile->getTexture() == "Wall"){
                cout << " # ";
            }
            else if (currentTile->getTexture() == "Portal"){
                cout << " O ";
            }
            else if (currentTile->getTexture() == "OpenDoor"){
                cout << " / ";
            }
            else if (currentTile->getTexture() == "CloseDoor"){
                cout << " D ";
            }
            else if (currentTile->getTexture() == "Switch"){
                cout << " ? ";
            }
            else if (currentTile->getTexture() == "Pit"){
                cout << " * ";
            }
            else if (currentTile->getTexture() == "Ramp"){
                cout << " = ";
            }
            else if (currentTile->getTexture() == "Levelchanger"){
                cout << " E ";
            }
            else if (currentTile->getTexture() == "Chest"){
                cout << " C ";
            }
        }
        cout << endl;
    }
}

Level* TerminalUI::setUpSpielfeld()
{
    int breite, hohe;
    cout << "Geben Sie die Hoehe und die Breite des Spiels ein: ";
    cin >> breite >> hohe;
    return new Level("",breite, hohe);
}

char TerminalUI::move()
{
    cout << "Eingabe zur Bewegung (nur char): ";
    char eingabe;
    cin >> eingabe;
    return eingabe;
}
