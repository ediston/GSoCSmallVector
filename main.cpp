#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "smallVector.h"
#include <limits.h>
#define print(x) cout << "\t" << x << "\n";
using namespace std;

void testAssign(){
    cout << "Testing ASSIGN function: " << endl;

    smallVector<int> first;
    smallVector<int> second;
    ;
    first.assign (7,100);             // 7 ints with a value of 100
    smallVector<int>::iterator it;
    it=first.begin()+1;
    second.assign (it, first.end()-1); // the 5 central values of first
    int myints[] = {1776,7,4};
    smallVector<int> third(myints,myints+3);   // assigning from array.
    assert (int (first.size()) ==7);
    print("Passed 1");
    assert (int (second.size()) ==5);
    print("Passed 2");
    assert (int (third.size()) ==3);
    print("Passed 3");
    print("");
}

void testErase(){
    cout << "Testing ERASE function: " << endl;
    smallVector<int> myvector;
    for (int i=1; i<=10; i++) myvector.push_back(i);
    myvector.erase (myvector.begin()+5);
    myvector.erase (myvector.begin(),myvector.begin()+3);
    assert (myvector[0] ==4);
    print("Passed 1");
    assert (myvector[2] ==7);
    print("Passed 2");
    assert (myvector[5] ==10);
    print("Passed 3");

    myvector.erase (myvector.begin()+1, myvector.begin()+3);
    assert (myvector[2] ==9);
    print("Passed 4");
}

void testString(){
    cout << "Testing with STRINGS : " << endl;
    smallVector<string> strVector;
    strVector.push_back("How are you??");
    strVector.push_back("I am good!");
    strVector.push_back("How's the dog?");
    strVector.push_back("Dog is good!");
    strVector.erase(strVector.begin()+1);
    strVector.erase(strVector.begin()+1);
    assert (strVector[1] == "Dog is good!");
    print("Passed 1");

    string args[] = {"01", "02", "03", "04"};
    smallVector<string> strV(args, args + 4);
    strV.erase(strV.begin()+2); // remove third element
    assert (strV[1] == "02");
    print("Passed 2");
    assert (strV[2] == "04");
    print("Passed 3");
    cout << endl;
}

void testInsertAndIterator(){
    cout << "Testing INSERT/Iterator function : " << endl;
    smallVector<int> myvector (3,100);
    smallVector<int>::iterator it;
    it = myvector.begin();
    myvector.insert ( it , 200 );
    it = myvector.begin();
    myvector.insert (it,2,300);
    it = myvector.begin();

    smallVector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());
    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);
    //501 502 503 300 300 400 400 200 100 100 100
    it=myvector.begin();
    assert (*it == 501);
    print("Passed 1");
    it+=2;
    assert (*it == 503);
    print("Passed 2");
    it += 3;
    assert (*it == 400);
    print("Passed 3");
    print(" ");
}

void testPushBack(){
    cout << "Testing PushBack function: " << endl;
    long SIZE = 1000;
    smallVector<int> myvector;
    try{
        for (long long i=1; i<=SIZE; i++) {
            myvector.push_back(10);
        }
        print("Passed 1");
    }catch(exception& e){
        cout << e.what() << '\n';
        assert(false);
    }
    assert(myvector.size() == SIZE);
    print("Passed 2");
    assert(myvector.max_size() == UINT_MAX);
    print("Passed 3");
    assert(myvector.capacity() <= 2*SIZE+1);
    print("Passed 4");
    print(" ");
}

void testAll(){
    testPushBack();
    testInsertAndIterator();
    testString();
    testAssign();
    testErase();
}


int main ()
{
    testAll();
    return 0;
}
