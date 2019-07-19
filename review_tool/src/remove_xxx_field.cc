#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

string file_name, field;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage : %s file_name field\n", argv[0]);
        exit(1);
    }

    file_name = argv[1];
    field = argv[2];

    json j;
    ifstream reader(file_name);
    reader >> j;
    reader.close();

    for (auto it = j.begin(); it != j.end(); it++) {
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            if (!entry.count(field)) {
                cout << "❌ " << field << " not exist, ignored... " << "[" << entry["desc"] << "]" << endl;
                continue;
            }
            entry.erase(field);
            cout << field << " remove succ! " << "[" << entry["desc"] << "]" << endl;
        }
    }

    ofstream writer(file_name);
    writer << setw(4) << j;
    writer.close();
}
