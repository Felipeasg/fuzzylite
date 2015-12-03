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


#ifndef FL_TERM_H
#define FL_TERM_H

#include "fl/fuzzylite.h"

#include "fl/Operation.h"

#include <cmath>
#include <string>
#include <vector>

namespace fl {
    class Engine;

    /**
      
      The Term class is an abstract base class that represents linguistic
      terms. As a reference, the terms in this library are grouped as basic,
      extended, edge, and function. The basic terms are Triangle, Trapezoid,
      Rectangle, and Discrete. The extended terms are Bell, Binary, Cosine,
      Gaussian, GaussianProduct, PiShape, SigmoidDifference, SigmoidProduct,
      and Spike. The edge terms are Concave, Ramp, Sigmoid, SShape, and ZShape.
      The function terms are Constant, Linear, and Function.
    
      @author Juan Rada-Vilela, Ph.D.
      @see Variable
      @see InputVariable
      @see OutputVariable
      @since 4.0
    
     */
    class FL_API Term {
    protected:
        std::string _name;
        scalar _height;
    public:

        explicit Term(const std::string& name = "", scalar height = 1.0);
        virtual ~Term();
        FL_DEFAULT_COPY_AND_MOVE(Term)

        /**
          Sets the name of the term
          @param name is the name of term
         */
        virtual void setName(const std::string& name);
        /**
          Gets the name of the term
          @return the name of the term
         */
        virtual std::string getName() const;

        /**
          Sets the height of the term
          @param height is the height of the term
         */
        virtual void setHeight(scalar height);
        /**
          Gets the height of the term
          @return the height of the term
         */
        virtual scalar getHeight() const;

        /**
          Returns the representation of the term in the FuzzyLite Language
          @return the representation of the term in FuzzyLite Language
          @see FllExporter
         */
        virtual std::string toString() const;

        /**
          Returns the name of the class of the term
          @return the name of the class of the term
         */
        virtual std::string className() const = 0;
        /**
          Returns the parameters to configure the term. The parameters are
          separated by spaces. If there is one additional parameter, the
          parameter will be considered as the height of the term; otherwise,
          the height will be set to @f$1.0@f$

          @return the parameters to configure the term (@see ::configure())
         */
        virtual std::string parameters() const = 0;
        /**
          Configures the term with the given parameters. The parameters are
          separated by spaces. If there is one additional parameter, the
          parameter will be considered as the height of the term; otherwise,
          the height will be set to @f$1.0@f$

          @param parameters is the parameters to configure the term
         */
        virtual void configure(const std::string& parameters) = 0;

        /**
          Computes the membership function value at @f$x@f$
          @param x 
          @return the membership function value @f$\mu(x)@f$
         */
        virtual scalar membership(scalar x) const = 0;

        /**
          Creates a clones of the term
          @return a clone of the term
         */
        virtual Term* clone() const = 0;

        //@todo This should not be static, and may not be here either.
        static void updateReference(Term* term, const Engine* engine);
    };

}
#endif /* FL_TERM_H */
