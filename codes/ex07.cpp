#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param wish_a The first wish.
 * @param wish_b The second wish.
 * @return The hybrid wish you created.
 */
string mixWishes(const string& wish_a, const string& wish_b) {
    int wish_a_length = wish_a.length();
    int wish_b_length = wish_b.length();

    vector<vector<int>> biggestSubsequenceLength(wish_a_length + 1, vector<int>(wish_b_length + 1, 0));

    for (int i = 1; i <= wish_a_length; ++i)
    {
        for (int j = 1; j <= wish_b_length; ++j)
        {
            if (wish_a[i - 1] == wish_b[j - 1])
                biggestSubsequenceLength[i][j] = biggestSubsequenceLength[i - 1][j - 1] + 1;
            else
                biggestSubsequenceLength[i][j] = max(biggestSubsequenceLength[i - 1][j], biggestSubsequenceLength[i][j - 1]);
        }
    }

    int i = wish_a_length;
    int j = wish_b_length;
    string result;

    while (i > 0 && j > 0)
    {
        if (wish_a[i - 1] == wish_b[j - 1])
        {
            result = wish_a[i - 1] + result;
            i--;
            j--;
        }
        else if (biggestSubsequenceLength[i - 1][j] > biggestSubsequenceLength[i][j - 1])
        {
            result = wish_a[i - 1] + result;
            i--;
        }
        else
        {
            result = wish_b[j - 1] + result;
            j--;
        }
    }

    while (i > 0)
    {
        result = wish_a[i - 1] + result;
        i--;
    }

    while (j > 0)
    {
        result = wish_b[j - 1] + result;
        j--;
    }

    return result;
}

/* Ignore and do not change the code below */

void trySolution(string mixed_ab) {
  Json::Value output_json;
  output_json = Json::Value(mixed_ab);

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
  string wish_a = parsed_json.asString();
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);
  string wish_b = parsed_json.asString();

  string output = mixWishes(wish_a, wish_b);
  trySolution(output);
}
/* Ignore and do not change the code above */

