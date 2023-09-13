#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;

typedef struct s_pt
{
  int x;
  int y;
} pt;

bool test(vector<string> instructions, vector<int> target)
{
  pt direction = {1, 0};
  pt player = {0, 0};

  for (string &ins : instructions)
  {
    // cerr << "POS: " << player.x << ";" << player.y << " | DIR: " << direction.x << ";" << direction.y << " | " << ins << endl;
    if (ins == "FORWARD")
    {
      player.x += direction.x;
      player.y += direction.y;
    }
    if (ins == "BACK")
    {
      player.x -= direction.x;
      player.y -= direction.y;
    }
    if (ins == "TURN RIGHT")
    {
      if (direction.x == 1)
      {
        direction.x = 0;
        direction.y = -1;
      }
      else if (direction.x == -1)
      {
        direction.x = 0;
        direction.y = 1;
      }
      else if (direction.y == 1)
      {
        direction.y = 0;
        direction.x = 1;
      }
      else if (direction.y == -1)
      {
        direction.y = 0;
        direction.x = -1;
      }
    }
    if (ins == "TURN LEFT")
    {
      if (direction.x == 1)
      {
        direction.x = 0;
        direction.y = 1;
      }
      else if (direction.x == -1)
      {
        direction.x = 0;
        direction.y = -1;
      }
      else if (direction.y == 1)
      {
        direction.y = 0;
        direction.x = -1;
      }
      else if (direction.y == -1)
      {
        direction.y = 0;
        direction.x = 1;
      }
    }
  }
  if (player.x == target[0] && player.y == target[1])
    return true;
  return false;
}

/**
 * @param instructions The list of instructions as memorized by the mutant.
 * @param target The coordinates (x, y) of the target.
 * @return A string respecting the given format to fix the mutant's path.
 */
string findCorrectPath(vector<string> instructions, vector<int> target) {
  // Write your code here
  vector<string> ins;
  ins.push_back("FORWARD");
  ins.push_back("BACK");
  ins.push_back("TURN RIGHT");
  ins.push_back("TURN LEFT");
  for (int i = 0; i < instructions.size(); i++)
  {
    vector<string> copy = vector(instructions);
    for (string &replace : ins)
    {
      if (instructions[i] != replace)
      {
        // cerr << "Test with " << replace << " as " << (i+1) << endl;
        copy[i] = replace;
        if (test(copy, target))
        {
          stringstream ss;
          ss << "Replace instruction " << (i+1) << " with " << replace;
          return ss.str();
         }
      }
    }
  }
  return "pouet";
}

/* Ignore and do not change the code below */

void trySolution(string recipe) {
  Json::Value output_json;
  output_json = Json::Value(recipe);

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

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> instructions = array;
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<int> array_2;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array_2.push_back(parsed_json[i].asInt());
  }
  vector<int> target = array_2;

  string output = findCorrectPath(instructions, target);
  trySolution(output);
}
/* Ignore and do not change the code above */

