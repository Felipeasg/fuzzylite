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
     * Term for the linear membership function
     * @author Juan Rada-Vilela, Ph.D.
     * @see Term
     * @see Variable
     * @since 4.0
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
         * Provides the coefficients of the linear function as `a b c`
         * @return `a b c`
         */
        virtual std::string parameters() const FL_IOVERRIDE;
        /**
         * Configures the term with the coefficients given as `a b c`
         * @param parameters as `a b c`
         */
        virtual void configure(const std::string& parameters) FL_IOVERRIDE;

        /**
         * Computes the membership function evaluated at @f$x@f$
         * @param x is irrelevant
         * @return @f$\sum_{i=0}^{I}{(c_ix_i)}+k@f$
         * 
         * where @f$I@f$ is the number of input variables in the Engine,
         *       @f$c_i@f$ is the @f$i@f$th coefficient of Linear,
         *       @f$x_i@f$ is the input value of the @f$i@f$th input variable,
         *       @f$k@f$ is a constant registered as the last coefficient in Linear
         */
        virtual scalar membership(scalar x) const FL_IOVERRIDE;

        /**
         * Sets the coefficients and the engine for the term
         * @param coefficients is a vector of coefficients
         * @param engine is the engine to relate the coefficients with the input variables 
         */
        virtual void set(const std::vector<scalar>& coefficients, const Engine* engine);

        /**
         * Sets the coefficients of the term
         * @param coefficients is a vector of coefficients
         */
        virtual void setCoefficients(const std::vector<scalar>& coefficients);
        /**
         * Gets an immutable vector of the coefficients of the term
         * @return an immutable vector of the coefficients of the term
         */
        virtual const std::vector<scalar>& coefficients() const;
        /**
         * Gets a mutable vector of the coefficients of the term
         * @return a mutable vector of the coefficients of the term
         */
        virtual std::vector<scalar>& coefficients();

        /**
         * Sets the engine for which the term relates the coefficients to the input variables
         * @param engine is the engine for which the term relates the coefficients to the input variables
         */
        virtual void setEngine(const Engine* engine);
        /**
         * Gets the engine for which the term relates the coefficients to the input variables
         * @return the engine for which the term relates the coefficients to the input variables
         */
        virtual const Engine* getEngine() const;

        virtual Linear* clone() const FL_IOVERRIDE;

        static Term* constructor();

        /**
         * Creates a Linear term from a variadic set of coefficients. 
         * Beware: this method is unsafe and must be used with care by 
         * ensuring:
         * - the data type of each variadic arguments is the same, e.g., 
         * @f$(1.0, 2.0, 3.0)@f$ are all fl::scalar%s, whereas in
         * @f$(1.0, 2, 3.0)@f$ the second term is an integer, which will cause
         * memory access issues due to the difference in size between 
         * `int` and `fl::scalar`,
         * - the number of variadic arguments is exactly the same as the 
         * number of input variables in the engine plus one in order to match 
         * the equation: @f$aX + bY + c@f$, where @f$X@f$ and @f$Y@f$ are input 
         * variables, and @f$a@f$, @f$b@f$ and @f$c@f$ are coefficients.
         * @param name is the name of the resulting term
         * @param engine the engine for which the term relates the coefficients 
         * to the input variables
         * @param firstCoefficient is the first coefficient of the term, 
         * which relates to the first input variable
         * @param ... a variadic number of coefficients whose type need to be 
         * the same as the first coefficient
         * @return a new Linear term with the given parameters
         */
        template <typename T>
        static Linear* create(const std::string& name, const Engine* engine,
                T firstCoefficient, ...);
    };
}

/**
 * Template implementation
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
