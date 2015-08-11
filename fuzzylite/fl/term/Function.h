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

#ifndef FL_FUNCTION_H
#define FL_FUNCTION_H

#include "fl/term/Term.h"

#include <map>
#include <string>

namespace fl {

    class Engine;

    /**
     * %Term for a generic formula membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @see FunctionFactory
     * @since 4.0
     */
    class FL_API Function : public Term {
    public:
        typedef scalar(*Unary)(scalar);
        typedef scalar(*Binary)(scalar, scalar);

        /**
         * A structure that defines a single element in a formula. 
         * An Element can represent a function or an operator. 
         * If the Element represents a function, the function can be 
         * Unary or Binary, that is, the function take one or two parameters 
         * (respectively). 
         * If the Element represents an operator, the parameters to be defined 
         * are its `arity`, its `precedence`, and its `associativity`.
         */
        struct FL_API Element {

            /**
             * Determines the type of the element
             */
            enum Type {
                Operator, Function
            };
            /**Name of the element**/
            std::string name;
            /**Description of the element**/
            std::string description;
            /**Type of the element**/
            Type type;
            /**Pointer to unary method**/
            Unary unary;
            /**Pointer to binary method**/
            Binary binary;
            /**Number of operands required**/
            int arity;
            /**Precedence of the element: clarifies which procedures should be 
             * performed first in a given mathematical expression
             * (https://en.wikipedia.org/wiki/Order_of_operations)**/
            int precedence;
            /**Associativity of the element: determines how operators of the 
             * same precedence are grouped in the absence of parentheses
             * (https://en.wikipedia.org/wiki/Operator_associativity)**/
            int associativity;
            Element(const std::string& name, const std::string& description, Type type);
            Element(const std::string& name, const std::string& description,
                    Type type, Unary unary, int precedence = 0, int associativity = -1);
            Element(const std::string& name, const std::string& description,
                    Type type, Binary binary, int precedence = 0, int associativity = -1);
            virtual ~Element();
            FL_DEFAULT_COPY_AND_MOVE(Element)

            /**
             * Indicates whether the element is a Type::Operator
             * @return whether the element is a Type::Operator
             */
            virtual bool isOperator() const;
            /**
             * Indicates whether the element is a Type::Function
             * @return whether the element is a Type::Function
             */
            virtual bool isFunction() const;
            /**
             * Clones the element
             * @return a clone of the element
             */
            virtual Element* clone() const;

            /**
             * Provides a description of the element and its members
             * @return a description of the element and its members
             */
            virtual std::string toString() const;

        };

        /**
         * A binary tree structure that can store a Function::Element, 
         * a reference to an InputVariable or OutputVariable by name, 
         * or a constant value.
         */
        struct FL_API Node {
            /**The node takes an operation or a function**/
            FL_unique_ptr<Element> element;
            /**The node can have an expression tree on the left**/
            FL_unique_ptr<Node> left;
            /**The node can have an expression tree on the right**/
            FL_unique_ptr<Node> right;
            /**The node can refer to a variable by name**/
            std::string variable;
            /**The node can take an arbitrary floating-point value**/
            scalar value;

            explicit Node(Element* element, Node* left = fl::null, Node* right = fl::null);
            explicit Node(const std::string& variable);
            explicit Node(scalar value);
            Node(const Node& source);
            Node& operator=(const Node& rhs);
            virtual ~Node();
            FL_DEFAULT_MOVE(Node)

            /**
             * Evaluates the node and substitutes the variables therein for the 
             * values passed in the map. The expression tree is evaluated recursively.
             * @param variables is a map of substitutions of variable names for fl::scalar%s
             * @return a fl::scalar indicating the result of the evaluation of the node
             */
            virtual scalar evaluate(const std::map<std::string, scalar>*
                    variables = fl::null) const;

            /**
             * Clones the node.
             * @return a clone of the node
             */
            virtual Node* clone() const;

            /**
             * Provides a string with the name of the element, the name of the 
             * variable, or the constant value, accordingly.
             * @return a string with the name of the element, the name of the 
             * variable, or the constant value, accordingly.
             */
            virtual std::string toString() const;
            /**
             * Provides a prefix representation of the expression tree under the
             * given node
             * @param node is the node to start the prefix representation from. 
             * If the node is `fl::null`, then the starting point is `this` node
             * @return a prefix representation of the expression tree under the
             * given node
             */
            virtual std::string toPrefix(const Node* node = fl::null) const;
            /**
             * Provides an infix representation of the expression tree under the
             * given node
             * @param node is the node to start the infix representation from. 
             * If the node is `fl::null`, then the starting point is `this` node
             * @return an infix representation of the expression tree under the
             * given node
             */
            virtual std::string toInfix(const Node* node = fl::null) const;
            /**
             * Provides a postfix representation of the expression tree under the
             * given node
             * @param node is the node to start the postfix representation from. 
             * If the node is `fl::null`, then the starting point is `this` node
             * @return a postfix representation of the expression tree under the
             * given node
             */
            virtual std::string toPostfix(const Node* node = fl::null) const;
        private:
            void copyFrom(const Node& source);
        };




