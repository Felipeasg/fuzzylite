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

#ifndef FL_ACTIVATION_H
#define	FL_ACTIVATION_H

#include "fl/fuzzylite.h"

namespace fl {
    class RuleBlock;

    /**
      Base class of all activation methods for RuleBlock%s.
      An activation method for any given RuleBlock needs to:
      - Activate the necessary Rule%s.
      - Deactivate the remaining Rule%s.
      
      @author Juan Rada-Vilela, Ph.D.
      @see Rule
      @see RuleBlock
      @see ActivationFactory
      @since 6.0
     */

    class FL_API Activation {
    public:

        Activation() {
        }

        virtual ~Activation() {
        }

        FL_DEFAULT_COPY_AND_MOVE(Activation)

        /**
          Provides the name of the activation method. The name is utilized to
          register the activation method in ActivationFactory
          
          @return the name of the activation method
          @see ActivationFactory
         */
        virtual std::string className() const = 0;

        /**
          Provides the parameters of the activation method. The parameters
          can be used to configure other instances of the activation method. 
          
          @return the parameters of the activation method
         */
        virtual std::string parameters() const = 0;

        /**
          Configures the activation method with the given parameters.
          
          @param parameters is a list of space-separated parameters
         */
        virtual void configure(const std::string& parameters) = 0;

        /**
          Activates the rule block.
          
          @param ruleBlock is the rule block to activate
         */
        virtual void activate(RuleBlock* ruleBlock) const = 0;

        /**
          Clones the activation method.
          
          @return a clone of the activation method
         */
        virtual Activation* clone() const = 0;
    };

}

#endif	/* FL_ACTIVATION_H */
