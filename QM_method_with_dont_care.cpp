#include "function.hpp"

int main()
{
    bool run = true;
x:
    if (run)
    {
        cout << endl
             << "Quine-McClusky algorithm!" << endl;
        QM a;
        a.init();
        a.data_input();
        a.processs();
        a.show_results();
        run = false;
        cout << endl
             << "Ban co muon thuc hien tiep?" << endl
             << "Nhap y hoac Y de tiep tuc!" << endl;
        char s;
        cin >> s;
        if (s == 'y' || s == 'Y')
            run = true;
        else
            cout << endl
                 << "Cam on ban. Hen gap lai!" << endl;

        goto x;
    }
    cout << endl;
    system("pause");
    return 0;
}