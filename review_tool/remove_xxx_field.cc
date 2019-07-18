#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

#define FILE_NAME "alg.json"

#define FIELD "last_time"
#define DEFAULT_VALUE 0

int main(int argc, char *argv[])
{
    json j;
    ifstream reader(FILE_NAME);
    reader >> j;
    reader.close();

    for (auto it = j.begin(); it != j.end(); it++) {
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            if (!entry.count(FIELD)) {
                cout << "❌ " << FIELD << " not exist, ignored... " << "[" << entry["desc"] << "]" << endl;
                continue;
            }
            entry.erase(FIELD);
            cout << FIELD << " remove succ! " << "[" << entry["desc"] << "]" << endl;
        }
    }

    ofstream writer(FILE_NAME);
    writer << setw(4) << j;
    writer.close();
}
