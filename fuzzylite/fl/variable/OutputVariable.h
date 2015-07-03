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

#ifndef FL_OUTPUTVARIABLE_H
#define FL_OUTPUTVARIABLE_H

#include "fl/variable/Variable.h"

namespace fl {
    class Accumulated;
    class Defuzzifier;

    /**
     * OutputVariable represents an output variable of the fuzzy controller
     * 
     * @author Juan Rada-Vilela, Ph.D.
     * @see Variable
     * @see InputVariable
     * @see Term
     * @since 4.0
     */
    class FL_API OutputVariable : public Variable {
    private:
        void copyFrom(const OutputVariable& other);
    protected:
        FL_unique_ptr<Accumulated> _fuzzyOutput;
        FL_unique_ptr<Defuzzifier> _defuzzifier;
        scalar _previousValue;
        scalar _defaultValue;
        bool _lockPreviousValue;

    public:
        explicit OutputVariable(const std::string& name = "",
                scalar minimum = -fl::inf, scalar maximum = fl::inf);
        OutputVariable(const OutputVariable& other);
        OutputVariable& operator=(const OutputVariable& other);
        virtual ~OutputVariable() FL_IOVERRIDE;
        FL_DEFAULT_MOVE(OutputVariable)

        /**
         * Gets the fuzzy output value
         * @return the fuzzy output value
         */
        virtual Accumulated* fuzzyOutput() const;

        virtual void setName(const std::string& name) FL_IOVERRIDE;

        virtual void setMinimum(scalar minimum) FL_IOVERRIDE;
        virtual void setMaximum(scalar maximum) FL_IOVERRIDE;

        /**
         * Sets the defuzzifier of the output variable
         * @param defuzzifier is the defuzzifier of the output variable
         */
        virtual void setDefuzzifier(Defuzzifier* defuzzifier);
        /**
         * Gets the defuzzifier of the output variable
         * @return the defuzzifier of the output variable
         */
        virtual Defuzzifier* getDefuzzifier() const;

        /**
         * Sets the previous value of the output variable. This value is managed
         * automatically upon calling @link{#defuzzify()
         * @param previousValue is the previous value to store
         */
        virtual void setPreviousValue(scalar previousValue);
        /**
         * Gets the previous value of the output variable. Initially, the 
         * previous value is @link{fl#nan
         * @return the previous value, or @link{fl#nan if there is none
         */
        virtual scalar getPreviousValue() const;

        /**
         * Sets the default value of the output variable. The default value 
         * will replace the current value whenever the defuzzification process 
         * results in a non-finite value.
         * @param defaultValue is the default value 
         */
        virtual void setDefaultValue(scalar defaultValue);
        /**
         * Gets the default value of the output variable. The default value 
         * will replace the current value whenever the defuzzification process 
         * results in a non-finite value.
         * @return the default value
         */
        virtual scalar getDefaultValue() const;

        /**
         * Sets whether the previous value is utilized as a replacement of the 
         * current value whenever the defuzzification process results in a 
         * non-finite value. If `true`, the previous value takes precedence over
         * the default value, unless there is no previous value. Otherwise, the
         * default value is utilized in such cases.
         * @param lockPreviousOutputValue is a boolean that indicates whether to 
         * lock the previous output value
         */
        virtual void setLockPreviousValue(bool lockPreviousOutputValue);
        /**
         * Gets whether the previous value is utilized as a replacement of the 
         * current value whenever the defuzzification process results in a 
         * non-finite value. If `true`, the previous value takes precedence over
         * the default value, unless there is no previous value. Otherwise, the
         * default value is utilized in such cases.
         * @returns a boolean that indicates whether to lock the previous output value
         */
        virtual bool isLockPreviousValue() const;

        /**
         * Defuzzifies the output variable, stores the previous output value, 
         * and updates the output value. @todo reflect code
         */
        virtual void defuzzify();

        /**
         * Gets the current fuzzy output value before defuzzification.
         * @return the fuzzy output value
         */
        virtual std::string fuzzyOutputValue() const;

        /**
         * Clears the Accumulated fuzzy output value, and sets the `value` and
         * `previousValue` to @link{fl#nan
         */
        virtual void clear();

         /**
         * Gets the representation of the output variable in the 
         * FuzzyLite Language (FLL)
         * @return the output variable in FLL
         * @see FllExporter
         */
        virtual std::string toString() const FL_IOVERRIDE;

    };

}
#endif /* FL_OUTPUTVARIABLE_H */
