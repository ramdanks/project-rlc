#ifndef TRUNCATE_H
#define TRUNCATE_H

#include "binding.h"

#define bind_string  lua_bind_fn_string
#define bind_number  lua_bind_fn_number
#define bind_integer lua_bind_fn_integer

typedef lua_bind_fn                 bind_fn;
typedef lua_bind_class_t            bind_class_t;
typedef lua_bind_vector_t           bind_vector_t;
typedef lua_bind_scalar_field_t     bind_scalar_field_t;
typedef lua_bind_vector_field_t     bind_vector_field_t;
typedef lua_bind_scalar_field_arg_t bind_scalar_field_arg_t;
typedef lua_bind_vector_field_arg_t bind_vector_field_arg_t;

#include "vector.h"

typedef lua_vector_t vector_t;

#endif