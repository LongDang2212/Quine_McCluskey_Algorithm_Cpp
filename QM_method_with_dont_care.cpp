#include "function.hpp"

int main()
{

    QM a;
    a.init();
    a.data_input();
    auto x = a.minterms_expression;
    do
    {
        x.clear();
        x = a.reduce();
    } while (vector_equal(x, a.reduce()));
    a.remove_unnecessary();
    cout << "Ham toi thieu: " << endl;
    cout << a.bin_to_expression(a.necessary.at(0));
    for (int i = 1; i < a.necessary.size(); i++)
    {
        cout << "  +  " << a.bin_to_expression(a.necessary.at(i));
    }
    if (!a.one_for_all.empty())
    {
        cout << endl
             << " Cong them cac hang sau: " << endl;
        for (int i = 0; i < a.one_for_all.size(); i++)
        {
            for (int j = 0; j < a.one_for_all.at(i).size(); j++)
            {
                cout << " or " << a.bin_to_expression(a.one_for_all.at(i).at(j));
            }
            cout << endl;
        }
    }
    cout << endl;
    system("pause");
    return 0;
}