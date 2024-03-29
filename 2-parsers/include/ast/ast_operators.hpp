#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>

class Operator
    : public Expression
{
private:
    const Expression *left;
    const Expression *right;
protected:
    Operator(const Expression *_left, const Expression *_right)
        : left(_left)
        , right(_right)
    {}
public:

    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    const Expression *getLeft() const
    { return left; }

    const Expression *getRight() const
    { return right; }

    virtual void print() const override
    {
        std::cout<<"( ";
        left->print();
        std::cout<<" ";
        std::cout<<getOpcode();
        std::cout<<" ";
        right->print();
        std::cout<<" )";
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
    virtual double evaluate(
    const std::map<std::string,double> &bindings
    ) const
    {return (getLeft()->evaluate(bindings) + getRight()->evaluate(bindings));}

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout<<"( ";
        getLeft()->differentiate(variable);
        std::cout<<" ";
        std::cout<<getOpcode();
        std::cout<<" ";
        getRight()->differentiate(variable);
        std::cout<<" )";
        return 0;
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
    virtual double evaluate(
    const std::map<std::string,double> &bindings
    ) const
    {return (getLeft()->evaluate(bindings) - getRight()->evaluate(bindings));}

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout<<"( ";
        getLeft()->differentiate(variable);
        std::cout<<" ";
        std::cout<<getOpcode();
        std::cout<<" ";
        getRight()->differentiate(variable);
        std::cout<<" )";
        return 0;
    }
};

class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
    virtual double evaluate(
    const std::map<std::string,double> &bindings
    ) const
    {return (getLeft() -> evaluate(bindings) * getRight() -> evaluate(bindings));}

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout<<"( ";
            std::cout<<"( ";
            getLeft()->differentiate(variable);
            std::cout<<" ";
            std::cout<<getOpcode();
            std::cout<<" ";
            getRight()->print();
            std::cout<<" )";
        std::cout<<" + ";
            std::cout<<"( ";
            getLeft()->print();
            std::cout<<" ";
            std::cout<<getOpcode();
            std::cout<<" ";
            getRight()->differentiate(variable);
            std::cout<<" )";
        std::cout<<" )";
        return 0;
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(const Expression *_left, const Expression *_right)
        : Operator(_left, _right)
    {}
    virtual double evaluate(
    const std::map<std::string,double> &bindings
    )const
    {return (getLeft() -> evaluate(bindings) / getRight() -> evaluate(bindings));}

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout<<"( ";
            std::cout<<"( ";
                std::cout<<"( ";
                getLeft()->differentiate(variable);
                std::cout<<" ";
                std::cout<<getOpcode();
                std::cout<<" ";
                getRight()->print();
                std::cout<<" )";
            std::cout<<" - ";
                std::cout<<"( ";
                getLeft()->print();
                std::cout<<" ";
                std::cout<<getOpcode();
                std::cout<<" ";
                getRight()->differentiate(variable);
                std::cout<<" )";
            std::cout<<" )";
        std::cout << " / ";
        getRight()->print();
        std::cout << " * ";
        getRight()->print();
        std::cout<<" )";
        return 0;
    }
};

#endif
