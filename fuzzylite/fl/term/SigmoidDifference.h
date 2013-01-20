/* 
 * File:   SigmoidDifference.h
 * Author: jcrada
 *
 * Created on 30 December 2012, 5:58 PM
 */

#ifndef FL_SIGMOIDDIFFERENCE_H
#define	FL_SIGMOIDDIFFERENCE_H

#include "fl/term/Term.h"

namespace fl {

    class SigmoidDifference : public Term {
    protected:
        scalar _left;
        scalar _rising;
        scalar _right;
        scalar _falling;
    public:
        SigmoidDifference(const std::string& name = "",
                scalar left = std::numeric_limits<scalar>::quiet_NaN(),
                scalar rising = std::numeric_limits<scalar>::quiet_NaN(),
                scalar right = std::numeric_limits<scalar>::quiet_NaN(),
                scalar falling = std::numeric_limits<scalar>::quiet_NaN());

        std::string className() const;
        SigmoidDifference* copy() const;

        scalar membership(scalar x) const;

        std::string toString() const;


        void setLeft(scalar leftInflection);
        scalar getLeft() const;

        void setRising(scalar risingSlope);
        scalar getRising() const;

        void setRight(scalar rightInflection);
        scalar getRight() const;

        void setFalling(scalar fallingSlope);
        scalar getFalling() const;


    };
}
#endif	/* FL_SIGMOIDDIFFERENCE_H */
