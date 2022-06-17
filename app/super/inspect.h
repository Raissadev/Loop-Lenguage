#ifndef INSPECT_H
#define INSPECT_H
#include "syntax.h"

typedef struct InspectStruct
{
} inspec_T;

inspec_T* ____construct();

syntax_T* inspect(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_def_variable(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_def_function(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_variable(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_function_call(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_string(inspec_T* visitor, syntax_T* node);

syntax_T* inspect_compose(inspec_T* visitor, syntax_T* node);

#endif