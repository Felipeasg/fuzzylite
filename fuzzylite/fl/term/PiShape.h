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

#ifndef FL_PISHAPE_H
#define FL_PISHAPE_H

#include "fl/term/Term.h"

namespace fl {

    /**
     * %Term for the Pi-shaped curve membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 4.0
     */
    class FL_API PiShape : public Term {
    protected:
        scalar _bottomLeft;
        scalar _topLeft;
        scalar _topRight;
        scalar _bottomRight;

    public:
        explicit PiShape(const std::string& name = "",
                scalar bottomLeft = fl::nan,
                scalar topLeft = fl::nan,
                scalar topRight = fl::nan,
                scalar bottomRight = fl::nan,
                scalar height = 1.0);
        virtual ~PiShape() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(PiShape)

        virtual std::string className() const FL_IOVERRIDE;
        /**
         * Provides the parameters of the term as `bottomLeft topLeft topRight bottomRight [height]`
         * @return `bottomLeft topLeft topRight bottomRight [height]`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the parameters given as `bottomLeft topLeft topRight bottomRight [height]`
         * @param parameters as `bottomLeft topLeft topRight bottomRight [height]`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;
        
        //@todo
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Sets the bottom-left value of the curve
         * @param bottomLeft is the bottom-left value of the curve
         */
        virtual void setBottomLeft(scalar bottomLeft);
        /**
         * Gets the bottom-left value of the curve
         * @return the bottom-left value of the curve
         */
        virtual scalar getBottomLeft() const;

        /**
         * Sets the top-left value of the curve
         * @param topLeft is the top-left value of the curve
         */
        virtual void setTopLeft(scalar topLeft);
        /**
         * Gets the top-left value of the curve
         * @return the top-left value of the curve
         */
        virtual scalar getTopLeft() const;

        /**
         * Sets the top-right value of the curve
         * @param topRight is the top-right value of the curve
         */
        virtual void setTopRight(scalar topRight);
        /**
         * Gets the top-right value of the curve
         * @return the top-right value of the curve
         */
        virtual scalar getTopRight() const;

        /**
         * Sets the bottom-right value of the curve
         * @param bottomRight is the bottom-right value of the curve
         */
        virtual void setBottomRight(scalar bottomRight);
        /**
         * Gets the bottom-right value of the curve
         * @return the bottom-right value of the curve
         */
        virtual scalar getBottomRight() const;

        virtual PiShape* clone() const FL_IOVERRIDE;

        static Term* constructor();
    };
}

#endif  /* FL_PISHAPE_H */
