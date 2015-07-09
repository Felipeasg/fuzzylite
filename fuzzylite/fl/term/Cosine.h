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

#ifndef FL_COSINE_H
#define FL_COSINE_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * %Term for the cosine membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 5.0
     */
    
    class FL_API Cosine : public Term {
    protected:
        scalar _center, _width;
    public:
        explicit Cosine(const std::string& name = "",
                scalar center = fl::nan,
                scalar width = fl::nan,
                scalar height = 1.0);
        virtual ~Cosine() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Cosine)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `center width [height]`
         * @return `center width [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `center width [height]`
         * @param parameters as `center width [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;
        //@todo
        virtual scalar membership(scalar x) const FL_IOVERRIDE;
        /**
         * Sets the center of the cosine
         * @param center is the center of the cosine
         */
        virtual void setCenter(scalar center);
        /**
         * Gets the center of the cosine
         * @return the center of the cosine
         */
        virtual scalar getCenter() const;

        /**
         * Sets the width of the cosine
         * @param width is the width of the cosine
         */
        virtual void setWidth(scalar width);
        /**
         * Gets the width of the cosine
         * @return the width of the cosine
         */
        virtual scalar getWidth() const;

        virtual Cosine* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };
}

#endif  /* FL_COSINE_H */
