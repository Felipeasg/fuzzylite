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

#ifndef FL_ENGINE_H
#define FL_ENGINE_H

#include "fl/fuzzylite.h"

#include "fl/defuzzifier/IntegralDefuzzifier.h"

#include <string>
#include <vector>

namespace fl {

    class InputVariable;
    class OutputVariable;
    class Variable;
    class RuleBlock;
    class Hedge;
    class TNorm;
    class SNorm;
    class Defuzzifier;

    /**
     * Model of a fuzzy logic controller. 
     * @author Juan Rada-Vilela, Ph.D.
     * @see InputVariable
     * @see OutputVariable
     * @see RuleBlock
     * @since 4.0
     */
    class FL_API Engine {
    private:
        void copyFrom(const Engine& source);
    protected:
        std::string _name;
        std::vector<InputVariable*> _inputVariables;
        std::vector<OutputVariable*> _outputVariables;
        std::vector<RuleBlock*> _ruleblocks;

        void updateReferences() const;

    public:
        explicit Engine(const std::string& name = "");
        Engine(const Engine& other);
        Engine& operator=(const Engine& other);
        virtual ~Engine();
        FL_DEFAULT_MOVE(Engine)

        /**
         * Configures the engine with the given operators
         * @param conjunctionT is a TNorm registered in the TNormFactory
         * @param disjunctionS is an SNorm registered in the SNormFactory
         * @param implicationT is an TNorm registered in the TNormFactory
         * @param accumulationS is an SNorm registered in the SNormFactory
         * @param defuzzifier is a defuzzifier registered in the DefuzzifierFactory
         */
        virtual void configure(const std::string& conjunctionT,
                const std::string& disjunctionS,
                const std::string& implicationT,
                const std::string& accumulationS,
                const std::string& defuzzifier);

        /**
         * Configures the engine with clones of the given operators. 
         * The given operators are automatically deleted within this method.
         * @param conjunction is the operator to process the propositions joined by `and` in the antecedent of the rules
         * @param disjunction is the operator to process the propositions joined by `or` in the antecedent of the rules
         * @param implication is the operator to modify the consequents of the rules based on the activation degree of the antecedents of the rules
         * @param accumulation is the operator to accumulate the resulting implications of the rules
         * @param defuzzifier is the operator to transform the accumulated implications into a single scalar value
         */
        virtual void configure(TNorm* conjunction, SNorm* disjunction,
                TNorm* implication, SNorm* accumulation,
                Defuzzifier* defuzzifier);

        /**
         * 
         * @param status
         * @return 
         */
        virtual bool isReady(std::string* status = fl::null) const;

        virtual void process();

        virtual void restart();

        /**
         * Sets the name of the engine
         * @param name is the name of the engine
         */
        virtual void setName(const std::string& name);
        /**
         * Gets the name of the engine
         * @return the name of the engine
         */
        virtual std::string getName() const;

        /**
         * Sets the value of the given input variable. 
         * @param name is the name of the input variable
         * @param value is the value for the input variable
         */
        virtual void setInputValue(const std::string& name, scalar value);
        /**
         * Gets the value of the given output variable
         * @param name is the name of the output variable
         * @return the value of the given output variable
         */
        virtual scalar getOutputValue(const std::string& name);

        /**
         * Returns a string representation of the engine in the FuzzyLite Language
         * @return a string representation of the engine in the FuzzyLite Language
         */
        virtual std::string toString() const;

        enum Type {
            /**When the output variables have IntegralDefuzzifier%s*/
            Mamdani,
            /**When Mamdani and AlgebraicProduct is the implication operator of the rule blocks */
            Larsen,
            /**When output variables have WeightedDefuzzifier%s of type TakagiSugeno 
             * and the output variables have Constant, Linear, or Function terms
             */
            TakagiSugeno,
            /**When output variables have WeightedDefuzzifier%s of type Tsukamoto
             * and the output variables only have monotonic terms (Concave, Ramp, Sigmoid, SShape, and ZShape)
             */
            Tsukamoto,
            /**When output variables have WeightedDefuzzifier%s of type TakagiSugeno
             * and the output variables do not only have Constant, Linear or Function terms
             */
            InverseTsukamoto,
            /**When output variables have different defuzzifiers*/
            Hybrid,
            /**When output variables have no defuzzifiers*/
            Unknown
        };
        /**
         * Infers the type of the engine based on its current configuration
         * @param name stores a string representation of the engine type 
         * (if the pointer passed is not `fl::null`)
         * @param reason stores a string representation explaining the reasons for the inferred type 
         * (if the pointer passed is not `fl::null`)
         * @return the inferred type of the engine based on its current configuration
         */
        virtual Type type(std::string* name = fl::null, std::string* reason = fl::null) const;

