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

#ifndef FL_EXPORTER_H
#define FL_EXPORTER_H

#include "fl/fuzzylite.h"

#include <string>

namespace fl {
    class Engine;

    /**
      Base class for all exporters
      @author Juan Rada-Vilela, Ph.D.
      @see Importer
      @since 4.0
     */
    class FL_API Exporter {
    public:

        Exporter();
        virtual ~Exporter();
        FL_DEFAULT_COPY_AND_MOVE(Exporter)

        /**
          Returns a string representation of the engine
          @param engine is the engine to export
          @return a string representation of the engine
         */
        virtual std::string toString(const Engine* engine) const = 0;
        /**
          Stores the string representation of the engine into the specified file
          @param path is the full path of the file to export the engine to
          @param engine is the engine to export
         */
        virtual void toFile(const std::string& path, const Engine* engine) const;

        /**
          Returns the name of the exporter
          @return the name of the exporter
         */
        virtual std::string name() const = 0;

        /**
          Creates a clone of the exporter
          @return a clone of the exporter
         */
        virtual Exporter* clone() const = 0;
    };

}

#endif  /* FL_EXPORTER_H */
