#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
vector<char> help = {'+', '-', '*', '/'};

void calcute(vector<int> &arr, int target, string ans) {
    //保存之前得表达式
    string old = ans;

    //如果数组是空的，并且结果为24直接输出
    if (arr.empty()) {
        if (target == 24) {
            cout << ans << endl;
        }
        return;
    }

    //如果数组中还有数
    for (int i = 0; i < arr.size(); ++i) {
        //如果当前数和前一个数相等，直接跳过
        if (i > 0 && arr[i] == arr[i - 1])continue;

        //删除当前的数
        int tmp = arr[i];
        arr.erase(arr.begin() + i);


        //进行下一次计算
        string cur;
        for (int j = 0; j < help.size(); ++j) {
            //遍历所有得可能计算情况
            switch (help[j]) {
                case '+':
                    ans = old;
                    cur = "+" + to_string(tmp);
                    ans += cur;
                    calcute(arr, target + tmp, ans);
                    break;

                case '-':
                    //两种情况，清除target字符串重新增加
                    ans = old;
                    cur = to_string(tmp) + "-";
                    if (ans.length() >= 3)
                        ans = cur + "(" + ans + ")";
                    else ans = cur + ans;
                    calcute(arr, tmp - target, ans);

                    ans = old;
                    cur = "-" + to_string(tmp);
                    ans += cur;
                    calcute(arr, target - tmp, ans);

                    break;

                case '*':
                    ans = old;
                    cur = "*" + to_string(tmp);
                    if (ans.length() >= 3)
                        ans = "(" + ans + ")" + cur;
                    else ans += cur;
                    calcute(arr, target * tmp, ans);
                    break;

                case '/':
                    //两种情况
                    if (target != 0 && tmp % target == 0) {
                        ans = old;
                        cur = to_string(tmp) + "/";
                        if (ans.length() >= 3)
                            ans = cur + "(" + ans + ")";
                        else ans = cur + ans;
                        calcute(arr, tmp / target, ans);
                    }

                    if (tmp != 0 && target % tmp == 0) {
                        ans = old;
                        cur = "/" + to_string(tmp);
                        if (ans.length() >= 3)
                            ans = "(" + ans + ")" + cur;
                        else ans += cur;
                        calcute(arr, target / tmp, ans);
                    }
                    break;
            }
        }
        arr.insert(arr.begin() + i, tmp);
    }
}

int main() {
    string ans;
    vector<int> ori(4);

    //获取输入
    for (int i = 0; i < 4; ++i) {
        int tmp;
        cin >> tmp;
        if (tmp <= 0 || tmp >= 14) {
            cout << "输入非法字符" << endl;
            break;
        }
        ori[i] = tmp;
    }
    //数组排序是为了处理相同数字得重复选取
    sort(ori.begin(), ori.end());

    for (int i = 0; i < 4; ++i) {
        int tmp = ori[i];
        ori.erase(ori.begin() + i);

        if (i > 0 && ori[i] == ori[i - 1])continue;
        ans = to_string(tmp);
        calcute(ori, tmp, ans);
        ori.insert(ori.begin() + i, tmp);
    }
    return 0;
}