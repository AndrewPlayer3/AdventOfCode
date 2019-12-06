#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>

using namespace std;
using namespace chrono;

struct Planet {
    Planet* parent;
};

int main() {
    ifstream file("input.txt");
    auto start = high_resolution_clock::now(); 
    string line = "";
    map<string, Planet> orbits;
    while(getline(file, line)) {
        string parent = line.substr(0, 3);
        string child = line.substr(4, 3);
        orbits[child].parent = &orbits[parent];
    }
    int count = 0;
    for(pair<string, Planet> planet : orbits) {
        Planet* p = planet.second.parent;
        while(p != nullptr) {
            p = p->parent;
            count++;
        }
    }
    cout << count << endl;
    Planet* YOU = &orbits["YOU"];
    Planet* SAN = &orbits["SAN"];
    Planet* you_traveler = YOU->parent;
    Planet* san_traveler = SAN->parent;
    int you_count = 0;
    int san_count = 0;
    for(int i = 0; i < count; i++) {
        for(int j = 0; j < count; j++) {
            if(san_traveler == nullptr) break;
            if(san_traveler == you_traveler) {
                san_count = j; 
                you_count = i;
                break;
            }
            san_traveler = san_traveler->parent;
        }
        if(san_traveler == you_traveler) break;
        san_traveler = SAN->parent;
        you_traveler = you_traveler->parent;
    }
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << san_count + you_count << endl;
    cout << "Time: " << duration.count() << '\n' << endl;
    return 0;
}