#include "function.hpp"

// chuyển thập phân sang nhị phân
string dec_to_bin(int n)
{
    if (n == 0)
        return n + "";

    if (n % 2 == 0)
        return dec_to_bin(n / 2) + "0";
    else
        return dec_to_bin(n / 2) + "1";
}
// hàm check xem hàng của 1 PI có dấu tích hay không
bool is_necessary(int n, vector<vector<int>> v)
{
    int checked = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v.at(i).at(n) == 2)
            checked++;
    }
    return (checked != 0);
}
// hàm check xem một cột chỉ có 1 dấu tích
bool is_essential(vector<int> v)
{
    int count = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v.at(i) != 0)
            count++;
    }
    return (count == 1);
}

// hàm chuẩn hoá chuỗi, loại bỏ ký tự không liên quan(không phải số và dấu ,)
string string_standardize(string s)
{
    string temp = s;
    if (s == "None" || s == "none")
        return "";
    else
    {

        for (int i = 0; i < temp.length(); i++)
        {
            if (temp[i] == ',')
                continue;
            if (temp[i] < '0' || temp[i] > '9')
            {
                temp.erase(temp.begin() + i--);
            }
        }
    }
    return temp;
}
// Dò ma trận, đặt các giá trị essential(dấu tích) thành 2
vector<vector<int>> mark_essential(vector<vector<int>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (is_essential(v.at(i)))
        {
            for (int j = 0; j < v.at(i).size(); j++)
            {
                if (v.at(i).at(j) == 1)
                    v.at(i).at(j) = 2;
            }
        }
    }
    return v;
}
//hàm chuyển nhị phân sang thập phân
int bin_to_dec(string bin)
{
    int dec = 0;
    for (int i = 0; i < bin.size(); i++)
    {
        dec += (bin[i] == '1' ? 1 : 0) * pow(2, bin.size() - 1 - i);
    }
    return dec;
}
// hàm tạo các chuỗi đầy đủ từ PI
// 01-- => 0110 & 0100 & 0111  & 0101
vector<string> expression_from_PI(string p)
{
    vector<string> temp;
    for (int i = 0; i < p.length(); i++)
    {
        if (p[i] == '-')
            return vector_concatenate(expression_from_PI(p.replace(i, 1, "0")), expression_from_PI(p.replace(i, 1, "1")));
    }
    temp.push_back(p);
    return temp;
}
// hàm tách nội dung từ chuỗi str, các nội dung cách nhau bởi chuỗi delim
vector<string> split(const string &str, const string &delim)
{
    vector<string> tokens;    // tạo một vector<string> tokens, là vector lưu các kết quả được tách ra
    size_t prev = 0, pos = 0; // size_t là kiểu unsigned long long, giống int nhưng to hơn
    do
    {
        pos = str.find(delim, prev);                     // tìm pos là vị trí của chuỗi delim trong chuỗi str, bắt đầu tìm từ vị trí prev
        if (pos == string::npos)                         // pos == string::npos là không tìm thấy gì
            pos = str.length();                          // không tìm thấy thì gán pos bằng độ dài chuỗi str(vòng lặp sẽ kết thúc)
        string token = str.substr(prev, pos - prev);     // token là 1 nội dung được lấy ra bằng substr, độ dài từ vị trí prev đến bị trí pos-prev(ngay trước chuỗi delim vừa tìm thấy)
        if (!token.empty())                              // nếu nội dung không rỗng
            tokens.push_back(token);                     // thêm nội dung vào vector
        prev = pos + delim.length();                     // gán prev là vị trí của dấu phẩy vừa tìm thấy
    } while (pos < str.length() && prev < str.length()); // điều kiện để vòng lặp chạy: pos và prev nhỏ hơn độ dài chuỗi str
    return tokens;
}
// check xem 2 chuỗi có thể kết hợp với nhau không
bool is_combinable(string s1, string s2)
{
    int flag = 0;
    if (s1.length() != s2.length())
        return false;
    else
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s1[i] != s2[i])
                flag++;
        }
        return (flag == 1);
    }
}

