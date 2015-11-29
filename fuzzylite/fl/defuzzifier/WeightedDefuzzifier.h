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

#ifndef FL_WEIGHTEDDEFUZZIFIER_H
#define FL_WEIGHTEDDEFUZZIFIER_H

#include "fl/defuzzifier/Defuzzifier.h"

namespace fl {
    class Activated;

    /**
      Base class for Weighted-base defuzzifiers
      @author Juan Rada-Vilela, Ph.D.
      @since 5.0
     */
    class FL_API WeightedDefuzzifier : public Defuzzifier {
    public:

        enum Type {
            /**Type is automatically inferred from the terms */
            Automatic, 
            /**Type is TakagiSugeno or Inverse Tsukamoto, depending on the terms*/
            TakagiSugeno, 
            /**Type is Tsukamoto*/
            Tsukamoto
        };
        /**
          Returns a string representation of the given type
          @param type is the type of a defuzzifier
          @return a string representation of the given type
         */
        static std::string typeName(Type type);

        explicit WeightedDefuzzifier(Type type = Automatic);
        explicit WeightedDefuzzifier(const std::string& type);
        virtual ~WeightedDefuzzifier() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(WeightedDefuzzifier)

        /**
          Sets the type of the weighted defuzzifier
          @param type is the type of the weighted defuzzifier
         */
        virtual void setType(Type type);
        /**
          Gets the type of the weighted defuzzifier
          @return the type of the weighted defuzzifier
         */
        virtual Type getType() const;
        /**
          Returns a string representation of the type of the defuzzifier
          @return a string representation of the type of the defuzzifier
         */
        virtual std::string getTypeName() const;
        /**
          Infers the type of the defuzzifier based on the given term. If the 
          given term is Constant, Linear or Function, then the type is TakagiSugeno;
          otherwise, the type is Tsukamoto
          @param term is the given term 
          @return the inferred type of the defuzzifier based on the given term
         */
        virtual Type inferType(const Term* term) const;
        /**
          Indicates if the given term is monotonic
          @param term is the given term
          @return a boolean indicating whether the given term is monotonic
         */
        virtual bool isMonotonic(const Term* term) const;

        /**
          Computes the Tsukamoto @f$z@f$-value for the given monotonic term. 
          If the term is not monotonic, then the TakagiSugeno (or InverseTsukamoto) 
          @f$z@f$-value is computed.
          @param monotonic is the monotonic term
          @param activationDegree is the activation degree for the term
          @param minimum is the minimum value of the range of the term
          @param maximum is the maximum value of the range of the term
          @return the Tsukamoto @f$z@f$-value for the given monotonic term, or
          the TakagiSugeno (or InverseTsukamoto) @f$z@f$-value if the term 
          is not monotonic.
         */
        virtual scalar tsukamoto(const Term* monotonic, scalar activationDegree,
                scalar minimum, scalar maximum) const;

    protected:
        Type _type;

    };

}

#endif  /* FL_WEIGHTEDDEFUZZIFIER_H */
