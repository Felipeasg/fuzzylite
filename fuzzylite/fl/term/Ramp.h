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

#ifndef FL_RAMP_H
#define FL_RAMP_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * (Edge) term for the ramp membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 4.0
     */
    class FL_API Ramp : public Term {
    protected:
        scalar _start, _end;

    public:
        
        /**The direction of the ramp**/
        enum Direction {
            /** `(_/)` increases to the right **/ Positive, 
            /** `(--)` slope is zero **/ Zero, 
            /** `(\_)` increases to the left **/ Negative
        };
        explicit Ramp(const std::string& name = "",
                scalar start = fl::nan,
                scalar end = fl::nan,
                scalar height = 1.0);
        virtual ~Ramp() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Ramp)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `start end [height]`
         * @return `start end [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `start end [height]`
         * @param parameters as `start end [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        //@todo
        virtual scalar membership(scalar x) const FL_IOVERRIDE;
        
        /**
         * Sets the start of the ramp
         * @param start is the start of the ramp
         */
        virtual void setStart(scalar start);
        /**
         * Gets the start of the ramp
         * @return the start of the ramp
         */
        virtual scalar getStart() const;

        /**
         * Sets the end of the ramp
         * @param end is the end of the ramp
         */
        virtual void setEnd(scalar end);
        /**
         * Gets the end of the ramp
         * @return the end of the ramp
         */
        virtual scalar getEnd() const;

        /**
         * Provides the direction of the ramp
         * @return the direction of the ramp
         */
        virtual Direction direction() const;

        virtual Ramp* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };
}
#endif  /* FL_RAMP_H */
