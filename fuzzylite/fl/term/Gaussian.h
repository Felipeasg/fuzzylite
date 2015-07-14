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

#ifndef FL_GAUSSIAN_H
#define FL_GAUSSIAN_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * %Term for the Gaussian curve membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 4.0
     */
    class FL_API Gaussian : public Term {
    protected:
        scalar _mean;
        scalar _standardDeviation;

    public:
        explicit Gaussian(const std::string& name = "",
                scalar mean = fl::nan,
                scalar standardDeviation = fl::nan,
                scalar height = 1.0);
        virtual ~Gaussian() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Gaussian)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `mean standardDeviation [height]`
         * @return `mean standardDeviation [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `mean standardDeviation [height]`
         * @param parameters as `mean standardDeviation [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
         * Computes the membership function evaluated at @f$x@f$
         * @param x
         * @return @f$ h \times \exp(-(x-\mu)^2/(2\sigma^2))
         * @f$
         * 
         * where @f$h@f$ is the height of the term,
         *       @f$\mu@f$ is the mean of the Gaussian,
         *       @f$\sigma@f$ is the standard deviation of the Gaussian
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Sets the mean of the Gaussian curve
         * @param mean is the mean of the Gaussian curve
         */
        virtual void setMean(scalar mean);
        /**
         * Gets the mean of the Gaussian curve
         * @return the mean of the Gaussian curve
         */
        virtual scalar getMean() const;

        /**
         * Sets the standard deviation of the Gaussian curve
         * @param standardDeviation is the standard deviation of the Gaussian curve
         */
        virtual void setStandardDeviation(scalar standardDeviation);
        /**
         * Gets the standard deviation of the Gaussian curve
         * @return the standard deviation of the Gaussian curve
         */
        virtual scalar getStandardDeviation() const;

        virtual Gaussian* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };

}
#endif /* FL_GAUSSIAN_H */
