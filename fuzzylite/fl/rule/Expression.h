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

#ifndef FL_EXPRESSION_H
#define FL_EXPRESSION_H

#include "fl/fuzzylite.h"

#include <string>
#include <vector>



namespace fl {
    class Variable;
    class Hedge;
    class Term;

    /**
     * Base class for an expression tree
     * @author Juan Rada-Vilela, Ph.D.
     * @see Antecedent
     * @see Consequent
     * @see Rule
     * @since 4.0
     */
    class FL_API Expression {
    public:

        Expression();
        virtual ~Expression();

        virtual std::string toString() const = 0;

    private:
        FL_DISABLE_COPY(Expression)
    };

    /**
     * A terminal node in the expression tree. The node represents a proposition 
     * in the form `variable is [hedge]* term`
     * @author Juan Rada-Vilela, Ph.D.
     * @see Antecedent
     * @see Consequent
     * @see Rule
     * @since 4.0
     */
    class FL_API Proposition : public Expression {
    public:
        /**Variable in `variable is [hedge]* term`*/
        Variable* variable;
        /**Hedge%s in `variable is [hedge]* term`*/
        std::vector<Hedge*> hedges;
        /**Term in `variable is [hedge]* term`*/
        Term* term;

        Proposition();
        virtual ~Proposition() FL_IOVERRIDE;

        /**
         * Returns a string representation of the proposition
         * @return a string representation of the proposition
         */
        virtual std::string toString() const FL_IOVERRIDE;

    private:
        FL_DISABLE_COPY(Proposition)
    };

    /**
     * A non-terminal node in the expression tree. The node represents a 
     * a binary operator (i.e., `and` or `or`) on two Expression%s
     * @author Juan Rada-Vilela, Ph.D.
     * @see Antecedent
     * @see Consequent
     * @see Rule
     * @since 4.0
     */
    class FL_API Operator : public Expression {
    public:
        /**Name of the operator*/
        std::string name;
        /**Expression in the left binary tree*/
        Expression* left;
        /**Expression in the right binary tree*/
        Expression* right;

        Operator();
        virtual ~Operator() FL_IOVERRIDE;

        /**
         * Provides the name of the operator
         * @return the name of the operator
         */
        virtual std::string toString() const FL_IOVERRIDE;

    private:
        FL_DISABLE_COPY(Operator)

    };

}
#endif /* FL_FUZZYEXPRESSION_H */
