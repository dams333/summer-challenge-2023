#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param n_gears An integer representing the number of gears in the system (numbered from 0 to N-1).
 * @param connections An array representing all pairs of gears connected together.
 * @return An array of two integers representing the number of gears rotating clockwise and counterclockwise respectively, or [-1, -1] if the configuration is invalid.
 */
vector<int> gearBalance(int n_gears, vector<vector<int>> connections) {
  // Write your code here

  map<int, set<int>> gears;

  for (auto it = connections.begin(); it != connections.end(); it++)
  {
    int g1 = it->at(0);
    int g2 = it->at(1);
    gears[g1].insert(g2);
    gears[g2].insert(g1);
  }

  map<int, int> rotations;
  rotations.insert(make_pair(0, 1));
  set<int> worked;
  worked.insert(0);
  set<int> tmp;
  int rotation = 1;
  while(worked.size() > 0)
  {
    rotation *= -1;
    for (auto &gear : worked)
    {
      for (auto &child : gears[gear])
      {
        if (rotations.find(child) == rotations.end())
        {
          rotations[child] = rotation;
          tmp.insert(child);
        }
        else
        {
          if (rotations[child] != rotation)
          {
            return {-1, -1};
          }
        }
      }
    }
    worked.clear();
    worked.insert(tmp.begin(), tmp.end());
    tmp.clear();
  }

  int c1 = 0;
  int c2 = 0;

  for (auto it = rotations.begin(); it != rotations.end(); it++)
  {
    if (it->second == 1)
      c1++;
    else
      c2++;
  }

  return {c1, c2};
}

/* Ignore and do not change the code below */

void trySolution(vector<int> output) {
  Json::Value output_json;

  output_json = Json::Value(Json::arrayValue);
  Json::Value current_value;
  for (int i = 0 ; i < output.size() ; i++) {
    current_value = Json::Value(output[i]);
    output_json.append(current_value);
  }

  Json::FastWriter fastWriter;
  std::string output_str = fastWriter.write(output_json);
  cout << "" << output_str.c_str();
}

int main () {
  setlocale(LC_ALL, "en_US.UTF-8");
  Json::Reader reader;
  string line;
  Json::Value parsed_json;
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);
  int n_gears = parsed_json.asInt();
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<vector<int>> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
  
    vector<int> array2;
    for (int j = 0 ; j < parsed_json[i].size() ; j++) {
      array2.push_back(parsed_json[i][j].asInt());
    }
    array.push_back(array2);
  }
  vector<vector<int>> connections = array;

  vector<int> output = gearBalance(n_gears, connections);
  trySolution(output);
}
/* Ignore and do not change the code above */

