#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <iomanip>

using namespace std;
using namespace nlohmann;

#define FILE_NAME "alg.json"

string get_last_expr(long lasttime)
{
    long cur = (long)time(NULL);
    long diff = cur - lasttime;

    if (diff <= 0)
        return "oh my god!";

    if (diff < 60) 
        return to_string(diff) + " 秒前";

    diff /= 60;
    if (diff < 60)
        return to_string(diff) + " 分钟前";

    diff /= 60;
    if (diff < 24)
        return to_string(diff) + " 小时前";

    diff /= 24;
    if (diff < 30)
        return to_string(diff) + " 天前";

    diff /= 30;
    if (diff < 12)
        return to_string(diff) + " 月前";

    diff /= 12;
    return to_string(diff) + " 年前";
}

struct entry {
    string desc;
    int times;
    int diff;
    int cost_time;
    long last_time;
    string get_diff_desc() {
        string s;
        for (int i = 0; i < diff; i++)
            s += "🌟";
        return s;
    }
    void output(int i = 0) {
        cout << "\t第 " << i << "道题" << endl; 
        cout << "\t\t" << "题目描述 : " << desc << endl;
        cout << "\t\t" << "难度 : " << get_diff_desc() << endl; 
        if (last_time <= 0)
            cout << "\t\t" << "还未复习过" << endl;
        else
            cout << "\t\t" <<  "复习过 " << times << " 次, 上次复习在 " << get_last_expr(last_time) << endl; 
        cout << "\t\t" << "预计耗时 :" << cost_time << " 分钟" << endl;
        cout << endl;
    }
    entry(const string &s, int d, int t, int c, long l) : desc(s), diff(d), times(t), cost_time(c), last_time(l) {}
};

void shuffle_vec(vector<entry> &vec)
{
    for (int i = 0; i < vec.size(); i++) {
        int r = rand() % (vec.size() - i); 
        entry t = vec[i];
        vec[i] = vec[r];
        vec[r] = t; 
    }
}

string get_time_fmt(void)
{
    struct tm *tmbuf;
    time_t cur = time(NULL);
    tmbuf = localtime(&cur);
    string s;
    int year = tmbuf->tm_year + 1900;
    int mon = tmbuf->tm_mon + 1;
    int day = tmbuf->tm_mday;
    int hour = tmbuf->tm_hour;
    int min = tmbuf->tm_min;
    char buf[100];
    snprintf(buf, sizeof(buf), "%04d/%02d/%02d/ %02d:%02d", year, mon, day, hour, min);
    return string(buf);
}

void handle_selected(json &to_modify, const string &module, const vector<entry> &selected)
{
    json &m = to_modify[module]; 
    for (int i = 0; i < selected.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            if (m[j]["desc"] == selected[i].desc) {
                m[j]["times"] = m[j]["times"].get<int>() + 1;
                m[j]["last_time"] = (long)time(NULL);
            }
        }
    }

    ofstream writer(FILE_NAME);
    writer << setw(4) << to_modify;
    writer.close();
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));

    // 总耗时
    int total_cost = 120;
    int total_num = 5;

    // 读取 json 配置
    ifstream reader(FILE_NAME);
    json jsn_content;
    reader >> jsn_content;
    reader.close();

    cout << endl;

    // 挑选一个主题
    int module_idx = rand() % jsn_content.size();
    auto module_it = jsn_content.begin();
    int i = 0;
    for (; module_it != jsn_content.end(); ++module_it)
        if (i++ == module_idx)
            break;
    cout << "\t" << get_time_fmt() << " 复习主题 -> 【 " << module_it.key() << " 】" << endl;
    if (!module_it.value().is_array()) {
        cout << "must be array!" << endl;
        return -1;
    }

    // 将该主题中所有题目按照挑选次数放入 map
    map<int, vector<entry>> times_map;
    for (int i = 0; i < module_it.value().size(); i++) {
        string desc = module_it.value()[i]["desc"];
        int diff = module_it.value()[i]["diff"];
        int times = module_it.value()[i]["times"];
        int cost_time = module_it.value()[i]["cost_time"];
        long last_time = module_it.value()[i]["last_time"];
        entry e(desc, diff, times, cost_time, last_time);

        if (times_map.count(times)) 
            times_map.find(times)->second.push_back(e);
        else {
            vector<entry> vec;
            vec.push_back(e);
            times_map.insert({ times, vec });
        }
    }

    // 挑选一批题目，总耗时不得超过 total_time, 最多 5 道题
    vector<entry> result;
    int tmpcost = 0;
    for (auto it = times_map.begin(); it != times_map.end(); it++) {
        shuffle_vec(it->second);
        for (int i = 0; i < it->second.size(); i++) {
            const entry &e = it->second[i];
            tmpcost += e.cost_time;
            result.push_back(e);
            if (tmpcost >= total_cost || result.size() >= total_num)
                goto finish;
        } 
    }

    // 打印所选的题目
finish:
    cout << "\t预计耗时 : " << tmpcost << endl;
    cout << "\t题目数量: " << result.size() << endl;
    cout << endl;
    int qi = 0;
    for (auto it : result)
        it.output(++qi);

    // 更新已选题目做过的次数和本次复习的时间
    handle_selected(jsn_content, module_it.key(), result);

    cout << endl;
}
