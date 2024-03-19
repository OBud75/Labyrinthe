#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const char PLAYER = 'J';
const char WALL = '#';
const char VOID = '.';
const char END = 'S';
bool showWalls = true;

void printMap(const vector<vector<char>>& map) 
{
    for (const auto& line : map) {
        for (const auto& cell : line) {
            if (cell == WALL && !showWalls) {
                cout << VOID << " ";
            } else {
                cout << cell << " ";
            }
        }
        cout << endl;
    }
}

vector<vector<char>> loadMap(const string& pathFile, int& posX, int& posY) 
{
    vector<vector<char>> map;
    ifstream file(pathFile);
    string line;

    while (getline(file, line)) {
        vector<char> lineMap;
        for (char& cell : line) {
            lineMap.push_back(cell);
        }
        map.push_back(lineMap);
    }
    file.close();
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] == PLAYER) {
                posX = x;
                posY = y;
            }
        }
    }
    return map;
}

int main() 
{
    int x = 0;
    int y = 0;
    vector<vector<char>> map = loadMap("carte.txt", x, y);
    cout << "Voulez-vous que les murs soient visibles (Cela rajoute de la difficulte ou non)? (o/n): ";
    char choice;
    cin >> choice;
    showWalls = (choice == 'o' || choice == 'O');

    while (true) {
        int dx = 0, dy = 0;
        printMap(map);
        cout << "Deplacez-vous (haut (z), bas (s), droite (d), gauche (g)): ";
        char movement;
        cin >> movement;

        switch (movement) {
            case 'z': dy = -1; break;
            case 's': dy = 1; break;
            case 'd': dx = 1; break;
            case 'q': dx = -1; break;
        }
        int newX = x + dx, newY = y + dy;
        if (newX >= 0 && newX < map[0].size() && newY >= 0 && newY < map.size()) {
            if (map[newY][newX] == END) {
                cout << "Bravo vous avez trouve la sortie!" << endl;
                break;
            } else if (map[newY][newX] != WALL) {
                map[y][x] = VOID;
                x = newX;
                y = newY;
                map[y][x] = PLAYER;
            } else
                cout << "Mouvement impossible !" << endl;
        } else
            cout << "Mouvement impossible !" << endl;
    }
    return (0);
}
