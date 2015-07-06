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

#ifndef FL_ANY_H
#define FL_ANY_H

#include "fl/hedge/Hedge.h"

namespace fl {
    /**
     * Any is a hedge that always returns 1.0. 
     * Antecedent considers Any a syntactically special hedge because it is 
     * not followed by a Term (e.g., `if Variable is any then...`).
     * Amongst hedges, only Any has virtual methods to be overriden 
     * due to its particular case.
     * @todo check other special cases of Any.
     */
    class FL_API Any : public Hedge {
    public:
        Any();
        virtual ~Any() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Any)

        virtual std::string name() const FL_IOVERRIDE;
        /**
         * Always returns 1.0
         * @param x is irrelevant
         * @return \f$1.0\f$
         */
        virtual scalar hedge(scalar x) const FL_IOVERRIDE;
        virtual Any* clone() const FL_IOVERRIDE;

        /**
         * @return a new instance of Any
         */
        static Hedge* constructor();
    };

}
#endif /* FL_ANY_H */
