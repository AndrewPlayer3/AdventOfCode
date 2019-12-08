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
    Amp(vector<int> memory, string name)
        : name(name), mem(memory), is_halted(false), inputs({}), pc(0), inp_count(0) {}
    int run();
};

int Amp::run() {
    for(int i = 0, j = 0; i < mem.size();) {
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
                mem[mem[i+1]] = inputs[j];
                j++; i+=2; break;
            case 4:
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
    Amp A(mem, string("A")); 
    Amp B(mem, string("B"));
    Amp C(mem, string("C")); 
    Amp D(mem, string("D"));
    Amp E(mem, string("E"));
    vector<int> final_values = {0};
    int pos = 0;
    int A_value = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(j != i) {
                for(int k = 0; k < 5; k++) {
                    if(k != j && k != i) { 
                        for(int l = 0; l < 5; l++) {
                            if(l != k && l != j && l != i) {
                                for(int m = 0; m < 5; m++) {
                                    if(m != l && m != k && m != j && m != i) {
                                        A.inputs = {i, A_value};
                                        int B_value = A.run();
                                        A.mem = mem;
                                        B.inputs = {j, B_value};
                                        int C_value = B.run();
                                        B.mem = mem;
                                        C.inputs = {k, C_value};
                                        int D_value = C.run();
                                        C.mem = mem;
                                        D.inputs = {l, D_value};
                                        int E_value = D.run();
                                        D.mem = mem;
                                        E.inputs = {m, E_value};
                                        int Final = E.run();
                                        E.mem = mem;
                                        final_values.push_back(Final);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "[";
    // for(int i : E.mem) {
    //     cout << i << ", ";
    // }
    // cout << "]";

    sort(final_values.begin(), final_values.end());
    for(int i : final_values) {
        cout << i << ", ";
    }
    cout << endl;
    std::cout << final_values[final_values.size() - 1] << std::endl;
    std::cout << std::endl;
    return 0;
} 