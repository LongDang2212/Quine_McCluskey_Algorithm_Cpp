#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// khuôn mẫu hàm check xem một đối tượng có ở trong 1 vector hay không
template <class T>
bool is_in_vector(T s, vector<T> v)
{
    for (auto i = v.begin(); i < v.end(); i++) // sử dụng iterator
    {
        if (*i == s)
            return true;
    }
    return false;
}
// khuôn mẫu hàm check xem 2 vector có bằng nhau hay không
template <class T>
bool vector_equal(vector<T> v1, vector<T> v2)
{
    if (v1.size() != v2.size())
        return false;
    else
    {
        for (int i = 0; i < v1.size(); i++)
        {
            if (v1.at(i) != v2.at(i))
                return false;
        }
    }
    return true;
}
// khuôn mẫu hàm để nối 2 vector
template <class T>
vector<T> vector_concatenate(vector<T> v1, vector<T> v2)
{
    for (int i = 0; i < v2.size(); i++)
    {
        v1.push_back(v2.at(i));
    }
    return v1;
}
string string_standardize(string);
string dec_to_bin(int);
int bin_to_dec(string);
vector<string> split(const string &, const string &);
bool is_combinable(string, string);
string replace_same_composition(string, string);
vector<vector<int>> find_root_minterm(vector<string>);
vector<string> expression_from_PI(string);
bool is_unnecessary(int, vector<vector<int>>);
bool is_essential(vector<int>);
vector<int> replace_vector_value(int, vector<int>);
vector<vector<int>> mark_essential(vector<vector<int>>);
bool is_necessary(int, vector<vector<int>>);
//main class
class QM
{
public:
    int vars;                           //  số lượng biến
    vector<string> var_char;            //chữ cái biểu diễn biến
    vector<int> minterms;               // số thứ tự của minterm
    vector<int> dont_care;              // số thứ tự của don't care
    vector<string> minterms_expression; // các biểu thức của minterm
    vector<string> prime_implicants;    // các biểu thức của PI
    vector<string> necessary;
    vector<vector<string>> one_for_all;
public:
    QM();
    void init();
    string bin_to_expression(string);
    string padding(string);
    void data_input();
    vector<string> reduce();
    void remove_unnecessary();
};
