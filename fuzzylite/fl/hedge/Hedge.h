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

#ifndef FL_HEDGE_H
#define FL_HEDGE_H

#include "fl/fuzzylite.h"

#include <string>

namespace fl {

    /**
     * Base class for all hedges
     * @author Juan Rada-Vilela, Ph.D.
     * @see Hedge
     * @see HedgeFactory
     * @since 4.0
     */
    class FL_API Hedge {
    public:

        Hedge() {
        }

        virtual ~Hedge() {
        }
        FL_DEFAULT_COPY_AND_MOVE(Hedge)

        /**
         * @return the name of the hedge
         */
        virtual std::string name() const = 0;
        /**
         * Computes the hedge for the membership function value @f$x@f$
         * @param x is a membership function value
         * @return the hedge of @f$x@f$
         */
        virtual scalar hedge(scalar x) const = 0;

        /**
         * @return a clone of the hedge.
         */
        virtual Hedge* clone() const = 0;

    };
}

#endif /* FL_HEDGE_H */
