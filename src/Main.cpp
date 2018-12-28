#include "Classes.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>

using namespace std;

class MyInteger
{
public:
    MyInteger( int val = 0 ) : m_Val( val ) {}

    MyInteger& operator*( int i )
    {
        m_Val *= i;
        return *this;
    }

private:
    int m_Val;
};

template< typename X, typename Y >
auto multiply( X x, Y y ) -> decltype( x * y )
{
    return x * y;
}

void lambaExample()
{
    vector< int > myIntegers { 1, 2, 3 };
    /*myIntegers.push_back( 1 );
    myIntegers.push_back( 2 );
    myIntegers.push_back( 3 );*/

    // can extend container using initializer_list
    myIntegers.insert( end( myIntegers ), { 4, 5, 6 } );

    // lambda with parameter
    //for_each( myIntegers.begin(), myIntegers.end(), []( int val ) { cout << "new val is " << ++val << endl; } );

    // or another way of iterating
    for_each( begin( myIntegers ), end( myIntegers ), []( int val ) { cout << "new val is " << ++val << endl; } );

    // lambda without parameter
    for ( int i = 0; i < 3; i++ ) { [] { static int x = 1; x += x;  cout << "calculated: " << x << endl; } (); }

    cout << endl;
}

void storingLambda()
{
    // lambda can be stored with auto
    auto lambda1 = [] { return 1; };
    // or with a std::function pointer
    function< int( int ) > lambdaN = []( int n ) { return n; };

    cout << "lambda 1: " << lambda1() << endl;
    cout << "lambda N=2: " << lambdaN( 2 ) << endl;
    cout << "lambda N=10: " << lambdaN( 10 ) << endl << endl;
}

class SomeClass
{
    int m_member;
public:
    SomeClass() : m_member( 0 ) {}
    function< int() > getMemberGetter()
    {
        return [ = ] { return m_member; };
    }
};

function< int( int ) > CloserInnerScope()
{
    int a = 100;
    function< int( int ) > lambda = [ &a ]( int par ) { return ( par + a ); };
    cout << "capturing 'a' in function scope: " << lambda( 2 ) << endl;
    a = 200;
    cout << "capturing 'a' in function scope: " << lambda( 2 ) << endl;

    return lambda;
}

void ClosuresAndCapturing()
{
    // create outer scope
    function< int( int ) > outerLambda;
    {
        // create inner scope
        int a = 1;
        outerLambda = [ &a ]( int par ) { return ( par + a ); };
        cout << "capturing 'a' in inner scope: " << outerLambda( 2 ) << endl;
    }
    int b = 2;
    cout << "capturing 'a' in outer scope: " << outerLambda( 10 ) << endl;

    function <int() > getter;
    {
        SomeClass sth;
        getter = sth.getMemberGetter();
        cout << "Getter: " << getter() << endl;
    }
    cout << "Getter out of scope: " << getter() << endl;

    function< int( int ) > functionLambda = CloserInnerScope();
    // this prints garbage, as a is destroyed resulting in undefined behaviour
    cout << "capturing function 'a' in outer scope: " << functionLambda( 1000 ) << endl;

    // default capture modes
    int x, y, z;
    x = 1;
    y = 2;
    z = 3;

    //auto lambdaVal = [ = ]() mutable { return x + y + z; };
    // mutable allows to modify copied capture
    auto lambdaVal = [ = ]() mutable { x += 1; return x + y + z; };
    auto lambdaRef = [ & ]() { x += 10; return x + y + z; };

    cout << "x=" << x << ", y=" << y << ", z=" << z << ", lambdaVal=" << lambdaVal() << endl;
    cout << "x=" << x << ", y=" << y << ", z=" << z << ", lambdaRef=" << lambdaRef() << endl;
    // values don't change with the second call!
    cout << "x=" << x << ", y=" << y << ", z=" << z << ", lambdaVal=" << lambdaVal() << endl;
    cout << "x=" << x << ", y=" << y << ", z=" << z << ", lambdaRef=" << lambdaRef() << endl;
    // neither with third!
    cout << "x=" << x << ", y=" << y << ", z=" << z << ", lambdaVal=" << lambdaVal() << endl;

    cout << endl;
}

int main()
{
    MyInteger myInt( 1 );
    auto val1 = multiply( 1, 1 );
    auto val2 = multiply( 1, 1.0 );
    auto val3 = multiply( myInt, 1 );

    cout << "val1: " << typeid( val1 ).name() << endl;
    cout << "val2: " << typeid( val2 ).name() << endl;
    cout << "val3: " << typeid( val3 ).name() << endl;
    cout << endl;

    lambaExample();
    storingLambda();
    ClosuresAndCapturing();

    TemplatedClass< int > c_int;
    // using instead of typedef
    using TemplatedString = TemplatedClass< string >;
    TemplatedString c_string;
    c_int.TemplatedMethod();
    c_string.TemplatedMethod();

    VariadicClass vc_1ele;
    VariadicClass vc_6ele;
    int i;
    bool b;
    vc_1ele.VariadicMethod( i );
    vc_6ele.VariadicMethod( i, i, i, b, i, b );

    return 0;
}