// hàm thay thế phần tử khác nhau duy nhất của 2 chuỗi thành dấu "-"
string replace_same_composition(string s1, string s2)
{
    string temp = "";
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] == s2[i])
        {
            temp += s1[i];
        }
        else
        {
            temp += "-";
        }
    }
    return temp;
}
// hàm tìm các minterm gốc tạo ra PI
vector<vector<int>> find_root_minterm(vector<string> v)
{
    vector<vector<int>> temp;
    for (int i = 0; i < v.size(); i++)
    {
        vector<string> t1 = expression_from_PI(v.at(i));
        vector<int> v1;
        for (int i = 0; i < t1.size(); i++)
        {
            v1.push_back(bin_to_dec(t1.at(i)));
        }
        temp.push_back(v1);
    }
    return temp;
}
QM::QM()
{
    vars = 0;
}
void QM::init()
{
    int n = -1;
    while (n <= 0)
    {
        cout << "Nhap so bien: ";
        cin >> n;
        cout << endl;
    }
    this->vars = n;
    for (int i = 0; i < this->vars; i++)
    {
        var_char.push_back(string(1, ('a' + i)));
    }
}
// chuyển nhị phân về dạng biểu thức
string QM::bin_to_expression(string bin)
{
    string exprression = "";
    for (int i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            exprression.append(var_char.at(i));
        }
        else if (bin[i] == '0')
        {
            exprression.append(var_char.at(i) + "'");
        }
    }
    return exprression;
}
// padding function
// Eg: vars = 4; 5 = 101 => 0101
string QM::padding(string bin)
{
    for (int i = bin.length(); i < vars; i++)
        bin = "0" + bin;
    return bin;
}
// hàm nhập các minterm và dont care
void QM::data_input()
{
    string input, input1;
    cout << "Nhap cac chi so don't care(0-" << pow(2, vars) - 1 << ", phan cach boi dau , neu khong co thi nhap None): ";
    cin.ignore();
    getline(cin, input);
    input = string_standardize(input);
    auto v2 = split(input, ",");
    for (int i = 0; i < v2.size(); i++)
    {
        if (!is_in_vector(padding(dec_to_bin(stoi(v2.at(i)))), minterms_expression))
        {
            minterms_expression.push_back(padding(dec_to_bin(stoi(v2.at(i)))));
            dont_care.push_back(stoi(v2.at(i)));
        }
    }
    string name = min_or_max ? "minterm" : "maxterm";
    cout << "Nhap cac chi so " << name
         << "(0-" << pow(2, vars) - 1 << ", phan cach boi dau ,): ";
    //ncin.ignore();
    getline(cin, input1);
    input1 = string_standardize(input1);
    if (!min_or_max)
        input1 = maxterm_2_minterm(input1, input);
    auto v1 = split(input1, ",");
    for (int i = 0; i < v1.size(); i++)
    {
        if (!is_in_vector(padding(dec_to_bin(stoi(v1.at(i)))), minterms_expression))
        {
            minterms_expression.push_back(padding(dec_to_bin(stoi(v1.at(i)))));
            minterms.push_back(stoi(v1.at(i)));
        }
    }
}

