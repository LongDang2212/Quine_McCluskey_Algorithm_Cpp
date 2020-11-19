#include "function.hpp"

int main()
{
    bool run = true;
x:
    if (run)
    {
        cout << endl
             << "Quine-McClusky algorithm!" << endl;
        cout << "1. Minterm" << endl
             << "2. Maxterm" << endl
             << "3. Exit" << endl;
        int select;
        cout << endl
             << "Nhap lua chon: ";
        cin >> select;
        QM a;
        switch (select)
        {
        case 1:
        {
            a.set_type(1);
            cout << endl
                 << "Minterm!" << endl;
            break;
        }
        case 2:
        {
            a.set_type(2);
            cout << endl
                 << "Maxterm!" << endl;
            break;
        }
        case 3:
        {
            run = false;
            goto x;
        }

        default:
        {
            cout << endl
                 << "So da nhap khong hop le! Vui long thu lai." << endl;
            goto x;
        }
        }

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
