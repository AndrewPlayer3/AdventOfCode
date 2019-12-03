#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> run(vector<int> mem) {
    for(int i = 0; i < mem.size(); i+=4) {
        if(mem[i] == 1) {
            mem[mem[i+3]] = mem[mem[i+1]] + mem[mem[i+2]];
        } else if(mem[i] == 2) {
            mem[mem[i+3]] = mem[mem[i+1]] * mem[mem[i+2]];
        } else if(mem[i] == 99) {
            return mem;
        } else {
            //do nothing
        }
    }
    return {0};
}

int crack(vector<int> mem) {
    for(int i = 0; i < 99; i++) {
        for(int j = 0; j < 99; j++) {
            vector<int> temp_vec = mem;
            temp_vec[1] = i;
            temp_vec[2] = j;
            if(run(temp_vec)[0] == 19690720) {
                return ((100 * i) + j);
            }
        }
    }
}

int to_int(string s) {
    istringstream is(s);
    int number;
    if(is >> number) return number;
    else cout << "Something went wrong..." << endl;
    exit(1);
}

int main() {

    ifstream file("input.txt");
    string line = "";
    vector<int> mem;
    while(getline(file, line)) {
        int pos = 0;
        string temp = "";
        while(pos != line.size()) {
            if(isdigit(line[pos])) {
                temp += line[pos++];
            } else if(line[pos] == ',') {
                mem.push_back(to_int(temp));
                temp = "";
                pos++;
            }
        }
    }
    mem[1] = 12;
    mem[2] = 2;
    //vector<int> done = run(mem);
    int combo = crack(mem);
    cout << combo << endl;
    return 0;
}