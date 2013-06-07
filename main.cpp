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
    cout << "seccon size: " << seccon.size() << '\n'
        << "seccon capacity: " << seccon.capacity() << '\n';
    cout << "Reverse iterator: \n";
    for(
        auto iter(seccon.rbegin());
        iter != seccon.rend();
        ++iter
    ) cout << *iter << '\n';
    cout << "Normal iterator: \n";
    for(
        auto iter(seccon.begin());
        iter != seccon.end();
        ++iter
    ) cout << *iter << '\n';
    cout << "Operator tests: \n";
    MyContainer::iterator it(seccon.begin());
    cout << "it position: " << it.Position() << '\n';
    it += 1;
    cout << *it << '\n';
    MyContainer::reverse_iterator it2(seccon.rbegin());
 //   it2 -= 1;
    cout << std::boolalpha << it2.Invalid() << '\n';
    cout << *it2 << '\n';

    int isle(5);
    MyContainer::iterator it3(&isle,0);
    cout << *it3 << ':' << it3.Position() << '\n';
    cout << "Pushing back new values to seccon...\n";
    for(int o(0); o < 20; ++o)
        seccon.push_back(o-10);
    cout << "New seccon: " << endl;
    for(auto iter(seccon.begin()); iter != seccon.end(); ++iter)
        cout << *iter << endl;
    cout << "New seccon size and capacity: "
        << seccon.size() << ':' << seccon.capacity() << '\n';
    cout << "Push_back_Steal from newc to seccon...\n";
    seccon.push_back_steal(newc);
    cout << "New newc size and capacity: "
        << newc.size() << ':' << newc.capacity() << '\n';
    cout << "New seccon:\n";
    for(auto iter(seccon.begin()); iter != seccon.end(); ++iter)
        cout << *iter << endl;
    cout << "New seccon size and capacity: "
        << seccon.size() << ':' << seccon.capacity() << '\n';
    newc.push_back_steal(isle);
    cout << "newc steals isle; new values: "
        << *(newc.begin()) << ':' << isle << '\n';
    newc.push_back(5);
    newc.push_back(5);
    newc.insert(1,7);
    cout << "New newc after insert:\n";
    for(auto iter(newc.begin()); iter != newc.end(); ++iter)
        cout << *iter << endl;

    auto it5(newc.begin());
        it5 += 2;
        newc.insert(it5,65);
    cout << "insert at it5 of newc. New newc:\n";
    for(auto iter(newc.begin()); iter != newc.end(); ++iter)
        cout << *iter << endl;
    if(newc.garbage_exists())
        cout << "Garbage check: " << *(newc.garbage()) << '\n';

    auto it4(seccon.begin());
        it4 += 11;
    it5 = newc.begin();
    newc.insert(it5, seccon.begin(), it4);
    cout << "it4(" << *it4 << ") insert into newc. New newc:\n";
    for(auto iter(newc.begin()); iter != newc.end(); ++iter)
        cout << *iter << endl;
    if(newc.garbage_exists())
        cout << "Garbage Check: " << *(newc.garbage()) << '\n';

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
