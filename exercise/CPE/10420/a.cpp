#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numLine;
    cin >> numLine;
    vector<pair<string, int>> countryMap;
    while (numLine--) {
        string country, trash;
        cin >> country >> trash >> trash;
        
        auto findIndex = countryMap.begin();
        for (; findIndex != countryMap.end(); findIndex++)
            if (findIndex->first == country)
                break;

        if (findIndex != countryMap.end())
            findIndex->second++;
        else
            countryMap.push_back(make_pair(country, 1));
    }
    sort(countryMap.begin(), countryMap.end());
    for (auto i : countryMap)
        cout << i.first << " " << i.second << endl;
    return 0;
}