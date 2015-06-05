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

#ifndef FL_HIGHEST_H
#define	FL_HIGHEST_H

#include "fl/fuzzylite.h"

#include "fl/activation/Activation.h"

namespace fl {

    /**
     * Highest activates a given number of rules whose activation 
     * degrees are the highest in any given {@link RuleBlock}.  
     * 
     * The rules are activated in descending order according to their activation 
     * degrees. If the given number of rules to activate is negative, then 
     * this class activates the rules with the lowest activation degrees, 
     * which is equivalent to the {@link Lowest} activation.
     * 
     * @author Juan Rada-Vilela, Ph.D.
     * @see Lowest
     * @see Rule
     * @see RuleBlock
     * @see ActivationFactory
     * @since 6.0
     */
    class FL_API Highest : public Activation {
    protected:
        int _activatedRules;
    public:
        /**
         * A constructor with the number of rules.
         * 
         * @param numberOfRules number of rules to activate. Defaults to 1.
         */
        Highest(int numberOfRules = 1);
        virtual ~Highest();
        FL_DEFAULT_COPY_AND_MOVE(Highest)

        virtual std::string className() const FL_IOVERRIDE;

        /**
         * Returns the number of rules to activate
         * 
         * @return number of rules to activate
         */
        virtual std::string parameters() const FL_IOVERRIDE;

        /**
         * Configures the activation method with the number of rules specified 
         * in the parameters
         * 
         * @param parameters is the number of rules to activate
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
         * Sets the number of rules to activate. 
         * 
         * @param activatedRules is the number of rules to activate. If negative, the 
         * rules with the lowest activation degrees will be activated.
         */
        virtual void setActivatedRules(int activatedRules);

        /**
         * Returns the number of rules to activate. 
         * 
         * @return the number of rules to activate. If negative, the 
         * rules with the lowest activation degrees will be activated.
         */
        virtual int getActivatedRules() const;

        /**
         * Activates the rules with the highest activation degrees in the 
         * given {@link RuleBlock}.
         * 
         * If the number of rules to activate is negative, then Highest
         * activates the given number of rules with the lowest activation degrees, 
         * which is equivalent to the {@link Lowest} activation.
         * 
         * @param ruleBlock is the rule block to activate.
         */
        virtual void activate(RuleBlock* ruleBlock) const FL_IOVERRIDE;

        virtual Highest* clone() const FL_IOVERRIDE;

        static Activation* constructor();
    };
}

#endif	/* FL_HIGHEST_H */
