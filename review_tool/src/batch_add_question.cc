#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <map>
#include <set>

using namespace std;
using namespace nlohmann;

string file_name;
string add_file;

void refresh_id(json &raw_jsn)
{
    int idx = 1;
    for (auto it = raw_jsn.begin(); it != raw_jsn.end(); it++) {
        string key = it.key();
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            entry["id"] = to_string(idx++);
        }
    }
    cout << "refresh idx finished! total_question is " << idx - 1 << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage : %s file_name add_file\n", argv[0]);
        exit(1);
    }

    file_name = argv[1];
    add_file = argv[2];

    // 原有内容
    json raw_jsn;
    ifstream raw_reader(file_name);
    raw_reader >> raw_jsn;
    raw_reader.close();

    // 待合并的新内容
    json new_jsn;
    ifstream new_reader(add_file);
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

            // 格式校验
            if (!new_entry.count("desc") ||
                !new_entry.count("diff") ||
                !new_entry.count("cost_time")) {
                cout << "format is invalid! ignore.. [" << new_entry << "]" << endl;
                continue;
            }

            // 排重
            string desc = new_entry["desc"];
            if (exclude_dup.count(key) && exclude_dup[key].count(desc)) {
                cout << "already exist! ignored.. [" << desc << "]" << endl;
                continue;
            }

            // 内部添加字段
            if (!new_entry.count("times"))
                new_entry["times"] = 0;

            if (!new_entry.count("last_time"))
                new_entry["last_time"] = 0;

            long cur_time = (long)time(NULL);
            if (!new_entry.count("init_time"))
                new_entry["init_time"] = cur_time;

            if (!new_entry.count("tmp_ignore"))
                new_entry["tmp_ignore"] = 0;

            raw_jsn[key].push_back(new_entry);
            cout << "add succ! " << desc << " init_time = " << new_entry["init_time"] << endl;
        }
    }

    // 刷新序号
    refresh_id(raw_jsn);
    
    ofstream writer(file_name);
    writer << setw(4) << raw_jsn;
    writer.close();
}
