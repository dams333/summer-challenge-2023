#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <algorithm>
using namespace std;



/**
 * @param file_contents A list of strings, where each string represents the contents of a file.
 * @return The contents of the merged file.
 */
string mergeFiles(vector<string> file_contents) {
  map<string, map<string, string>> mutants;
  for (auto it = file_contents.begin(); it != file_contents.end(); it++)
  {
    stringstream stream(*it);
    string str;
    while (getline(stream, str))
    {
      stringstream stream2(str);
      string elem;
      map<string, string> mutant;
      while (getline(stream2, elem, ';'))
      {
        auto sep = elem.find("=");
        string key(elem, 0, sep);
        string value(elem, sep + 1, elem.length());
        mutant.insert(make_pair(key, value));
      }
      string name = mutant["Name"];
      mutant.erase(mutant.find("Name"));
      mutants[name].insert(mutant.begin(), mutant.end());
    }
  }
  std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> mutantsAsVector;

  for (const auto& mutant : mutants) {
    std::pair<std::string, std::vector<std::pair<std::string, std::string>>> mutantPair;
    mutantPair.first = mutant.first;

    for (const auto& innerPair : mutant.second) {
      mutantPair.second.push_back(innerPair);
    }

    std::sort(mutantPair.second.begin(), mutantPair.second.end(),
      [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    mutantsAsVector.push_back(mutantPair);
  }

  std::sort(mutantsAsVector.begin(), mutantsAsVector.end(),
    [](const auto& a, const auto& b) {
      return a.first < b.first;
  });
  string res;
  for (auto it = mutantsAsVector.begin(); it != mutantsAsVector.end(); it++)
  {
    res += "Name=" + it->first;
    for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
    {
      res += ";" + it2->first + "=" + it2->second;
    }
    res += "\n";
  }
  res.erase(res.end() - 1);
  return res;
}

/* Ignore and do not change the code below */

void trySolution(string merged_file) {
  Json::Value output_json;
  output_json = Json::Value(merged_file);

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
  vector<string> file_contents = array;

  string output = mergeFiles(file_contents);
  trySolution(output);
}
/* Ignore and do not change the code above */