        /**
         * Creates a clone of the engine
         * @return a clone of the engine 
         */
        virtual Engine* clone() const;

        /**
         * Returns a vector that contains the input variables followed by the output variables
         * in the order of insertion
         * @return a vector that contains the input variables followed by the output variables
         * in the order of insertion
         */
        virtual std::vector<Variable*> variables() const;

        /**
         * Adds the input variable
         * @param inputVariable is the input variable
         */
        virtual void addInputVariable(InputVariable* inputVariable);
        /**
         * Sets the input variable at the given index 
         * @param inputVariable is the input variable to set
         * @param index is the index at which the input variable is to be stored
         * @return the input variable previously stored at the given index
         */
        virtual InputVariable* setInputVariable(InputVariable* inputVariable, std::size_t index);
        /**
         * Inserts the input variable at the given index, shifting other variables one position to the right
         * @param inputVariable is the input variable to insert
         * @param index is the index at which the input variable is to be inserted
         */
        virtual void insertInputVariable(InputVariable* inputVariable, std::size_t index);
        /**
         * Gets the input variable at the given index
         * @param index is the given index
         * @return the input variable at the given index
         */
        virtual InputVariable* getInputVariable(std::size_t index) const;
        /**
         * Gets the input variable of the given name after iterating the input variables
         * @param name is the name of the input variable
         * @return input variable of the given name 
         * @throws fl::Exception if there is no variable with the given name
         */
        virtual InputVariable* getInputVariable(const std::string& name) const;
        /**
         * Removes the input variable at the given index (without deleting it) and
         * shifts the remaining input variables one position to the left
         * @param index is the given index
         * @return the input variable at the given index
         */
        virtual InputVariable* removeInputVariable(std::size_t index);
        /**
         * Removes the input variable of the given name (without deleting it) and
         * shifts the remaining input variables one position to the left
         * @param name is the name of the input variable
         * @return the input variable of the given name
         * @throws fl::Exception if there is no variable with the given name
         */
        virtual InputVariable* removeInputVariable(const std::string& name);
        /**
         * Indicates whether an input variable of the given name is in the input variables 
         * @param name is the name of the input variable
         * @return a boolean indicating whether an input variable of the given name 
         * is in the input variables
         */
        virtual bool hasInputVariable(const std::string& name) const;
        /**
         * Returns the number of input variables added to the engine
         * @return the number of input variables added to the engine
         */
        virtual std::size_t numberOfInputVariables() const;
        /**
         * Returns an immutable vector of input variables
         * @return an immutable vector of input variables
         */
        virtual const std::vector<InputVariable*>& inputVariables() const;
        /**
         * Sets the vector of input variables
         * @param inputVariables is the vector of input variables
         */
        virtual void setInputVariables(const std::vector<InputVariable*>& inputVariables);
        /**
         * Returns a mutable vector of input variables
         * @return a mutable vector of input variables
         */
        virtual std::vector<InputVariable*>& inputVariables();

        /**
         * Adds the output variable
         * @param outputVariable is the output variable
         */
        virtual void addOutputVariable(OutputVariable* outputVariable);
        /**
         * Sets the output variable at the given index 
         * @param outputVariable is the output variable to set
         * @param index is the index at which the output variable is to be stored
         * @return the output variable previously stored at the given index
         */
        virtual OutputVariable* setOutputVariable(OutputVariable* outputVariable, std::size_t index);
        /**
         * Inserts the output variable at the given index, shifting other variables one position to the right
         * @param outputVariable is the output variable to insert
         * @param index is the index at which the output variable is to be inserted
         */
        virtual void insertOutputVariable(OutputVariable* outputVariable, std::size_t index);
        /**
         * Gets the output variable at the given index
         * @param index is the given index
         * @return the output variable at the given index
         */
        virtual OutputVariable* getOutputVariable(std::size_t index) const;
        /**
         * Gets the output variable of the given name after iterating the output variables
         * @param name is the name of the output variable
         * @return output variable of the given name 
         * @throws fl::Exception if there is no variable with the given name
         */
        virtual OutputVariable* getOutputVariable(const std::string& name) const;

