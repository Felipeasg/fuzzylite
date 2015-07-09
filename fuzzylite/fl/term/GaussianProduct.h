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

#ifndef FL_GAUSSIANPRODUCT_H
#define FL_GAUSSIANPRODUCT_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * %Term for the two-sided Gaussian membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 4.0
     */
    class FL_API GaussianProduct : public Term {
    protected:
        scalar _meanA;
        scalar _standardDeviationA;
        scalar _meanB;
        scalar _standardDeviationB;

    public:
        explicit GaussianProduct(const std::string& name = "",
                scalar meanA = fl::nan,
                scalar standardDeviationA = fl::nan,
                scalar meanB = fl::nan,
                scalar standardDeviationB = fl::nan,
                scalar height = 1.0);
        virtual ~GaussianProduct() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(GaussianProduct)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `meanA standardDeviationA meanB standardDeviationB [height]`
         * @return `meanA standardDeviationA meanB standardDeviationB [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `meanA standardDeviationA meanB standardDeviationB [height]`
         * @param parameters as `meanA standardDeviationA meanB standardDeviationB [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;
        //@todo
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Sets the mean of the first Gaussian curve
         * @param meanA is the mean of the first Gaussian curve
         */
        virtual void setMeanA(scalar meanA);
        /**
         * Gets the mean of the first Gaussian curve
         * @return the mean of the first Gaussian curve
         */
        virtual scalar getMeanA() const;

        /**
         * Sets the standard deviation of the first Gaussian curve
         * @param sigmaA is the standard deviation of the first Gaussian curve
         */
        virtual void setStandardDeviationA(scalar sigmaA);
        /**
         * Gets the standard deviation of the first Gaussian curve
         * @return the standard deviation of the first Gaussian curve
         */
        virtual scalar getStandardDeviationA() const;

        /**
         * Sets the mean of the second Gaussian curve
         * @param meanB is the mean of the second Gaussian curve
         */
        virtual void setMeanB(scalar meanB);
        /**
         * Gets the mean of the second Gaussian curve
         * @return the mean of the second Gaussian curve
         */
        virtual scalar getMeanB() const;

        /**
         * Sets the standard deviation of the second Gaussian curve
         * @param sigmaB is the standard deviation of the second Gaussian curve
         */
        virtual void setStandardDeviationB(scalar sigmaB);
        /**
         * Gets the standard deviation of the second Gaussian curve
         * @return the standard deviation of the second Gaussian curve
         */
        virtual scalar getStandardDeviationB() const;

        virtual GaussianProduct* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };
}
#endif  /* FL_GAUSSIANPRODUCT_H */
