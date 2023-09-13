#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param mutant_scores The score corresponding to each mutant
 * @param threshold The score threshold above which mutants should be ignored
 * @return 
 */
string bestRemainingMutant(map<string, double> mutant_scores, int threshold) {
  // Write your code here
  string bestName;
  double bestScore = -1;

  for (auto it = mutant_scores.begin(); it != mutant_scores.end(); it++)
  {
    if (it->second <= threshold)
    {
      if (bestScore == -1)
      {
        bestScore = it->second;
        bestName = it->first;
      }
      else
      {
        if (bestScore < it->second)
        {
          bestScore = it->second;
        bestName = it->first;
        }
      }
    }
  }

  return bestName;
}

/* Ignore and do not change the code below */

void trySolution(string output) {
  Json::Value output_json;
  output_json = Json::Value(output);

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

  map<string, double> dict;
  for(Json::Value::const_iterator itr = parsed_json.begin(); itr != parsed_json.end(); itr++ ) {
    dict.insert(std::pair<string,double>(itr.key().asString().c_str(), (*itr).asDouble()));
  }
  map<string, double> mutant_scores = dict;

  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);
  int threshold = parsed_json.asInt();

  string output = bestRemainingMutant(mutant_scores, threshold);
  trySolution(output);
}
/* Ignore and do not change the code above */