// hàm tối thiểu các minterm
vector<string> QM::reduce()
{
    vector<string> new_minterm_expression;
    int size = minterms_expression.size();
    vector<int> check(size, 0);
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (is_combinable(minterms_expression.at(i), minterms_expression.at(j)))
            {
                check.at(i)++;
                check.at(j)++;
                string new_expression = replace_same_composition(minterms_expression.at(i), minterms_expression.at(j));
                if (!is_in_vector(new_expression, new_minterm_expression))
                {
                    new_minterm_expression.push_back(new_expression);
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (check.at(i) == 0)
            prime_implicants.push_back(minterms_expression.at(i));
    }

    minterms_expression.clear();
    minterms_expression = new_minterm_expression;
    return minterms_expression;
}
// hàm loại bỏ các PI không cần thiết
void QM::remove_unnecessary()
{
    vector<int> un;
    prime_implicants = vector_concatenate(minterms_expression, prime_implicants);
    remove_same_in_vector(prime_implicants);
    auto v = find_root_minterm(prime_implicants);
    cout << "Cac minterm tao thanh PI:" << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << "PI" << i + 1 << ": ";
        for (int j = 0; j < v.at(i).size(); j++)
            cout << v.at(i).at(j) << "\t";
        cout << endl;
    }
    // cout << endl;
    // for (int i = 0; i < minterms.size(); i++)
    //     cout << minterms.at(i) << "\t";
    // cout << endl;
    vector<vector<int>> x(minterms.size(), vector<int>(v.size(), 0)); // ma trận PI - minterm
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x.at(0).size(); j++)
        {
            if (is_in_vector(minterms.at(i), v.at(j)))
                x.at(i).at(j)++;
        }
    }
    cout << "Ma tran cac PI va cac minterm:" << endl;
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x.at(0).size(); j++)
            cout << x.at(i).at(j) << "\t";
        cout << endl;
    }
    x = mark_essential(x);
    cout << "Ma tran sau khi xu ly, tim cac essential: " << endl;
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x.at(i).size(); j++)
            cout << x.at(i).at(j) << "\t";
        cout << endl;
    }
    for (int i = 0; i < prime_implicants.size(); i++)
    {
        if (is_necessary(i, x))
            necessary.push_back(prime_implicants.at(i));
    }
    for (int i = 0; i < x.size(); i++)
    {
        vector<string> c;
        if (!is_essential(x.at(i)))
        {
            bool flag = true;
            for (int j = 0; j < x.at(i).size(); j++)
            {
                if (x.at(i).at(j) != 0)
                {
                    if (is_necessary(j, x))
                        flag = false;
                }
            }
            if (flag)
            {
                for (int j = 0; j < x.at(i).size(); j++)
                {
                    if (x.at(i).at(j) != 0)
                    {
                        if (!is_necessary(j, x))
                            c.push_back(prime_implicants.at(j));
                    }
                }
            }
        }
        if (!c.empty())
            one_for_all.push_back(c);
    }
}
void QM::processs()
{
    auto x = minterms_expression;
    do
    {
        x.clear();
        x = this->reduce();
    } while (vector_equal(x, this->reduce()));
    vector<string> new_minterm_expression;
    int size = minterms_expression.size();
    vector<int> check(size, 0);
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (is_combinable(minterms_expression.at(i), minterms_expression.at(j)))
            {
                check.at(i)++;
                check.at(j)++;
                string new_expression = replace_same_composition(minterms_expression.at(i), minterms_expression.at(j));
                if (!is_in_vector(new_expression, new_minterm_expression))
                {
                    new_minterm_expression.push_back(new_expression);
                }
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (check.at(i) == 0)
            prime_implicants.push_back(minterms_expression.at(i));
    }
    minterms_expression.clear();
    minterms_expression = new_minterm_expression;
    this->remove_unnecessary();
}
void QM::show_results()
{
    if (min_or_max)
    {
        cout << "Ham toi thieu: " << endl;
        cout << this->bin_to_expression(this->necessary.at(0));
        for (int i = 1; i < this->necessary.size(); i++)
        {
            cout << "  +  " << this->bin_to_expression(this->necessary.at(i));
        }
        if (!this->one_for_all.empty())
        {
            cout << endl
                 << " Cong them cac hang sau: " << endl;
            for (int i = 0; i < this->one_for_all.size(); i++)
            {
                cout << i + 1 << ".   ";
                for (int j = 0; j < this->one_for_all.at(i).size(); j++)
                {
                    cout << " or " << this->bin_to_expression(this->one_for_all.at(i).at(j));
                }
                cout << endl;
            }
        }
    }
    else
    {
        cout << "Ham toi thieu: " << endl;
        cout << "(" << this->bin_to_expression_maxterm(this->necessary.at(0)) << ")";
        for (int i = 1; i < this->necessary.size(); i++)
        {
            cout << "  *  (" << this->bin_to_expression_maxterm(this->necessary.at(i)) << ")";
        }
        if (!this->one_for_all.empty())
        {
            cout << endl
                 << " Nhan them cac hang sau: " << endl;
            for (int i = 0; i < this->one_for_all.size(); i++)
            {
                cout << i + 1 << ".   ";
                for (int j = 0; j < this->one_for_all.at(i).size(); j++)
                {
                    cout << " or (" << this->bin_to_expression_maxterm(this->one_for_all.at(i).at(j)) << ")";
                }
                cout << endl;
            }
        }
    }
}
// các hàm dưới đây dùng để xử lý trong trường hợp input là Maxterm
string QM::bin_to_expression_maxterm(string bin)
{
    string exprression = "";
    if (bin[0] == '0')
    {

        exprression.append(var_char.at(0));
    }
    else if (bin[0] == '1')
    {

        exprression.append(var_char.at(0) + "'");
    }
    else
    {
        exprression.append("None");
    }

    for (int i = 1; i < bin.length(); i++)
    {
        if (bin[i] == '0')
        {
            exprression.append(" + ");
            exprression.append(var_char.at(i));
        }
        else if (bin[i] == '1')
        {
            exprression.append(" + ");
            exprression.append(var_char.at(i) + "'");
        }
    }
    return exprression;
}
void QM::set_type(int i)
{
    if (i == 1)
        this->min_or_max = true;
    else
        this->min_or_max = false;
}
string QM::maxterm_2_minterm(string s, string s1)
{
    string temp;
    auto v1 = split(s, ",");
    auto v2 = split(s1, ",");
    vector<int> temp1, temp2;
    for (int i = 0; i < v1.size(); i++)
    {
        temp1.push_back(stoi(v1.at(i)));
    }
    for (int i = 0; i < v2.size(); i++)
    {
        temp2.push_back(stoi(v2.at(i)));
    }
    for (int i = 0; i < pow(2, vars); i++)
    {
        if (!is_in_vector(i, temp1) && !is_in_vector(i, temp2))
        {
            temp.append(to_string(i));
            temp.append(",");
        }
    }
    cout << endl
         << "Maxterm:\t" << s << endl;
    cout << endl
         << "Don't care:\t" << s1 << endl;
    cout << endl
         << "Minterm:\t" << temp << endl;
    return temp;
}
