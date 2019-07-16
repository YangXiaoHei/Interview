#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>

using namespace nlohmann;
using namespace std;

#define FILE_NAME "alg.json"

int main(int argc, char *argv[])
{
    json j;
    ifstream reader(FILE_NAME);
    reader >> j;
    reader.close();

    int count = 0;
    for (auto it = j.begin(); it != j.end(); it++) {
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            if (entry["times"].get<int>() > 0) {
                count++;
                cout << "清除复习次数 succ! -> [" << entry["desc"] << "]" << endl; 
                entry["times"] = 0;
                entry["last_time"] = 0;
            }
        }
    }
    if (count) 
        cout << "清理了 " << count << " 道题的复习次数" << endl;

    ofstream writer(FILE_NAME);
    writer << setw(4) << j;
    writer.close();
}
