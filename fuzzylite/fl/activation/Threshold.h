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

#ifndef FL_THRESHOLD_H
#define	FL_THRESHOLD_H

#include "fl/fuzzylite.h"

#include "fl/activation/Activation.h"

namespace fl {

    /**
      Activation method that activates the Rule%s of any given RuleBlock iff 
      their activation degrees satisfy the given comparison operator for the 
      given threshold. Otherwise, the rules are deactivated.
      
      @author Juan Rada-Vilela, Ph.D.
      @see Rule
      @see RuleBlock
      @see ActivationFactory
      @since 6.0
     */
    class FL_API Threshold : public Activation {
    public:

        /**
          Comparison provides six comparison operators for the threshold. 
         */
        enum Comparison {
            /**@f$a = b@f$**/ EqualTo,
            /**@f$a \neq b@f$**/ NotEqualTo,
            /**\f$a < b\f$**/ LessThan,
            /**@f$a \leq b@f$**/ LessThanOrEqualTo,
            /**@f$a > b@f$**/ GreaterThan,
            /**@f$a \geq b@f$**/ GreaterThanOrEqualTo
        };
    protected:
        Comparison _comparison;
        scalar _threshold;
    public:
        /**
          A constructor with the comparison operator and threshold.
          
          @param comparison is the comparison operator.
          @param threshold is the threshold (default: `0.0`)
         */
        Threshold(Comparison comparison = GreaterThan, scalar threshold = 0.0);
        virtual ~Threshold();
        FL_DEFAULT_COPY_AND_MOVE(Threshold)

        virtual std::string className() const FL_IOVERRIDE;

        /**
          Provides the comparison operator (in short form) followed by the 
          threshold.
          
          @return comparison operator and threshold
         */
        virtual std::string parameters() const FL_IOVERRIDE;

        /**
          Configures the activation method with the comparison operator (in 
          short form) and the threshold given in the parameters
          
          @param parameters is the comparison operator and threshold
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
          Sets the comparison operator for the activation method
          
          @param comparison is an enum option from {@link Comparison}
         */
        virtual void setComparison(Comparison comparison);

        /**
          Gets the comparison operator for the activation method
          
          @return the comparison operator as an enum option
         */
        virtual Comparison getComparison() const;

        /**
          Gets the short form of the comparison operator of the activation method 
          
          @return one of ("==", "!=", "<", ">", "<=", ">=")
         */
        virtual std::string getComparisonOperator() const;

        /**
          Parses the comparison operator, or throws an
          exception if the parameter does not correspond to a valid operator
          
          @param comparisonOperator is one of ("==", "!=", "<", ">", "<=", ">=")
         */
        virtual Comparison parseComparisonOperator(const std::string& comparisonOperator) const;

        /**
          Sets the threshold of the activation method
          
          @param threshold is the threshold for activation degrees
         */
        virtual void setThreshold(scalar threshold);

        /**
          Gets the threshold of the activation method
          
          @return the threshold for activation degrees
         */
        virtual scalar getThreshold() const;

        /**
          Sets the comparison operator and the threshold for the activation method 
         
          @param comparison is an enum option
          @param threshold is the threshold for activation degrees
         */
        virtual void setComparisonThreshold(Comparison comparison, scalar threshold);

        /**
          Sets the comparison operator (in short form) and the threshold for 
          the activation method 
          
          @param comparison is an enum option
          @param threshold is the threshold for activation degrees
         */
        virtual void setComparisonThreshold(const std::string& comparison, scalar threshold);

        /**
          Determines whether the activation method will activate a rule with
          the given activation degree.
          
          @param activationDegree an activation degree
          @return whether the activation degree satisfy the condition 
          for activation
         */
        virtual bool activates(scalar activationDegree) const;

        /**
          Activates the rules of the given rule block iff 
          their activation degrees satisfy the given comparison for the  
          given threshold. Otherwise, the rules are deactivated.
          
          @param ruleBlock
         */
        virtual void activate(RuleBlock* ruleBlock) const FL_IOVERRIDE;

        virtual Threshold* clone() const FL_IOVERRIDE;

        static Activation* constructor();
    };

}

#endif	/* FL_THRESHOLD_H */
