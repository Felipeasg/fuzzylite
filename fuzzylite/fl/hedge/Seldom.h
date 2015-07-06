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

#ifndef FL_SELDOM_H
#define FL_SELDOM_H

#include "fl/hedge/Hedge.h"

namespace fl {

    /**
     * Seldom is a hedge in the ordered set 
     * (Not, Seldom, Somewhat, Very, Extremely, Any)
     */
    class FL_API Seldom : public Hedge {
    public:
        std::string name() const FL_IOVERRIDE;
        /**
         * Computes Seldom for a membership function value \f$x\f$
         * @param x is a membership function value
         * @return \f$
         * \cases{
         * \sqrt{x/2} & \mbox{if $x \le 0.5$} \cr
         * 1-\sqrt{(1-x)/2} & \mbox{otherwise}\cr
         * }
         * \f$
         */
        
        scalar hedge(scalar x) const FL_IOVERRIDE;
        Seldom* clone() const FL_IOVERRIDE;

        /**
         * @return a new instance of Seldom
         */
        static Hedge* constructor();
    };

}
#endif /* FL_SELDOM_H */
