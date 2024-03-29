#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print() const override
    {
        std::cout<<id;
    }
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
        double x = bindings.at(id);
        return x;
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        if(id == variable){
            std::cout << 1;
        }else{
            std::cout << 0;
        }
        return 0;
    }

};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print() const override
    {
        std::cout<<value;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { return value;
    }

    virtual const Expression *differentiate(
        const std::string &variable
    ) const
    {
        std::cout << 0;
        return 0;
    }
};


#endif
