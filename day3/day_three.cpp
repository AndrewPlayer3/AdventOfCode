#include "paths.hpp"

using namespace std;
using namespace chrono;

int get_min_distance(vector<Point> points) {
    int min = abs(points[1].x - 0) + (points[1].y - 0);
    for(Point p : points) {
        int distance = (abs(p.x - 0) + (p.y - 0));
        if(distance > 0 && distance < min) min = distance;
    }
    return min;
}

int get_min_steps(vector<int> steps) {
    int min = steps[1];
    for(int i = 0; i < steps.size(); i++) {
        int step_count = steps[i];
        if(step_count > 0 && step_count < min) min = step_count;
    }
    return min;
}

vector<Point> get_intersections(vector<Line> v1, vector<Line> v2) {
    vector<Point> intersections;
    for(int i = 0; i < v1.size(); i++) {
        for(int j = 0; j < v2.size(); j++) {
            if(v2[j].intersects(v1[i])) intersections.push_back(v2[j].get_intersection(v1[i]));
            if(v1[i].intersects(v2[j])) intersections.push_back(v1[i].get_intersection(v2[j]));
        }
    }
    return intersections;
}

vector<int> get_intersection_steps(Path p, Path q) {
    vector<int> step_vector;
    for(int i = 0; i < p.size(); i++) {
        for(int j = 0; j < q.size(); j++) {
            if(p[i].intersects(q[j])) {
                Point intersection = p[i].get_intersection(q[j]);
                int q_steps, p_steps, q_offset, p_offset;
                if(i == 0) p_steps = 0;
                else p_steps = p.steps[i-1];
                if(j == 0) q_steps = 0;
                else q_steps = q.steps[j-1];
                switch(q[j].D) {
                    case RIGHT: q_offset = intersection.x - q[j].A.x; break;
                    case LEFT:  q_offset = q[j].B.x - intersection.x; break;
                    case UP:    q_offset = intersection.y - q[j].B.y; break;
                    case DOWN:  q_offset = q[j].A.y - intersection.y; break;
                }
                switch(p[i].D) {
                    case RIGHT: p_offset = intersection.x - p[i].A.x; break;
                    case LEFT:  p_offset = p[i].B.x - intersection.x; break;
                    case UP:    p_offset = intersection.y - p[i].B.y; break;
                    case DOWN:  p_offset = p[i].A.y - intersection.y; break;
                }
                step_vector.push_back(q_steps + p_steps + q_offset + p_offset);
            }
        }
    }
    return step_vector;
}

vector<Line> get_lines(vector<pair<char, int>> wire1) {
    vector<Line> lines; int x, y, new_x, new_y = 0; Point p, q; Line  l;
    for(int i = 0; i < wire1.size(); i++) {
        switch(wire1[i].first) {
            case 'R':
                l.A = Point(x, y); l.B = Point(x + wire1[i].second, y);
                x = x + wire1[i].second;
                break;
            case 'L':
                l.A = Point(x, y); l.B = Point(x - wire1[i].second, y);
                x = x - wire1[i].second;
                break;
            case 'U':
                l.A = Point(x, y); l.B = Point(x, y + wire1[i].second);
                y = y + wire1[i].second;
                break;
            case 'D':
                l.A = Point(x, y); l.B = Point(x, y - wire1[i].second);
                y = y - wire1[i].second;
                break;
        }
        l.set_direction(); l.set_orientation(); lines.push_back(l);
    }
    return lines;
}

int to_int(string s) {
    int number;
    istringstream is(s);
    if(is >> number) return number;
    else cout << "Something went wrong" << endl;
    exit(1);
}

int main() {
    ifstream file("input.txt");
    auto start = high_resolution_clock::now(); 
    vector<vector<pair<char, int>>> wires;
    vector<pair<char, int>> wire1, wire2;
    wires.push_back(wire1); wires.push_back(wire2);
    int i = 0; string line = "";
    while(getline(file, line)) {
        int pos = 0;
        char direction = ' ';
        string distance = "";
        while(pos != line.size() + 1) {
            if(isalpha(line[pos])) direction = line[pos];
            else if(isdigit(line[pos])) distance += line[pos];
            else if(pos == line.size() || line[pos] == ',') {
                wires[i].push_back(pair<char, int>(direction, to_int(distance)));
                direction = ' '; distance = "";
            }
            pos++;
        }
        i++;
    }
    vector<Line> wire1_lines = get_lines(wires[0]);
    vector<Line> wire2_lines = get_lines(wires[1]);
    Path P1(wire1_lines);
    Path P2(wire2_lines);
    vector<Point> intersections = get_intersections(wire1_lines, wire2_lines);
    vector<int> inter_steps = get_intersection_steps(P1, P2);
    int min_distance = get_min_distance(intersections);
    int min_steps = get_min_steps(inter_steps);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Minimum Distance: " << min_distance << endl;
    cout << "Minimum Steps: " << min_steps << endl;
    cout << "Time: " << duration.count() << endl;
    cout << endl;
    return 0;
}