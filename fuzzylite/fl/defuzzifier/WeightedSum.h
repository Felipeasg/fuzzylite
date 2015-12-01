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

#ifndef FL_WEIGHTEDSUM_H
#define FL_WEIGHTEDSUM_H


#include "fl/defuzzifier/WeightedDefuzzifier.h"

namespace fl {

    /**
      The WeightedSum class is a WeightedDefuzzifier that computes the
      weighted sum of a fuzzy set represented in an AccumulatedTerm

      @author Juan Rada-Vilela, Ph.D.
      @see WeightedAverage
      @see WeightedDefuzzifier
      @see Defuzzifier
      @since 4.0
     */
    class FL_API WeightedSum : public WeightedDefuzzifier {
    public:
        explicit WeightedSum(Type type = Automatic);
        explicit WeightedSum(const std::string& type);
        virtual ~WeightedSum() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(WeightedSum)

        virtual std::string className() const FL_IOVERRIDE;
        /**
          Computes the weighted sum of a fuzzy set represented in an
          AccumulatedTerm as @f$y = \sum_i{w_iz_i} @f$,
          where @f$w_i@f$ is the activation degree of term @f$i@f$, and @f$z_i
          = \mu_i(w_i) @f$.

          If the accumulation operator in the given AccumulatedTerm is
          fl::null, then the WeightedDefuzzifier yields the typical operation
          defined by the given equation. Otherwise, the accumulation operator
          is utilized to compute a single weight from the weights of the
          repeated terms in the fuzzy set, and then proceed with the given
          equation.
          
          @param term is the fuzzy set represented as an AccumulatedTerm
          @param minimum is the minimum value of the range (only used for Tsukamoto)
          @param maximum is the maximum value of the range (only used for Tsukamoto)
          @return 
         */
        virtual scalar defuzzify(const Term* term,
                scalar minimum, scalar maximum) const FL_IOVERRIDE;
        virtual WeightedSum* clone() const FL_IOVERRIDE;

        static Defuzzifier* constructor();
    };
}

#endif  /* FL_WEIGHTEDSUM_H */
