// Copyright (c) 2018, 2019 Marko Mahnič
// License: MPL2. See LICENSE in the root of the project.

#pragma once

#include "values.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace argparse {

class OptionGroup;

class Option
{
   friend class OptionFactory;

public:
   enum Kind { singleValue, vectorValue };

private:
   std::unique_ptr<Value> mpValue;
   AssignAction mAssignAction;
   AssignDefaultAction mAssignDefaultAction;
   std::string mShortName;
   std::string mLongName;
   std::string mMetavar;
   std::string mHelp;
   std::string mFlagValue = "1";
   std::vector<std::string> mChoices;
   std::shared_ptr<OptionGroup> mpGroup;
   int mMinArgs = 0;
   int mMaxArgs = 0;
   bool mIsRequired = false;
   bool mIsVectorValue = false;

public:
   void setShortName( std::string_view name );
   void setLongName( std::string_view name );
   void setMetavar( std::string_view varname );
   void setHelp( std::string_view help );
   void setNArgs( int count );
   void setMinArgs( int count );
   void setMaxArgs( int count );
   void setRequired( bool isRequired = true );
   void setFlagValue( std::string_view value );
   void setChoices( const std::vector<std::string>& choices );
   void setAction( AssignAction action );
   void setAssignDefaultAction( AssignDefaultAction action );
   void setGroup( const std::shared_ptr<OptionGroup>& pGroup );
   bool isRequired() const;
   const std::string& getName() const;
   const std::string& getShortName() const;
   const std::string& getLongName() const;
   std::string getHelpName() const;
   bool hasName( std::string_view name ) const;
   const std::string& getRawHelp() const;
   std::string getMetavar() const;
   void setValue( std::string_view value, Environment& env );
   void assignDefault();
   bool hasDefault() const;
   void resetValue();
   void onOptionStarted();
   bool acceptsAnyArguments() const;
   bool willAcceptArgument() const;
   bool needsMoreArguments() const;
   bool hasVectorValue() const;

   /**
    * @returns true if the value was assigned through any option that shares
    * this option's value.
    */
   bool wasAssigned() const;

   bool wasAssignedThroughThisOption() const;
   const std::string& getFlagValue() const;
   std::tuple<int, int> getArgumentCounts() const;
   std::shared_ptr<OptionGroup> getGroup() const;

   ValueId getValueId() const;
   TargetId getTargetId() const;

private:
   Option( std::unique_ptr<Value>&& pValue, Kind kind )
      : mpValue( std::move( pValue ) )
      , mIsVectorValue( kind == Option::vectorValue )
   {}
};

}   // namespace argparse
