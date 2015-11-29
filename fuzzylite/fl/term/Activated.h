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

#ifndef FL_ACTIVATED_H
#define FL_ACTIVATED_H

#include "fl/term/Term.h"

namespace fl {
    class TNorm;

    /**
      Term that contains pointers to the necessary information of an activated term, 
      but does not assume the ownership of the pointers. Activated was previously 
      named `Thresholded` in version 4.0
      
      @author Juan Rada-Vilela, Ph.D.
      @see OutputVariable
      @see Activated
      @see Term
      @since 5.0
     */
    class FL_API Activated : public Term {
    protected:
        const Term* _term;
        scalar _degree;
        const TNorm* _implication;

    public:
        explicit Activated(const Term* term = fl::null, scalar degree = 1.0,
                const TNorm* implication = fl::null);
        virtual ~Activated() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Activated)

        virtual std::string className() const FL_IOVERRIDE;
        /**
          Provides the parameters of the term as "degree implication term"
          @return "degree implication term"
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
          Does nothing.
          @param parameters are irrelevant
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
          Computes the implication of the activation degree and the membership 
          function value of @f$x@f$
          @param x is a value
          @return @f$d \otimes \mu(x)@f$, where @f$d@f$ is the activation degree
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;
        virtual std::string toString() const FL_IOVERRIDE;

        /**
          Sets the activated term
          @param term is the activated term 
         */
        virtual void setTerm(const Term* term);
        /**
          Gets the activated term 
          @return the activated term 
         */
        virtual const Term* getTerm() const;

        /**
          Sets the activation degree of the term
          @param degree is the activation degree of the term
         */
        virtual void setDegree(scalar degree);
        /**
          Gets the activation degree of the term
          @return the activation degree of the term
         */
        virtual scalar getDegree() const;

        /**
          Sets the implication operator
          @param implication is the implication operator
         */
        virtual void setImplication(const TNorm* implication);
        /**
          Gets the implication operator
          @return the implication operator
         */
        virtual const TNorm* getImplication() const;

        virtual Activated* clone() const FL_IOVERRIDE;
    };

}
#endif /* FL_ACTIVATED_H */
