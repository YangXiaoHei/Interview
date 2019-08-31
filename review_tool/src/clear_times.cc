#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>

using namespace nlohmann;
using namespace std;


int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("usage : %s file_name module_name\n", argv[0]);
        exit(1);
    }

    string file_name = argv[1];
    string module = argv[2];

    json j;
    ifstream reader(file_name);
    reader >> j;
    reader.close();

    int count = 0;
    for (auto it = j.begin(); it != j.end(); it++) {
        if (it.key() == module) {
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
    }
    if (count) 
        cout << "\n\n --> 清理了 " << "[" << module <<  "] 共 "<< count << " 道题的复习次数" << endl;
    else
        cout << "[" << module << "]" << " 中没有复习过的题, 不需清理" << endl;

    ofstream writer(file_name);
    writer << setw(4) << j;
    writer.close();
}
