#ifndef __CLASSES_HPP__
#define __CLASSES_HPP__

#include <iostream>

using namespace std;

// C++11 type class declaration
class CPP11_Class
{
public:
    CPP11_Class() {}
    CPP11_Class( const string& _name ) : m_name( _name ) {}

    virtual void virt( int _i ) {}
    virtual void virt_final( int _i ) final {}

protected:
    void initialize() {}
    void init() {}

private:
    int m_par1 = 0;
    int m_par2 = 0;
    string m_name = "Something";
};

class CPP11_derived : public CPP11_Class
{
    // Inheriting constructors from base class, but can be overriden
    using CPP11_Class::CPP11_Class;

public:

    virtual void virt( int _i ) override {}
};

class ConstructorDelegation
{
public:
    ConstructorDelegation() : ConstructorDelegation( 0, 0 ) {}
    ConstructorDelegation( int _i ) : ConstructorDelegation( _i, 0 )
    {
        init_more();
    }

private:
    ConstructorDelegation( int _i, int _j ) : m_i( _i ), m_j( _j )
    {
        init();
    }

    void init() {}
    void init_more() {}

    int m_i;
    int m_j;
};

class ImplicitMethodImplementation
{
public:
    ImplicitMethodImplementation() = default;
    ImplicitMethodImplementation( int i ) {}
    virtual ~ImplicitMethodImplementation() = default;

    ImplicitMethodImplementation( const ImplicitMethodImplementation& ) = delete;
    ImplicitMethodImplementation& operator=( const ImplicitMethodImplementation& ) = delete;

    // prevent heap allocation
    void* operator new( size_t ) = delete;

    // delete can also prevent instantiation of a template
};

// Templates can also be extern-ed like:
// extern template vector< int >

template< typename A >
class TemplatedClass
{
public:
    void TemplatedMethod();
};

template< typename A >
void TemplatedClass< A >::TemplatedMethod()
{
    cout << "template type is: " << typeid( A ).name() << endl;
}

class VariadicClass
{
public:
    template< typename A, typename... B >
    bool VariadicMethod( A& _a, B&... _b );
 
    template< typename A >
    bool VariadicMethod( A& );
};

template< typename A, typename... B >
bool VariadicClass::VariadicMethod( A& _a, B&... _b )
{
    // sizeof...( B )
    cout << "#" << typeid( A ).name() << " ";
    VariadicMethod( _b... );
    return true;
}

template< typename A >
bool VariadicClass::VariadicMethod( A& _a )
{
    cout << "#" << typeid( A ).name() << endl;
    return true;
}

#endif // !__CLASSES_HPP__
