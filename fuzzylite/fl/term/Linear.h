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

#ifndef FL_LINEAR_H
#define FL_LINEAR_H

#include "fl/term/Term.h"

namespace fl {
    class Engine;

    /**
      
      The Linear class is a function Term that represents the linear membership
      function.

      @author Juan Rada-Vilela, Ph.D.
      @see Term
      @see Variable
      @since 4.0
    
     */
    class FL_API Linear : public Term {
    protected:
        std::vector<scalar> _coefficients;
        const Engine* _engine;
    public:
        explicit Linear(const std::string& name = "",
                const std::vector<scalar>& coefficients = std::vector<scalar>(),
                const Engine* engine = fl::null);
        virtual ~Linear() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(Linear)

        virtual std::string className() const FL_IOVERRIDE;

        /**
          Returns the coefficients @f$\{c_1, \ldots, c_i, \ldots, c_n, k\}@f$
          of the linear function defined as @f$f(\mathbf{x})=c_1x_1 + \ldots +
          c_ix_i + \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector
          containing the values of the input variables in the order registered
          in the Linear::getEngine()
          @return `"c1 ... ci ... cn k"`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
          Configures the coefficients @f$\{c_1, \ldots, c_i, \ldots, c_n,
          k\}@f$ of the linear function @f$f(\mathbf{x})=c_1x_1 + \ldots +
          c_ix_i + \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector
          containing the values of the input variables in the order registered
          in the Engine
          @param parameters as `"c1 ... ci ... cn k"`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
          Computes the membership function @f$f(\mathbf{x})=c_1x_1 + \ldots +
          c_ix_i + \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector
          containing the values of the input variables in the order registered
          in the Linear::getEngine()
          @param z is irrelevant and not used
          @return @f$\sum_{i=0}^{I}{(c_ix_i)}+k@f$
          
          where @f$I@f$ is the number of input variables in the Engine,
                @f$c_i@f$ is the @f$i@f$th coefficient of Linear,
                @f$x_i@f$ is the input value of the @f$i@f$th input variable,
                @f$k@f$ is a constant registered as the last coefficient in Linear
         */
        virtual scalar membership(scalar z) const FL_IOVERRIDE;

        /**
          Sets the coefficients @f$\{c_1, \ldots, c_i, \ldots, c_n, k\}@f$ of
          the linear function @f$f(\mathbf{x})=c_1x_1 + \ldots + c_ix_i +
          \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector containing
          the values of the input variables in the order registered in the
          given Engine, whose pointer is stored to retrieve the input
          variables when needed

          @param coefficients is a vector of the coefficients @f$\{c_1, \ldots,
          c_i, \ldots, c_n, k\}@f$
          @param engine is the engine from which the values of the input
          variables will be retrieved upon computing the membership function
         */
        virtual void set(const std::vector<scalar>& coefficients, const Engine* engine);

        /**
          Sets the coefficients @f$\{c_1, \ldots, c_i, \ldots, c_n, k\}@f$ of
          the linear function @f$f(\mathbf{x})=c_1x_1 + \ldots + c_ix_i +
          \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector containing
          the values of the input variables in the order registered in the
          Linear::getEngine()
          @param coefficients is a vector of the coefficients @f$\{c_1, \ldots,
          c_i, \ldots, c_n, k\}@f$
         */
        virtual void setCoefficients(const std::vector<scalar>& coefficients);
        /**
          Gets an immutable vector of the coefficients @f$\{c_1, \ldots, c_i,
          \ldots, c_n, k\}@f$ of the linear function @f$f(\mathbf{x})=c_1x_1 +
          \ldots + c_ix_i + \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a
          vector containing the values of the input variables in the order
          registered in the Linear::getEngine()
          @return an immutable vector of the coefficients @f$\{c_1, \ldots,
          c_i, \ldots, c_n, k\}@f$
         */
        virtual const std::vector<scalar>& coefficients() const;
        /**
          Gets a mutable vector of the coefficients @f$\{c_1, \ldots, c_i,
          \ldots, c_n, k\}@f$ of the linear function @f$f(\mathbf{x})=c_1x_1 +
          \ldots + c_ix_i + \ldots + c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a
          vector containing the values of the input variables in the order
          registered in the Linear::getEngine()
          @return a mutable vector of the coefficients @f$\{c_1, \ldots,
          c_i, \ldots, c_n, k\}@f$
         */
        virtual std::vector<scalar>& coefficients();

        /**
          Sets the engine to retrieve the values of the input variables
          required to compute the membership function
          @param engine is the engine from which the values of the input
          variables will be retrieved upon computing the membership function
         */
        virtual void setEngine(const Engine* engine);
        /**
          Gets the engine from which the values of the input variables are
          retrieved upon computing the membership function
          @return the engine from which the values of the input variables will
          be retrieved upon computing the membership function
         */
        virtual const Engine* getEngine() const;

        virtual Linear* clone() const FL_IOVERRIDE;

        static Term* constructor();

        /**
          Creates a Linear term from a variadic set of coefficients. 
          Beware: this method is unsafe and must be used with care by 
          ensuring:
        
          - the data type of each variadic arguments is the same, e.g.,
            @f$(1.0, 2.0, 3.0)@f$ are all fl::scalar%s. Special care needs to
            be taken in the case of @f$(1.0, 2, 3.0)@f$, where the second term
            is an integer because this will cause memory access issues due to
            the difference in size between an `int` and `fl::scalar`,

          - the number of variadic arguments is exactly the same as the number
            of input variables in the engine plus one in order to match the
            equation: @f$f(\mathbf{x})=c_1x_1 + \ldots + c_ix_i + \ldots +
            c_nx_n + k@f$, where @f$\mathbf{x}@f$ is a vector containing the
            values of the input variables , and @f$c_i@f$ is the coefficient
            for the @f$i@f$-th input variable.

          @param name is the name of the term
          @param engine is the engine from which the values of the input
          variables will be retrieved upon computing the membership function
          @param firstCoefficient is the first coefficient of the term, namely
          @f$c_i@f$, which relates to the first input variable
          @param ... a variadic number of coefficients whose type need to be 
          the same as the first coefficient
          @return a new Linear term with the given parameters
         */
        template <typename T>
        static Linear* create(const std::string& name, const Engine* engine,
                T firstCoefficient, ...);
    };
}

/**
  Template implementation
 */

#include "fl/Engine.h"

namespace fl {

    template <typename T>
    inline Linear* Linear::create(const std::string& name,
            const Engine* engine, T firstCoefficient, ...) {
        if (not engine) throw fl::Exception("[linear error] cannot create term <" + name + "> "
                "without a reference to the engine", FL_AT);
        std::vector<scalar> coefficients;
        coefficients.push_back((scalar) firstCoefficient);

        va_list args;
        va_start(args, firstCoefficient);
        for (std::size_t i = 0; i < engine->inputVariables().size(); ++i) {
            coefficients.push_back((scalar) va_arg(args, T));
        }
        va_end(args);

        return new Linear(name, coefficients, engine);
    }
}
#endif  /* FL_LINEAR_H */
