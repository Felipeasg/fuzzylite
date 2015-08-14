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

#ifndef FL_FLDEXPORTER_H
#define FL_FLDEXPORTER_H

#include "fl/imex/Exporter.h"

#include <vector>

namespace fl {
    class Engine;
    class InputVariable;
    class OutputVariable;

    /**
     * Exports an Engine to the FuzzyLite Dataset (FLD)
     * @author Juan Rada-Vilela, Ph.D.
     * @see FllExporter
     * @see Exporter
     * @since 4.0
     */
    class FL_API FldExporter : public Exporter {
    protected:
        std::string _separator;
        bool _exportHeaders;
        bool _exportInputValues;
        bool _exportOutputValues;
    public:
        explicit FldExporter(const std::string& separator = " ");
        virtual ~FldExporter() FL_IOVERRIDE;
        FL_DEFAULT_COPY_AND_MOVE(FldExporter)

        virtual std::string name() const FL_IOVERRIDE;

        /**
         * Sets the separator of the dataset columns
         * @param separator is the separator of the dataset columns
         */
        virtual void setSeparator(const std::string& separator);
        /**
         * Gets the separator of the dataset columns
         * @return the separator of the dataset columns
         */
        virtual std::string getSeparator() const;

        /**
         * Sets whether the header of the dataset is to be exported
         * @param exportHeaders is a boolean indicating whether the header of 
         * the dataset is to be exported
         */
        virtual void setExportHeader(bool exportHeaders);
        /**
         * Gets whether the header of the dataset is to be exported
         * @return a boolean indicating whether the header of 
         * the dataset is to be exported
         */
        virtual bool exportsHeader() const;

        /**
         * Sets whether the values of the input variables are to be exported
         * @param exportInputValues is a boolean indicating whether the values
         * of the input variables are to be exported
         */
        virtual void setExportInputValues(bool exportInputValues);
        /**
         * Gets whether the values of the input variables are to be exported
         * @return a boolean indicating whether the values
         * of the input variables are to be exported
         */
        virtual bool exportsInputValues() const;

        /**
         * Sets whether the values of the output variables are to be exported
         * @param exportOutputValues is a boolean indicating whether the values
         * of the output variables are to be exported
         */
        virtual void setExportOutputValues(bool exportOutputValues);
        /**
         * Gets whether the values of the output variables are to be exported
         * @return a boolean indicating whether the values
         * of the output variables are to be exported
         */
        virtual bool exportsOutputValues() const;

        /**
         * Gets the header of the dataset for the given engine
         * @param engine is the engine to be exported
         * @return the header of the dataset for the given engine
         */
        virtual std::string header(const Engine* engine) const;

        /**
         * Returns a FuzzyLite Dataset from the engine. Please consider that
         * the engine will be `const_cast`ed to achieve so; that is, despite 
         * being marked as `const`, the engine will be modified in order to compute 
         * the output values based on the input values.
         * @param engine is the engine to export
         * @return a FuzzyLite Dataset from the engine
         */
        virtual std::string toString(const Engine* engine) const FL_IOVERRIDE;
        /**
         * Returns a FuzzyLite Dataset from the engine.
         * 
         * @param engine is the engine to export
         * @param maximumNumberOfResults is the maximum number of results to export
         * @return a FuzzyLite Dataset from the engine
         */
        virtual std::string toString(Engine* engine, int maximumNumberOfResults) const;
        /**
         * Returns a FuzzyLite Dataset from the engine.
         * 
         * @param engine is the engine to export
         * @param inputData is a set of lines containing space-separated input values 
         * upon which the engine will be evaluated
         * @return a FuzzyLite Dataset from the engine
         */
        virtual std::string toString(Engine* engine, const std::string& inputData) const;

        
        using Exporter::toFile;
        /**
         * Saves the engine as a FuzzyLite Dataset into the specified file
         * @param path is the full path of the file
         * @param engine is the engine to export
         * @param maximumNumberOfResults is the maximum number of results to export
         */
        virtual void toFile(const std::string& path, Engine* engine, int maximumNumberOfResults) const;
        /**
         * Saves the engine as a FuzzyLite Dataset into the specified file
         * @param path is the full path of the file
         * @param engine is the engine to export
         * @param inputData is a set of lines containing space-separated input values 
         * upon which the engine will be evaluated
         */
        virtual void toFile(const std::string& path, Engine* engine, const std::string& inputData) const;

        /**
         * Parses the string into a vector of values unless the string starts with `#`
         * @param x is a space-separated set of values
         * @return a vector of values
         */
        virtual std::vector<scalar> parse(const std::string& x) const;

        /**
         * Writes the engine into the given writer
         * @param engine is the engine to export
         * @param writer is the output where the engine will be written to
         * @param maximumNumberOfResults is the maximum number of results to write
         */
        void write(Engine* engine, std::ostream& writer, int maximumNumberOfResults) const;
        /**
         * Writes the engine into the given writer
         * @param engine is the engine to export
         * @param writer is the output where the engine will be written to
         * @param reader is the reader of a set of lines containing space-separated input values
         */
        void write(Engine* engine, std::ostream& writer, std::istream& reader) const;
      /**
         * Writes the engine into the given writer
         * @param engine is the engine to export
         * @param writer is the output where the engine will be written to
         * @param inputValues is the vector of input values
         */
        void write(Engine* engine, std::ostream& writer, const std::vector<scalar>& inputValues) const;

        virtual FldExporter* clone() const FL_IOVERRIDE;
    };
}

#endif  /* FL_FLDEXPORTER_H */
