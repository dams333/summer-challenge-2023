#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct s_pt
{
    int x;
    int y;
} pt;

int get_distance(pt &p1, pt &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int get_smallest_distance(pt p1, vector<pt> &pts)
{
    int smallestDistance = get_distance(pts[0], p1);
    for (pt &p : pts)
    {
        int dist = get_distance(p, p1);
        if (dist < smallestDistance)
        {
            smallestDistance = dist;
        }
    }
    return smallestDistance;
}

int main()
{

    // game loop
    while (1) {
        string input;
        getline(cin, input);
        stringstream ss(input);

        vector<int> inputs;
        string elem;
        while (getline(ss, elem, ' '))
            inputs.push_back(atoi(elem.c_str()));
            
        cerr << "Inputs (" << inputs.size() << "):";
        for (int &input : inputs)
            cerr << " " << input;
        cerr << endl;

        pt player;
        vector<pt> enemies;

        for (int i = 0; i < inputs.size() - 2; i += 2)
        {
            enemies.push_back({inputs[i], inputs[i + 1]});
        }
        player = {inputs[inputs.size() - 2], inputs[inputs.size() - 1]};

        int upDistance = get_smallest_distance({player.x, player.y + 1}, enemies);
        int downDistance = get_smallest_distance({player.x, player.y - 1}, enemies);
        int leftDistance = get_smallest_distance({player.x - 1, player.y}, enemies);
        int rightDistance = get_smallest_distance({player.x + 1, player.y}, enemies);

        if (upDistance <= downDistance && upDistance >= leftDistance && upDistance >= rightDistance)
        {
            cout << "RB" << endl;
            continue ;
        }
        if (downDistance >= upDistance && downDistance >= leftDistance && downDistance >= rightDistance)
        {
            cout << "KLUO" << endl;
            continue ;
        }
        if (leftDistance >= downDistance && leftDistance >= upDistance && leftDistance >= rightDistance)
        {
            cout << "EQXF" << endl;
            continue ;
        }
        if (rightDistance >= downDistance && rightDistance >= leftDistance && rightDistance >= upDistance)
        {
            cout << "TYHPF" << endl;
            continue ;
        }

        //RB = UP / KLUO = DOWN / EQXF = LEFT / TYHPF = RIGHT
        cout << "KLUO" << endl;
    }
}
