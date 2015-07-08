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

#ifndef FL_NILPOTENTMINIMUM_H
#define FL_NILPOTENTMINIMUM_H

#include "fl/norm/TNorm.h"

namespace fl {

    /**
     * T-Norm for the nilpotent minimum of values
     * @author Juan Rada-Vilela, Ph.D.
     * @see NilpotentMaximum
     * @see TNorm
     * @see TNormFactory
     * @see Norm
     * @since 5.0
     */
    class FL_API NilpotentMinimum : public TNorm {
    public:
        std::string className() const FL_IOVERRIDE;
        /**
         * Computes the nilpotent minimum of two membership function values
         * @param a is a membership function value
         * @param b is a membership function value
         * @return @f$\cases{
         * \min(a,b) & \mbox{if $a+b>1$} \cr
         * 0.0 & \mbox{otherwise}
         * }@f$
         */
        scalar compute(scalar a, scalar b) const FL_IOVERRIDE;
        NilpotentMinimum* clone() const FL_IOVERRIDE;

        static TNorm* constructor();
    };
}

#endif  /* FL_NILPOTENTMINIMUM_H */
