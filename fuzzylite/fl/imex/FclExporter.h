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

#ifndef FL_FCLEXPORTER_H
#define FL_FCLEXPORTER_H

#include "fl/imex/Exporter.h"

namespace fl {
    class InputVariable;
    class OutputVariable;
    class RuleBlock;
    class Norm;
    class TNorm;
    class SNorm;
    class Defuzzifier;
    class Term;

    /**
     * Exports an Engine to the Fuzzy Control Language specification
     * @author Juan Rada-Vilela, Ph.D.
     * @see FclImporter
     * @see Exporter
     * @since 4.0
     */
    class FL_API FclExporter : public Exporter {
    protected:
        std::string _indent;

    public:
        explicit FclExporter(const std::string& indent = "  ");
        virtual ~FclExporter() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(FclExporter)

        virtual void setIndent(const std::string& indent);
        virtual std::string getIndent() const;

        virtual std::string name() const FL_IOVERRIDE;
        virtual std::string toString(const Engine* engine) const FL_IOVERRIDE;

        /**
         * Returns a string representation of the input variable according to the Fuzzy Control Language specification
         * @param variable is the input variable
         * @return a string representation of the input variable  according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const InputVariable* variable) const;
        /**
         * Returns a string representation of the output variable according to the Fuzzy Control Language specification
         * @param variable is the output variable
         * @return a string representation of the output variable according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const OutputVariable* variable) const;
        /**
         * Returns a string representation of the rule block according to the Fuzzy Control Language specification
         * @param ruleBlock is the rule block
         * @return a string representation of the rule block according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const RuleBlock* ruleBlock) const;
        /**
         * Returns a string representation of the norm according to the Fuzzy Control Language specification
         * @param norm is the norm
         * @return a string representation of the norm according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const Norm* norm) const;
        /**
         * Returns a string representation of the defuzzifier according to the Fuzzy Control Language specification
         * @param defuzzifier is the defuzzifier
         * @return a string representation of the defuzzifier according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const Defuzzifier* defuzzifier) const;
        /**
         * Returns a string representation of the term according to the Fuzzy Control Language specification
         * @param term is the term
         * @return a string representation of the term according to the Fuzzy Control Language specification
         */
        virtual std::string toString(const Term* term) const;

        virtual FclExporter* clone() const FL_IOVERRIDE;
    };

}
#endif /* FL_FCLEXPORTER_H */
