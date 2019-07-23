#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <iomanip>

using namespace std;
using namespace nlohmann;

int total_num = 5; // 题目数量限制
int total_cost = 120; // 复习时间限制
string file_name, bk_file;

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
    long init_time;
    int tmp_ignore;
    string id;
    string get_diff_desc() {
        string s;
        for (int i = 0; i < diff; i++)
            s += "🌟";
        return s;
    }
    void output(int i = 0) {
        cout << "\t第 " << i << " 道题 " << "(" << id << ")"<< endl; 
        cout << "\t\t" << "题目描述 : " << desc << endl;
        cout << "\t\t" << "难度 : " << get_diff_desc() << endl; 
        if (last_time <= 0)
            cout << "\t\t" << "还未复习过" << endl;
        else
            cout << "\t\t" <<  "复习过 " << times << " 次, 上次复习在 " << get_last_expr(last_time) << endl; 
        cout << "\t\t" << "预计耗时 :" << cost_time << " 分钟" << endl;
        cout << endl;
    }
    entry(const string &s, int d, int t, int c, long l, const string &i, long itime, int ignore) : desc(s), diff(d), times(t), cost_time(c), last_time(l), id(i), init_time(itime), tmp_ignore(ignore) {}
};

void shuffle_vec(vector<entry> &vec)
{
    for (int i = 0; i < vec.size(); i++) {
        int r = i + rand() % (vec.size() - i); 
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
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d", year, mon, day, hour, min);
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

    ofstream writer(file_name);
    writer << setw(4) << to_modify;
    writer.close();
}

bool entry_comparator(const entry &a, const entry &b)
{
    return a.last_time < b.last_time;
}

void scheme_random_module(json &jsn_content, string &selected_module, vector<entry> &result)
{
    if (jsn_content.empty()) {
        cout << "empty module!" << endl;
        exit(1);
    }

    cout << endl;

    // 挑选一个主题
    int module_idx = rand() % jsn_content.size();
    auto module_it = jsn_content.begin();
    int i = 0;
    for (; module_it != jsn_content.end(); ++module_it)
        if (i++ == module_idx)
            break;
    cout << "\t" << get_time_fmt() << " 复习主题 -> 【 " << module_it.key() << " 】" << endl;
    selected_module = module_it.key();
    if (!module_it.value().is_array()) {
        cout << "must be array!" << endl;
        exit(1);
    }

    // 将该主题中所有题目按照挑选次数放入 map
    map<int, vector<entry>> times_map;
    for (int i = 0; i < module_it.value().size(); i++) {
        const json &jsn_entry = module_it.value()[i];
        string desc = jsn_entry["desc"];
        int diff = jsn_entry["diff"];
        int times = jsn_entry["times"];
        int cost_time = jsn_entry["cost_time"];
        long last_time = jsn_entry["last_time"];
        long init_time = jsn_entry["init_time"];
        int tmp_ignore = jsn_entry["tmp_ignore"];
        string id = jsn_entry["id"];
        entry e(desc, diff, times, cost_time, last_time, id, init_time, tmp_ignore);

        if (times_map.count(times)) 
            times_map.find(times)->second.push_back(e);
        else {
            vector<entry> vec;
            vec.push_back(e);
            times_map.insert({ times, vec });
        }
    }

    long cur_time = (long)time(NULL);

    // 挑选一批题目，总耗时不得超过 total_time, 最多 total_num 道题
    int tmpcost = 0;
    for (auto it = times_map.begin(); it != times_map.end(); it++) {
        sort(it->second.begin(), it->second.end(), entry_comparator);
        for (int i = 0; i < it->second.size(); i++) {
            const entry &e = it->second[i];

            // 忽略被置上这个位的题
            if (e.tmp_ignore)
                continue;

            // 防止新做的题，刚加进去，就被选出来复习...
            if (e.last_time <= 0 && cur_time - e.init_time < 8 * 60 * 60)
                continue;

            tmpcost += e.cost_time;
            result.push_back(e);
            if (tmpcost >= total_cost || result.size() >= total_num)
                goto finish;
        } 
    }

    // 打印所选的题目
finish:
    shuffle_vec(result);
    cout << "\t预计耗时 : " << tmpcost << endl;
    cout << "\t题目数量: " << result.size() << endl;
    cout << endl;
    int qi = 0;
    for (auto it : result)
        it.output(++qi);
    cout << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("usage : %s file_name bk_file total_num total_cost\n", argv[0]);
        exit(1);
    }

    file_name = argv[1];
    bk_file = argv[2];
    total_num = atoi(argv[3]);
    total_cost = atoi(argv[4]);

    srand((unsigned)time(NULL));

    // 读取 json 配置
    ifstream reader(file_name);
    json jsn_content;
    reader >> jsn_content;
    reader.close();

    // 备份
    ofstream writer(bk_file);
    writer << setw(4) << jsn_content;
    writer.close();

    // 随机选主题策略
    vector<entry> result;
    string select_module;
    scheme_random_module(jsn_content, select_module, result);

    // 更新已选题目做过的次数和本次复习的时间
    handle_selected(jsn_content, select_module, result);
}
