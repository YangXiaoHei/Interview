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

    cout << "将题目做过的次数清零..." << endl;
    for (auto it = j.begin(); it != j.end(); it++) {
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            entry["times"] = 0;
            entry["last_time"] = 0;
        }
    }

    ofstream writer(FILE_NAME);
    writer << setw(4) << j;
    writer.close();
    cout << "执行完毕" << endl;
}
