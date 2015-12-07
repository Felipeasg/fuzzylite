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
#define FL_THRESHOLD_H

#include "fl/fuzzylite.h"

#include "fl/activation/Activation.h"

namespace fl {

    /**
    
      The Threshold class is a RuleBlock Activation method that activates the
      rules whose activation degrees satisfy the equation given by the
      comparison operator and the threshold, and deactivates the rules which do
      not satisfy the equation.
      
      @author Juan Rada-Vilela, Ph.D.
      @see Rule
      @see RuleBlock
      @see ActivationFactory
      @since 6.0
    
     */
    
    class FL_API Threshold : public Activation {
    public:

        /**
          Comparison is an enumerator that provides six comparison operators 
          between the activation degree @f$a@f$ and the threshold @f$\theta@f$. 
         */
        enum Comparison {
            /**@f$a = \theta@f$*/ 
            EqualTo,
            /**@f$a \neq \theta@f$*/ 
            NotEqualTo,
            /**\f$a < \theta@f$*/ 
            LessThan,
            /**@f$a \leq \theta@f$*/ 
            LessThanOrEqualTo,
            /**@f$a > \theta@f$*/ 
            GreaterThan,
            /**@f$a \geq \theta@f$*/ 
            GreaterThanOrEqualTo
        };
    protected:
        Comparison _comparison;
        scalar _threshold;
    public:
        /**
          A constructor with the comparison operator and threshold.
          
          @param comparison is the comparison operator
          @param threshold is the threshold
         */
        Threshold(Comparison comparison = GreaterThan, scalar threshold = 0.0);
        virtual ~Threshold();
        FL_DEFAULT_COPY_AND_MOVE(Threshold)

        virtual std::string className() const FL_IOVERRIDE;

        /**
          Returns the comparison operator (in short form) followed by the 
          threshold.
          
          @return comparison operator and threshold
         */
        virtual std::string parameters() const FL_IOVERRIDE;

        /**
          Configures the activation method with the comparison operator (in 
          short form) and the threshold
          
          @param parameters is the comparison operator and threshold
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
          Sets the comparison operator for the activation method
          
          @param comparison is the operator for the activation method
         */
        virtual void setComparison(Comparison comparison);

        /**
          Gets the comparison operator for the activation method
          
          @return comparison operator for the activation method
         */
        virtual Comparison getComparison() const;

        /**
          Gets the short form of the comparison operator of the activation
          method
          @return the short form of an operator in (`==`, `!=`, `<`, `>`, `<=`,
          `>=`)
         */
        virtual std::string getComparisonOperator() const;

        /**
          Parses the comparison operator, or throws an
          exception if the parameter does not correspond to a valid operator
          @param comparisonOperator is an operator in (`==`, `!=`, `<`, `>`,
          `<=`, `>=`)
         */
        virtual Comparison parseComparisonOperator(const std::string& comparisonOperator) const;

        /**
          Sets the threshold of the activation method
          @param threshold is the threshold for activation degrees
         */
        virtual void setThreshold(scalar threshold);

        /**
          Gets the threshold of the activation method
          @return the threshold of the activation method
         */
        virtual scalar getThreshold() const;

        /**
          Sets the comparison operator and the threshold for the activation
          method
          @param comparison is an enum option
          @param threshold is the threshold of the activation method
         */
        virtual void setComparisonThreshold(Comparison comparison, scalar threshold);

        /**
          Sets the comparison operator (in short form) and the threshold for
          the activation method.
          
          @param comparison is an enum option
          @param threshold is the threshold for activation degrees
         */
        virtual void setComparisonThreshold(const std::string& comparison, scalar threshold);

        /**
          Returns whether the activation method will activate a rule with
          the given activation degree
          @todo rename to  `activatesWith`
          
          @param activationDegree an activation degree
          @return whether the comparison equation is satisfied with the  
          activation degree and the threshold
         */
        virtual bool activates(scalar activationDegree) const;

        /**
          Activates the rules whose activation degrees satisfy the comparison
          equation with the given threshold, and deactivate the rules which do
          not.
        
          @param ruleBlock is the rule block to activate
         */
        virtual void activate(RuleBlock* ruleBlock) const FL_IOVERRIDE;

        virtual Threshold* clone() const FL_IOVERRIDE;

        static Activation* constructor();
    };

}

#endif /* FL_THRESHOLD_H */
