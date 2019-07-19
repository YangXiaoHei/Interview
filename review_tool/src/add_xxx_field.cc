#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

string file_name;
string field;
string type;

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("usage : %s file_name field type\n", argv[0]);
        exit(1);
    }

    file_name = argv[1];
    field = argv[2];
    type = argv[3];

    json j;
    ifstream reader(file_name);
    reader >> j;
    reader.close();

    for (auto it = j.begin(); it != j.end(); it++) {
        int size = it.value().size();
        for (int i = 0; i < size; i++) {
            json &entry = it.value()[i];
            if (entry.count(field)) {
                cout << "❌ " << field << " already exist! " << "[" << entry["desc"] << "]" << endl;
                continue;
            }
            if (type == "int")
                entry[field] = 0;
            else if(type == "float")
                entry[field] = 0.0;
            else if (type == "string")
                entry[field] = "";
            else {
                cout << "unsupported type!" << endl; 
                exit(1);
            }
            cout << field << " add succ! " << "[" << entry["desc"] << "]" << endl;
        }
    }

    ofstream writer(file_name);
    writer << setw(4) << j;
    writer.close();
}
