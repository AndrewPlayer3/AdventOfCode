#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Amp {
public:
    string name;
    vector<int> mem;
    bool is_halted;
    vector<int> inputs;
    int inp_count;
    int pc;
    Amp(vector<int> memory)
        : name(""), mem(memory), is_halted(false), inputs({}), pc(0), inp_count(0) {}
    int run();
};

int Amp::run() {
    for(int i = pc, j = inp_count; i < mem.size();) {
        int OP = (mem[i] % 100) / 1;
        int A  = ((mem[i] % 1000) - OP) / 100;
        int B  = ((mem[i] % 10000) - A)  / 1000;
        int C  = ((mem[i] % 100000) - B)  / 10000; // Should always be ZERO
        int a_param; int b_param;
        if(i+1 < mem.size()) {
            if(A == 0) a_param = mem[i+1];
            else a_param = i+1;
        }
        if(i+2 < mem.size()) {
            if(B == 0) b_param = mem[i+2];
            else b_param = i+2;
        }        
        switch(OP) {
            case 1:
                mem[mem[i+3]] = mem[a_param] + mem[b_param];
                i+=4; break;
            case 2:
                mem[mem[i+3]] = mem[a_param] * mem[b_param];
                i+=4;  break;
            case 3:
                mem[mem[i+1]] = inputs[inp_count];
                inp_count+=1;
                j++; i+=2; break;
            case 4:
                pc = i+2;
                if(A == 0) {
                    return mem[mem[i+1]];
                }  
                else {
                    return mem[i+1];
                } 
                break;
            case 5:
                if(mem[a_param] != 0) i = mem[b_param]; 
                else i+=3; break;
            case 6:
                if(mem[a_param] == 0) i = mem[b_param]; 
                else i+=3; break;
            case 7:
                if(mem[a_param] < mem[b_param]) mem[mem[i+3]] = 1; 
                else mem[mem[i+3]] = 0;
                i+=4; break;
            case 8:
                if(mem[a_param] == mem[b_param]) mem[mem[i+3]] = 1; 
                else mem[mem[i+3]] = 0;
                i+=4; break;
            case 99:
                is_halted = true;
                return mem[0]; break;
            default:
                i++; break;
        }
    }
    return {0};
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
                temp += line[pos];
            }
            if(line[pos] == ',' || pos == line.size() - 1) {
                mem.push_back(to_int(temp));
                temp = "";
                pos;
            }
            ++pos;
        }
    }
    vector<int> final_values = {0};
    int A_value = 0;
    vector<Amp> amps = {{mem}, {mem}, {mem}, {mem}, {mem}};
    int params[] = {5, 6, 7, 8, 9};
    while(next_permutation(params, params+5)) {
        A_value = 0;
        for(int i = 0; i < amps.size(); i++) amps[i] = Amp(mem);
        amps[0].inputs = {params[0]};
        amps[1].inputs = {params[1]};
        amps[2].inputs = {params[2]};
        amps[3].inputs = {params[3]};
        amps[4].inputs = {params[4]};
        while(!amps[4].is_halted) {
            int n = 0;
            amps[n].inputs.push_back(A_value);
            amps[++n].inputs.push_back(amps[n-1].run());
            amps[++n].inputs.push_back(amps[n-1].run());
            amps[++n].inputs.push_back(amps[n-1].run());
            amps[++n].inputs.push_back(amps[n-1].run());
            A_value = amps[n].run();
            final_values.push_back(A_value);
        }
        amps[4].is_halted = false;
    }
                                                            
    std::sort(final_values.begin(), final_values.end());
    std::cout << std::endl;
    std::cout << "Max thruster value: " << final_values[final_values.size() - 1] << std::endl;
    std::cout << std::endl;
    return 0;
} 