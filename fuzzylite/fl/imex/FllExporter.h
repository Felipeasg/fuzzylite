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

#ifndef FL_FLLEXPORTER_H
#define FL_FLLEXPORTER_H

#include "fl/imex/Exporter.h"

#include <vector>

namespace fl {
    class Variable;
    class InputVariable;
    class OutputVariable;
    class RuleBlock;
    class Rule;
    class Norm;
    class Activation;
    class Defuzzifier;
    class Term;

    /**
     * Exports an Engine to the FuzzyLite Language (FLL)
     * @author Juan Rada-Vilela, Ph.D.
     * @see FclExporter
     * @see Importer
     * @since 4.0
     */
    class FL_API FllExporter : public Exporter {
    protected:
        std::string _indent;
        std::string _separator;
    public:
        explicit FllExporter(const std::string& indent = "  ", const std::string& separator = "\n");
        virtual ~FllExporter() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(FllExporter)

        virtual std::string name() const FL_IOVERRIDE;

        /**
         * Sets the indent string of the language
         * @param indent is the indent string of the language
         */
        virtual void setIndent(const std::string& indent);
        /**
         * Gets the indent string of the language
         * @return the indent string of the language
         */
        virtual std::string getIndent() const;

        /**
         * Gets the separator of the language
         * @param separator of the language
         */
        virtual void setSeparator(const std::string& separator);
        /**
         * Gets the separator of the language
         * @return the separator of the language
         */
        virtual std::string getSeparator() const;

        virtual std::string toString(const Engine* engine) const FL_IOVERRIDE;

        /**
         * Returns a string representation of the vector of variables
         * @param variables is the vector of variables to export
         * @return a string representation of the vector of variables
         */
        virtual std::string toString(const std::vector<Variable*>& variables) const;
        /**
         * Returns a string representation of the vector of input variables
         * @param inputVariables is the vector of input variables to export
         * @return a string representation of the vector of input variables
         */
        virtual std::string toString(const std::vector<InputVariable*>& inputVariables) const;
        /**
         * Returns a string representation of the vector of output variables
         * @param outputVariables is a vector of output variables to export
         * @return a string representation of the vector of output variables
         */
        virtual std::string toString(const std::vector<OutputVariable*>& outputVariables) const;
        /**
         * Returns a string representation of the vector of rule blocks
         * @param ruleBlocks is the vector of rule blocks to export
         * @return a string representation of the vector of rule blocks
         */
        virtual std::string toString(const std::vector<RuleBlock*>& ruleBlocks) const;

        /**
         * Returns a string representation of the variable
         * @param variable is the variable to export
         * @return a string representation of the variable
         */
        virtual std::string toString(const Variable* variable) const;
        /**
         * Returns a string representation of the input variable
         * @param inputVariable is the input variable to export
         * @return a string representation of the input variable
         */
        virtual std::string toString(const InputVariable* inputVariable) const;
        /**
         * Returns a string representation of the output variable
         * @param outputVariable is the output variable to export
         * @return a string representation of the output variable
         */
        virtual std::string toString(const OutputVariable* outputVariable) const;

        /**
         * Returns a string representation of the rule block
         * @param ruleBlock is the rule block to export
         * @return a string representation of the rule block
         */
        virtual std::string toString(const RuleBlock* ruleBlock) const;
        /**
         * Returns a string representation of the rule
         * @param rule is the rule to export
         * @return a string representation of the rule
         */
        virtual std::string toString(const Rule* rule) const;

        /**
         * Returns a string representation of the norm
         * @param norm is the norm to export
         * @return a string representation of the norm
         */
        virtual std::string toString(const Norm* norm) const;
        /**
         * Returns a string representation of the activation method
         * @param activation is the activation method to export
         * @return a string representation of the activation method
         */
        virtual std::string toString(const Activation* activation) const;
        /**
         * Returns a string representation of the defuzzifier
         * @param defuzzifier is the defuzzifier to export
         * @return a string representation of the defuzzifier
         */
        virtual std::string toString(const Defuzzifier* defuzzifier) const;
        /**
         * Returns a string representation of the term
         * @param term is the term to export
         * @return a string representation of the term
         */
        virtual std::string toString(const Term* term) const;

        virtual FllExporter* clone() const FL_IOVERRIDE;
    };

}

#endif  /* FL_FLLEXPORTER_H */
