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

#ifndef FL_CONSOLE_H
#define FL_CONSOLE_H

#include "fl/fuzzylite.h"

#include <map>
#include <string>
#include <vector>

namespace fl {
    class Engine;

    /**
      A command-line tool to utilize the `fuzzylite` library
      @author Juan Rada-Vilela, Ph.D.
      @since 4.0
     */
    class FL_API Console {
    public:

        /**
          A command-line option given by key, value and description
         */
        struct Option {
            std::string key, value, description;

            explicit Option(const std::string& key = "", const std::string& value = "", const std::string& description = "") :
            key(key), value(value), description(description) {
            }
        };

        /**Keyword for input file*/
        static const std::string KW_INPUT_FILE;
        /**Keyword for input file format*/
        static const std::string KW_INPUT_FORMAT;
        /**Keyword for output file*/
        static const std::string KW_OUTPUT_FILE;
        /**Keyword for output file format*/
        static const std::string KW_OUTPUT_FORMAT;
        /**Keyword for built-in example*/
        static const std::string KW_EXAMPLE;
        /**Keyword for number of decimals*/
        static const std::string KW_DECIMALS;
        /**Keyword for file containing input data*/
        static const std::string KW_DATA_INPUT;
        /**Keyword for maximum number of results to evaluate the engine*/
        static const std::string KW_DATA_MAXIMUM;
        /**Keyword for exporting headers in FLD*/
        static const std::string KW_DATA_EXPORT_HEADER;
        /**Keyword for exporting input values in FLD*/
        static const std::string KW_DATA_EXPORT_INPUTS;

        /**
          Creates a new Mamdani Engine based on the SimpleDimmer example
          @return a new Mamdani Engine based on the SimpleDimmer example
         */
        static Engine* mamdani();
        /**
          Creates a new TakagiSugeno Engine based on the Approximation example of @f$sin(x)/x@f$
          @return a new TakagiSugeno Engine based on the Approximation example of @f$sin(x)/x@f$
         */
        static Engine* takagiSugeno();

    protected:
        static std::map<std::string, std::string> parse(int argc, char** argv);
        static void process(const std::map<std::string, std::string>& options);

        static void process(const std::string& input, std::ostream& writer,
                const std::string& inputFormat, const std::string& outputFormat,
                const std::map<std::string, std::string>& options);

        static int readCharacter();
        static void interactive(std::ostream& writer, Engine* engine);
        static std::string interactiveHelp();

        static void exportAllExamples(const std::string& from, const std::string& to);
        static void exportAllExamples(const std::string& from, const std::string& to, const std::string& path);
#ifdef FL_CPP11
        static void benchmarkExamples(const std::string& path, int runs);
#endif

    public:
        /**
          Returns a string representation of the usage of the command-line tool
          @return a string representation of the usage of the command-line tool
         */
        static std::string usage();
        /**
          Returns a vector of the options available from the command line
          @return a vector of the options available from the command line
         */
        static std::vector<Option> availableOptions();

        static int main(int argc, char** argv);
    };

}

#endif  /* FL_CONSOLE_H */
