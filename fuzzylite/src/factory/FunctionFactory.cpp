/*
 Copyright © 2010-2015 by FuzzyLite Limited.
 All rights reserved.

 This file is part of fuzzylite®.

 fuzzylite® is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with 
 fuzzylite®. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite® is a registered trademark of FuzzyLite Limited.

 */

#include "fl/factory/FunctionFactory.h"

#include "fl/rule/Rule.h"

namespace fl {

    FunctionFactory::FunctionFactory() : CloningFactory<Function::Element*>("Function::Element") {
        registerOperators();
        registerFunctions();
    }

    FunctionFactory::~FunctionFactory() {

    }

    void FunctionFactory::registerOperators() {
        //OPERATORS:
        int p = 100;
        //First order: not, negate:
        registerObject("!", new Function::Element("!", "Logical NOT",
                Function::Element::Operator, &(fl::Op::logicalNot), p, 1)); //logical not
        registerObject("~", new Function::Element("~", "Negation",
                Function::Element::Operator, &(fl::Op::negate), p, 1)); // ~ negates a number

        p -= 10;
        //Second order: power
        registerObject("^", new Function::Element("^", "Power",
                Function::Element::Operator, &(std::pow), p, 1));

        p -= 10;
        //Third order: multiplication, division, modulo
        registerObject("*", new Function::Element("*", "Multiplication",
                Function::Element::Operator, &(fl::Op::multiply), p));
        registerObject("/", new Function::Element("/", "Division",
                Function::Element::Operator, &(fl::Op::divide), p));
        registerObject("%", new Function::Element("%", "Modulo",
                Function::Element::Operator, &(fl::Op::modulo), p));

        p -= 10;
        //Fourth order: addition, subtraction
        registerObject("+", new Function::Element("+", "Addition",
                Function::Element::Operator, &(fl::Op::add), p));
        registerObject("-", new Function::Element("-", "Subtraction",
                Function::Element::Operator, &(fl::Op::subtract), p));

        //Fifth order: logical and, logical or
        p -= 10; //Logical AND
        registerObject(fl::Rule::andKeyword(), new Function::Element(fl::Rule::andKeyword(), "Logical AND",
                Function::Element::Operator, &(fl::Op::logicalAnd), p));
        p -= 10; //Logical OR
        registerObject(fl::Rule::orKeyword(), new Function::Element(fl::Rule::orKeyword(), "Logical OR",
                Function::Element::Operator, &(fl::Op::logicalOr), p));
    }

    void FunctionFactory::registerFunctions() {
        //FUNCTIONS
        registerObject("gt", new Function::Element("gt", "Greater than (>)",
                Function::Element::Function, &(fl::Op::gt)));
        registerObject("ge", new Function::Element("ge", "Greater than or equal to (>=)",
                Function::Element::Function, &(fl::Op::ge)));
        registerObject("eq", new Function::Element("eq", "Equal to (==)",
                Function::Element::Function, &(fl::Op::eq)));
        registerObject("neq", new Function::Element("neq", "Not equal to (!=)",
                Function::Element::Function, &(fl::Op::neq)));
        registerObject("le", new Function::Element("le", "Less than or equal to (<=)",
                Function::Element::Function, &(fl::Op::le)));
        registerObject("lt", new Function::Element("lt", "Less than (<)",
                Function::Element::Function, &(fl::Op::lt)));

        registerObject("acos", new Function::Element("acos", "Inverse cosine",
                Function::Element::Function, &(std::acos)));
        registerObject("asin", new Function::Element("asin", "Inverse sine",
                Function::Element::Function, &(std::asin)));
        registerObject("atan", new Function::Element("atan", "Inverse tangent",
                Function::Element::Function, &(std::atan)));

        registerObject("ceil", new Function::Element("ceil", "Ceiling",
                Function::Element::Function, &(std::ceil)));
        registerObject("cos", new Function::Element("cos", "Cosine",
                Function::Element::Function, &(std::cos)));
        registerObject("cosh", new Function::Element("cosh", "Hyperbolic cosine",
                Function::Element::Function, &(std::cosh)));
        registerObject("exp", new Function::Element("exp", "Exponential",
                Function::Element::Function, &(std::exp)));
        registerObject("fabs", new Function::Element("fabs", "Absolute",
                Function::Element::Function, &(std::fabs)));
        registerObject("floor", new Function::Element("floor", "Floor",
                Function::Element::Function, &(std::floor)));
        registerObject("log", new Function::Element("log", "Natural logarithm",
                Function::Element::Function, &(std::log)));
        registerObject("log10", new Function::Element("log10", "Common logarithm",
                Function::Element::Function, &(std::log10)));
        registerObject("round", new Function::Element("round", "Round",
                Function::Element::Function, &(fl::Op::round)));
        registerObject("sin", new Function::Element("sin", "Sine",
                Function::Element::Function, &(std::sin)));
        registerObject("sinh", new Function::Element("sinh", "Hyperbolic sine",
                Function::Element::Function, &(std::sinh)));
        registerObject("sqrt", new Function::Element("sqrt", "Square root",
                Function::Element::Function, &(std::sqrt)));
        registerObject("tan", new Function::Element("tan", "Tangent",
                Function::Element::Function, &(std::tan)));
        registerObject("tanh", new Function::Element("tanh", "Hyperbolic tangent",
                Function::Element::Function, &(std::tanh)));

#if defined(FL_UNIX) && !defined(FL_USE_FLOAT)
        //found in Unix when using double precision. not found in Windows.
        registerObject("log1p", new Function::Element("log1p", "Natural logarithm plus one",
                Function::Element::Function, &(log1p)));
        registerObject("acosh", new Function::Element("acosh", "Inverse hyperbolic cosine",
                Function::Element::Function, &(acosh)));
        registerObject("asinh", new Function::Element("asinh", "Inverse hyperbolic sine",
                Function::Element::Function, &(asinh)));
        registerObject("atanh", new Function::Element("atanh", "Inverse hyperbolic tangent",
                Function::Element::Function, &(atanh)));
#endif

        registerObject("pow", new Function::Element("pow", "Power",
                Function::Element::Function, &(std::pow)));
        registerObject("atan2", new Function::Element("atan2", "Inverse tangent (y,x)",
                Function::Element::Function, &(std::atan2)));
        registerObject("fmod", new Function::Element("fmod", "Floating-point remainder",
                Function::Element::Function, &(std::fmod)));
    }

    std::vector<std::string> FunctionFactory::availableOperators() const {
        std::vector<std::string> result;
        std::map<std::string, Function::Element*>::const_iterator it = this->_objects.begin();
        while (it != this->_objects.end()) {
            if (it->second and it->second->type == Function::Element::Operator)
                result.push_back(it->first);
            ++it;
        }
        return result;
    }

    std::vector<std::string> FunctionFactory::availableFunctions() const {
        std::vector<std::string> result;
        std::map<std::string, Function::Element*>::const_iterator it = this->_objects.begin();
        while (it != this->_objects.end()) {
            if (it->second and it->second->type == Function::Element::Function)
                result.push_back(it->first);
            ++it;
        }
        return result;
    }

}
