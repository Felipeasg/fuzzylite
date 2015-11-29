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

#ifndef FL_ACCUMULATED_H
#define FL_ACCUMULATED_H

#include "fl/term/Term.h"

#include <vector>

namespace fl {

    class Activated;
    class SNorm;
    class TNorm;

    /**
      Fuzzy set that contains the Activated terms from the Antecedent%s of the Rule%s, 
      thereby serving as a fuzzy output value in OutputVariable. The instances 
      of the activated terms added for accumulation will be owned by Accumulated, and will be destroyed upon
      clearing the term.
      
      @author Juan Rada-Vilela, Ph.D.
      @see Antecedent
      @see Rule
      @see OutputVariable
      @see Activated
      @see Term
      @since 4.0
     */
    class FL_API Accumulated : public Term {
    private:
        void copyFrom(const Accumulated& source);
    protected:
        std::vector<Activated*> _terms;
        scalar _minimum, _maximum;
        FL_unique_ptr<SNorm> _accumulation;
    public:
        explicit Accumulated(const std::string& name = "",
                scalar minimum = fl::nan,
                scalar maximum = fl::nan,
                SNorm* accumulation = fl::null);
        Accumulated(const Accumulated& other);
        Accumulated& operator=(const Accumulated& other);
        virtual ~Accumulated() FL_IOVERRIDE;
        FL_DEFAULT_MOVE(Accumulated)

        virtual std::string className() const FL_IOVERRIDE;
        /**
          Provides the parameters of the term
          @return "accumulation minimum maximum terms"
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
          Does nothing
          @param parameters are irrelevant 
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        virtual Accumulated* clone() const FL_IOVERRIDE;
        /**
          Accumulates the membership function values of @f$x@f$ utilizing the
          accumulation operator
          @param x is a value
          @return @f$\sum_i{\mu_i(x)}, i \in \mbox{terms}@f$
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;
        /**
          Computes the accumulated activation degree for the given term. 
          If the same term is present multiple times, the accumulation operator 
          is utilized to sum the activation degrees of the term. If the 
          accumulation operator is fl::null, a regular sum is performed.
          @param forTerm is the term for which to compute the accumulated 
          activation degree
          @return the accumulated activation degree for the given term
         */
        virtual scalar activationDegree(const Term* forTerm) const;

        virtual std::string toString() const FL_IOVERRIDE;

        /**
          Sets the minimum of the range of the fuzzy set
          @param minimum is the minimum of the range of the fuzzy set
         */
        virtual void setMinimum(scalar minimum);
        /**
          Gets the minimum of the range of the fuzzy set
          @return the minimum of the range of the fuzzy set
         */
        virtual scalar getMinimum() const;

        /**
          Sets the maximum of the range of the fuzzy set
          @param maximum is the maximum of the range of the fuzzy set
         */
        virtual void setMaximum(scalar maximum);
        /**
          Gets the maximum of the range of the fuzzy set
          @return the maximum of the range of the fuzzy set
         */
        virtual scalar getMaximum() const;

        /**
          Sets the range of the fuzzy set to `[minimum, maximum]`
          @param minimum is the minimum of the range of the fuzzy set
          @param maximum is the maximum of the range of the fuzzy set
         */
        virtual void setRange(scalar minimum, scalar maximum);
        /**
          Provides the magnitude of the range of the fuzzy set, 
          @return the magnitude of the range of the fuzzy set, 
          i.e., `maximum - minimum`
         */
        virtual scalar range() const;

        /**
          Sets the accumulation operator
          @param accumulation is the accumulation operator
         */
        virtual void setAccumulation(SNorm* accumulation);
        /**
          Gets the accumulation operator
          @return the accumulation operator
         */
        virtual SNorm* getAccumulation() const;

        /**
          Adds a new Activated term (from the parameters) to the fuzzy set
          @param term is the activated term
          @param degree is the activation degree
          @param implication is the implication operator
         */
        virtual void addTerm(const Term* term, scalar degree, const TNorm* implication);
        /**
          Adds the activated term to the fuzzy set. The activated term 
          will be deleted upon {@link #clear()}
          @param term is the activated term
         */
        virtual void addTerm(Activated* term);
        /**
          Gets the term at the given index
          @param index is the index of the term
          @return the activated term at the given index
         */
        virtual Activated* getTerm(std::size_t index) const;
        /**
          Removes the term at the given index without deleting the term 
          @param index is the index of the term
          @return the removed term
         */
        virtual Activated* removeTerm(std::size_t index);
        /**
          Provides the number of activated terms 
          @return the number of activated terms
         */
        virtual std::size_t numberOfTerms() const;
        /**
          Provides an immutable vector of activated terms
          @return an immutable vector of activated terms
         */
        virtual const std::vector<Activated*>& terms() const;
        /**
          Provides a mutable vector of activated terms
          @return a mutable vector of activated terms
         */
        virtual std::vector<Activated*>& terms();
        /**
          Indicates whether the vector of activated terms is empty
          @return whether the vector of activated terms is empty
         */
        virtual bool isEmpty() const;
        /**
          Clears and deletes the activated terms
         */
        virtual void clear();
    };

}
#endif /* FL_ACCUMULATED_H */
