#include "MyContainer.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    MyContainer newc(20,45);
    for(auto i = newc.begin(); i != newc.end(); ++i)
        cout << *i;
    {
        cout << endl;
        auto i = newc.begin();
        int j(20);
        for(;
            i != newc.end();
            ++i, --j
        )cout << (*i = j) << endl;
    }
    cout << "Subscript: " << newc[11] << endl;
    if(!newc.empty()){
        cout << "Not empty.\n";
        newc.clear();
        if(newc.empty())
            cout << "Now it is!\n";
        else cout << "Sill not empty...?\n";
    }else cout << "Empty?\n";

    if(newc.garbage_exists())
        cout << "Garbage already?\n";
    else{
        cout << "No garbage yet.\n";
        newc[7] = 67;
        if(newc.garbage_exists()){
            cout << "New garbage "
                << *(newc.garbage())
                << '\n';
        }else cout << "Still no garbage.\n";
    }
    MyContainer seccon;
    if(newc == seccon)
        cout << "Containers equal.\n";
    else{
        cout << "Containers not equal.\n";
        newc = seccon = MyContainer({4,7,1});
        if(newc == seccon)
            cout << "Now they're equal.\n";
        else cout << "Still inequivalent.\n";
    }
    for(
        auto iter(seccon.rbegin());
        iter != seccon.rend();
        --iter
    ) cout << *iter << '\n';

    MyContainer::iterator it(seccon.begin());
    it += 1;
    cout << *it << '\n';

    cout << endl;

    return 0;
}

#include <limits>
struct KeepRunning{
    ~KeepRunning(){
        cin.ignore(
            std::numeric_limits<
            std::streamsize>::max(),
            ' '
        );
    }
}__KR__;
