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

#ifndef FL_BINARY_H
#define	FL_BINARY_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * %Term for the binary membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 6.0
     */
    class FL_API Binary : public Term {
    protected:
        scalar _threshold;

    public:
        explicit Binary(const std::string& name = "", scalar threshold = fl::nan, scalar height = 1.0);
        virtual ~Binary() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Binary)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `threshold [height]`
         * @return `threshold [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `threshold [height]`
         * @param parameters as `threshold [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
         * Computes the membership function evaluated at @f$x@f$
         * @param x 
         * @return @f$\begin{cases}
         * 0h & \mbox{if $x<t$} \cr
         * 1h & \mbox{otherwise}
         * \end{cases}@f$
         *
         * where @f$h@f$ is the height of the term,
         *       @f$t@f$ is the threshold of the Binary
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Sets the threshold
         * @param threshold
         */
        virtual void setThreshold(scalar threshold);
        /**
         * Gets the threshold
         * @return 
         */
        virtual scalar getThreshold() const;

        virtual Binary* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };

}

#endif	/* FL_BINARY_H */
