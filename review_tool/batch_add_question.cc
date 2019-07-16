#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>

using namespace std;
using namespace nlohmann;

#define ADD_FILE "alg.add.json"
#define FILE_NAME "alg.json"
#define DEBUG_FILE "alg.debug.json"

int main(int argc, char *argv[])
{
    // 原有内容
    json raw_jsn;
    ifstream raw_reader(FILE_NAME);
    raw_reader >> raw_jsn;
    raw_reader.close();

    // 待合并的新内容
    json new_jsn;
    ifstream new_reader(ADD_FILE);
    new_reader >> new_jsn;
    new_reader.close();

    map<string, set<string>> exclude_dup;
    
    for (auto it = raw_jsn.begin(); it != raw_jsn.end(); it++) {
        string key = it.key();
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            string desc = it.value()[i]["desc"];
            if (exclude_dup.count(key)) {
                exclude_dup[key].insert(desc);
            } else {
                set<string> tmp_set;
                tmp_set.insert(desc);
                exclude_dup.insert( { key, tmp_set } );
            }
        }
    }

#ifdef DEBUG
    for (auto &it : exclude_dup) {
        cout << it.first << endl;
        for (auto &sit : it.second)
            cout << "\t\t" << sit << endl;
    }
#endif

    for (auto it = new_jsn.begin(); it != new_jsn.end(); it++) {
        string key = it.key();
        if (!raw_jsn.count(key))
            raw_jsn[key] = json::array();

        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &new_entry = it.value()[i];
            if (!new_entry.count("desc") ||
                !new_entry.count("times") || 
                !new_entry.count("last_time") ||
                !new_entry.count("diff") ||
                !new_entry.count("cost_time")) {
                cout << "format is invalid! ignore.. [" << new_entry << "]" << endl;
                continue;
            }

            string desc = new_entry["desc"];
            if (exclude_dup.count(key) && exclude_dup[key].count(desc)) {
                cout << "already exist! ignored.. [" << desc << "]" << endl;
                continue;
            }
            raw_jsn[key].push_back(new_entry);
            cout << "add succ! " << desc << endl;
        }
    }
    
    ofstream writer(FILE_NAME);
    writer << setw(4) << raw_jsn;
    writer.close();
}
