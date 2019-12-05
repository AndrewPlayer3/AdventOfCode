#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> run(vector<int> mem) {
    for(int i = 0; i < mem.size();) {
        int OP = (mem[i] % 100) / 1;
        int A  = ((mem[i] % 1000) - OP) / 100;
        int B  = ((mem[i] % 10000) - A)  / 1000;
        int C  = ((mem[i] % 100000) - B)  / 10000; // Should always be ZERO
        if(OP == 1)  {
            if     (A == 0 && B == 0) mem[mem[i+3]] = mem[mem[i+1]] + mem[mem[i+2]];
            else if(A == 1 && B == 0) mem[mem[i+3]] = mem[    i+1 ] + mem[mem[i+2]];
            else if(A == 0 && B == 1) mem[mem[i+3]] = mem[mem[i+1]] + mem[    i+2 ];
            else if(A == 1 && B == 1) mem[mem[i+3]] = mem[    i+1 ] + mem[    i+2 ];
            i+=4;
        } else if(OP == 2)  {
            if     (A == 0 && B == 0) mem[mem[i+3]] = mem[mem[i+1]] * mem[mem[i+2]];
            else if(A == 1 && B == 0) mem[mem[i+3]] = mem[    i+1 ] * mem[mem[i+2]];
            else if(A == 0 && B == 1) mem[mem[i+3]] = mem[mem[i+1]] * mem[    i+2 ];
            else if(A == 1 && B == 1) mem[mem[i+3]] = mem[    i+1 ] * mem[    i+2 ];
            i+=4;
        }
        else if(OP == 3)  {
            int input;
            cout << "Enter an int: ";
            cin >> input;
            mem[mem[i+1]] = input;
            i+=2;
        }
        else if(OP == 4 ) {
            if(A == 0) cout << mem[mem[i+1]] << endl;  
            else       cout << mem[    i+1 ] << endl;
            i+=2;
        }
        else if(OP == 99) {
            return mem;
        } else {
            i++;
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
            if(run(temp_vec)[0] == 19690720) 
                return ((100 * i) + j);
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
            if(isdigit(line[pos]) || line[pos] == '-') {
                temp += line[pos++];
            } else if(line[pos] == ',') {
                mem.push_back(to_int(temp));
                temp = "";
                pos++;
            }
        }
    }
    vector<int> done = run(mem);
    return 0;
}