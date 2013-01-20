/* 
 * File:   SigmoidDifference.cpp
 * Author: jcrada
 * 
 * Created on 30 December 2012, 5:58 PM
 */

#include "fl/term/SigmoidDifference.h"

#include "fl/operator/Operator.h"

#include <cmath>
#include <sstream>
namespace fl {

    SigmoidDifference::SigmoidDifference(const std::string& name,
            scalar left, scalar rising,
            scalar right, scalar falling)
    : Term(name), _left(left), _rising(rising), _right(right), _falling(falling) { }

    std::string SigmoidDifference::className() const {
        return "SigmoidDifference";
    }

    SigmoidDifference* SigmoidDifference::copy() const {
        return new SigmoidDifference(*this);
    }

    scalar SigmoidDifference::membership(scalar x) const {
        scalar a = 1.0 / (1 + std::exp(-_rising * (x - _left)));
        scalar b = 1.0 / (1 + std::exp(-_falling * (x - _right)));
        return std::abs(a - b);
    }

    std::string SigmoidDifference::toString() const {
        std::ostringstream ss;
        ss << std::setprecision(FL_DECIMALS) << std::fixed;
        ss << "SigmoidDifference (" << _left << ", " << _rising << ", "
                << _right << ", " << _falling << ")";
        return ss.str();

    }

    void SigmoidDifference::setLeft(scalar leftInflection) {
        this->_left = leftInflection;
    }

    scalar SigmoidDifference::getLeft() const {
        return this->_left;
    }

    void SigmoidDifference::setRising(scalar risingSlope) {
        this->_rising = risingSlope;
    }

    scalar SigmoidDifference::getRising() const {
        return this->_rising;
    }

    void SigmoidDifference::setRight(scalar rightInflection) {
        this->_right = rightInflection;
    }

    scalar SigmoidDifference::getRight() const {
        return this->_right;
    }

    void SigmoidDifference::setFalling(scalar fallingSlope) {
        this->_falling = fallingSlope;
    }

    scalar SigmoidDifference::getFalling() const {
        return this->_falling;
    }



}