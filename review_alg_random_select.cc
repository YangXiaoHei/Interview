#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace nlohmann;

void shuffle_vec(vector<int> &vec)
{
    for (int i = 0; i < vec.size(); i++) {
        int r = rand() % (vec.size() - i); 
        int t = vec[i];
        vec[i] = vec[r];
        vec[r] = t; 
    }
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

    int nselect = 5;
    if (argc == 2)
        nselect = atoi(argv[1]);

    ifstream reader("alg.json");

    json j;
    reader >> j;

    int i = 0;
    int module_idx = rand() % j.size();
    auto it = j.begin();
    for (; it != j.end(); it++) {
        if (i++ == module_idx) {
            cout << "choose module : " << it.key() << endl;
            break;
        }
    }

    if (!it->is_array()) {
        cout << "must be array!" << endl;
        return -1;
    }

    vector<int> idx_vec;
    for (int i = 0; i < it->size(); i++)
        idx_vec.push_back(i);

    shuffle_vec(idx_vec);

    int ns = 0;
    for (int i = 0; i < it->size(); i++) {
        if (ns++ >= nselect)
            break;
        cout << it.value()[idx_vec[i]] << endl;
    }

    ofstream writer("output_alg.json");
    writer << j << endl;
}
