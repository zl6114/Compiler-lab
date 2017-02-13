#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    const Expression *arg;
protected:
    Function(const Expression *_arg)
        : arg(_arg)
    {}
public:

    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    const Expression *getArg() const
    { return arg; }

    virtual void print() const override
    {
        std::cout<<getFunction()<<"( ";
        arg->print();
        std::cout<<" )";
    }
};

class LogFunction
    : public Function
{
public:
    LogFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
        return log(getArg()->evaluate(bindings));
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout << "( ";
            getArg()->differentiate(variable);
        std::cout<<" * ";
            std::cout<<"( 1 / ";
            getArg()->print();
            std::cout<<" )";
        std::cout<<" )";
        return 0;
    }
};

class ExpFunction
    : public Function
{
public:
    ExpFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
        return exp(getArg()->evaluate(bindings));
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout << "( ";
            getArg()->differentiate(variable);
        std::cout<<" * ";
            std::cout<<getFunction()<<"( ";
            getArg()->print();
            std::cout<<" )";
        std::cout<<" )";
        return 0;
    }


};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(const Expression *_arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
        return sqrt(getArg()->evaluate(bindings));
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout << "( ";
            std::cout << "( ";
                std::cout << "1 / 2 ";
                std::cout << " * ";
                getArg()->differentiate(variable);
            std::cout<<" )";
            std::cout<< " * ";
            std::cout << "( ";
                std::cout << "1 / ";
                std::cout<<getFunction()<<"( ";
                getArg()->print();
                std::cout<<" )";
            std::cout<<" )";
        std::cout << " )";
        return 0;
    }
};


#endif
