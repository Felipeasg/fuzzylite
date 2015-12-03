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

#ifndef FL_SNORM_H
#define FL_SNORM_H

#include "fl/norm/Norm.h"

namespace fl {

    /**
    
      The SNorm class is the base class for all S-Norms, and it is utilized as
      the disjunction fuzzy logic operator (see RuleBlock::getDisjunction())
      and as the aggregation fuzzy logic operator (see
      OutputVariable::fuzzyOutput() and Accumulated::getAccumulation()).

    
      @author Juan Rada-Vilela, Ph.D.
      @see SNormFactory
      @see Norm
      @since 4.0
    
     */
    class FL_API SNorm : public Norm {
    public:

        SNorm() {
        }

        virtual ~SNorm() FL_IOVERRIDE {
        }

        FL_DEFAULT_COPY_AND_MOVE(SNorm)

        virtual SNorm* clone() const FL_IOVERRIDE = 0;
    };
}
#endif  /* FL_SNORM_H */