        /**
         * Indicates whether an output variable of the given name is in the output variables 
         * @param name is the name of the output variable
         * @return a boolean indicating whether an output variable of the given name 
         * is in the output variables
         */
        virtual bool hasOutputVariable(const std::string& name) const;
        /**
         * Removes the output variable at the given index (without deleting it) and
         * shifts the remaining output variables one position to the left
         * @param index is the given index
         * @return the output variable at the given index
         */
        virtual OutputVariable* removeOutputVariable(std::size_t index);
        /**
         * Removes the output variable of the given name (without deleting it) and
         * shifts the remaining output variables one position to the left
         * @param name is the name of the output variable
         * @return the output variable of the given name
         * @throws fl::Exception if there is no variable with the given name
         */
        virtual OutputVariable* removeOutputVariable(const std::string& name);
        /**
         * Returns the number of output variables added to the engine
         * @return the number of output variables added to the engine
         */
        virtual std::size_t numberOfOutputVariables() const;
        /**
         * Returns an immutable vector of output variables
         * @return an immutable vector of output variables
         */
        virtual const std::vector<OutputVariable*>& outputVariables() const;
        /**
         * Sets the vector of output variables
         * @param outputVariables is the vector of output variables
         */
        virtual void setOutputVariables(const std::vector<OutputVariable*>& outputVariables);
        /**
         * Returns a mutable vector of output variables
         * @return a mutable vector of output variables
         */
        virtual std::vector<OutputVariable*>& outputVariables();

        /**
         * Adds the rule block
         * @param ruleBlock is the rule block
         */
        virtual void addRuleBlock(RuleBlock* ruleBlock);
        /**
         * Sets the rule block at the given index 
         * @param ruleBlock is the rule block to set
         * @param index is the index at which the rule block is to be stored
         * @return the rule block previously stored at the given index
         */
        virtual RuleBlock* setRuleBlock(RuleBlock* ruleBlock, std::size_t index);
        /**
         * Inserts the rule block at the given index, shifting other blocks one position to the right
         * @param ruleBlock is the rule block to insert
         * @param index is the index at which the rule block is to be inserted
         */
        virtual void insertRuleBlock(RuleBlock* ruleBlock, std::size_t index);
        /**
         * Gets the rule block at the given index
         * @param index is the given index
         * @return the rule block at the given index
         */
        virtual RuleBlock* getRuleBlock(std::size_t index) const;
        /**
         * Gets the rule block of the given name after iterating the rule blocks
         * @param name is the name of the rule block
         * @return rule block of the given name 
         * @throws fl::Exception if there is no block with the given name
         */
        virtual RuleBlock* getRuleBlock(const std::string& name) const;
        /**
         * Indicates whether an rule block of the given name is in the rule blocks 
         * @param name is the name of the rule block
         * @return a boolean indicating whether an rule block of the given name 
         * is in the rule blocks
         */
        virtual bool hasRuleBlock(const std::string& name) const;
        /**
         * Removes the rule block at the given index (without deleting it) and
         * shifts the remaining rule blocks one position to the left
         * @param index is the given index
         * @return the rule block at the given index
         */
        virtual RuleBlock* removeRuleBlock(std::size_t index);
        /**
         * Removes the rule block of the given name (without deleting it) and
         * shifts the remaining rule blocks one position to the left
         * @param name is the name of the rule block
         * @return the rule block of the given name
         * @throws fl::Exception if there is no block with the given name
         */
        virtual RuleBlock* removeRuleBlock(const std::string& name);
        /**
         * Returns the number of rule blocks added to the engine
         * @return the number of rule blocks added to the engine
         */
        virtual std::size_t numberOfRuleBlocks() const;
        /**
         * Returns an immutable vector of rule blocks
         * @return an immutable vector of rule blocks
         */
        virtual const std::vector<RuleBlock*>& ruleBlocks() const;
        /**
         * Sets the vector of rule blocks
         * @param ruleBlocks is the vector of rule blocks
         */
        virtual void setRuleBlocks(const std::vector<RuleBlock*>& ruleBlocks);
        /**
         * Returns a mutable vector of rule blocks
         * @return a mutable vector of rule blocks
         */
        virtual std::vector<RuleBlock*>& ruleBlocks();

    };

}
#endif /* FL_ENGINE_H */