    protected:
        FL_unique_ptr<Node> _root;
        std::string _formula;
        const Engine* _engine;
    public:
        /**A map of variables and substitution values**/
        mutable std::map<std::string, scalar> variables;
        explicit Function(const std::string& name = "",
                const std::string& formula = "", const Engine* engine = fl::null);
        Function(const Function& other);
        Function& operator=(const Function& other);
        virtual ~Function() FL_IOVERRIDE;
        FL_DEFAULT_MOVE(Function)

        /**
         * Creates a Function term with the given parameters
         * @param name is the name of the term
         * @param formula is the formula defining the membership function
         * @param engine is the engine to which the Function can have access
         * @return a Function term configured with the given parameters
         * @throws fl::Exception if the formula has a syntax error
         */
        static Function* create(const std::string& name,
                const std::string& formula,
                const Engine* engine = fl::null);

        /**
         * Computes the membership function value of @f$x@f$ at the root node.
         * If the engine has been set, the current values of the input variables 
         * and output variables are added to the map of {@link Function::variables}.
         * In addition, the variable @f$x@f$ will also be added to the map.
         * @param x
         * @return the membership function value of @f$x@f$ at the root node
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Computes the function value of this term using the given map of 
         * variable substitutions.
         * @param variables is a map of substitution variables
         * @return the function value of this term using the given map of 
         * variable substitutions.
         */
        virtual scalar evaluate(const std::map<std::string, scalar>* variables) const;

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `formula`
         * @return `formula`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `formula`
         * @param parameters as `formula`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
         * Sets the formula of the function
         * @param formula is the formula of the function
         */
        virtual void setFormula(const std::string& formula);
        /**
         * Gets the formula of the function
         * @return the formula of the function
         */
        virtual std::string getFormula() const;

        /**
         * Sets the engine to which the formula can refer
         * @param engine is the engine to which the formula can refer
         */
        virtual void setEngine(const Engine* engine);
        /**
         * Gets the engine to which the formula can refer
         * @return the engine to which the formula can refer
         */
        virtual const Engine* getEngine() const;

        /**
         * Gets the root node of the expression tree defining the Function. The 
         * root is `fl::null` if the formula has not been loaded.
         * @return the root node of the expression tree defining the Function, 
         * or `fl::null` if the formula has not been loaded
         */
        virtual Node* root() const;

        /**
         * Indicates whether the formula is loaded
         * @return whether the formula is loaded
         */
        virtual bool isLoaded() const;
        /**
         * Unloads the formula and resets the map of substitution variables.
         */
        virtual void unload();
        /**
         * Loads the current formula expressed in infix notation
         */
        virtual void load();
        /**
         * Loads the given formula expressed in infix notation
         * @param formula is the right-hand side of a mathematical equation
         * @throws fl::Exception if the formula has syntax errors
         */
        virtual void load(const std::string& formula);
        /**
         * Loads the given formula expressed in infix notation, and sets the 
         * engine holding the variables to which the formula refers.
         * @param formula is the right-hand side of a mathematical equation 
         * expressed in infix notation
         * @param engine is the engine to which the formula can refer
         * @throws fl::Exception if the formula has syntax errors
         */
        virtual void load(const std::string& formula, const Engine* engine);
        /**
         * Creates a node representing a binary expression tree from the given formula
         * @param formula is the right-hand side of a mathematical equation
         * expressed in infix notation
         * @return a node representing a binary expression tree from the given formula
         * @throws fl::Exception if the formula has syntax errors
         */
        virtual Node* parse(const std::string& formula);

        /**
         * Translates the given formula to postfix notation
         * @param formula is the right-hand side of a mathematical equation
         * expressed in infix notation
         * @return the formula represented in postfix notation
         * @throws fl::Exception if the formula has syntax errors
         */
        virtual std::string toPostfix(const std::string& formula) const;

        /**
         * Adds spaces to the formula to separate parentheses, commas and function
         * operators such that these are treated as tokens when parsing the function.
         * @param formula is the right-hand side of a mathematical equation
         * expressed in infix notation
         * @return the formula with spaces before and after parentheses, commas 
         * and function operators
         */
        virtual std::string space(const std::string& formula) const;

        virtual Function* clone() const FL_IOVERRIDE;

        static Term* constructor();

        static void main();

    };

}

#endif  /* FL_FUNCTION_H */
