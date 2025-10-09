//
//  Copyright (C) 2024-2025 Nick Gasson
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _VLOG_UTIL_H
#define _VLOG_UTIL_H

#include "prim.h"

bool vlog_is_net(vlog_node_t v);
unsigned vlog_dimensions(vlog_node_t v);
bool vlog_get_const(vlog_node_t v, int64_t *value);
bool vlog_is_const(vlog_node_t v);
bool vlog_is_up(vlog_node_t v);
bool vlog_bounds(vlog_node_t v, int64_t *left, int64_t *right);
unsigned vlog_size(vlog_node_t v);
bool is_top_level(vlog_node_t v);
bool is_data_type(vlog_node_t v);
bool is_implicit_data_type(vlog_node_t v);
vlog_node_t vlog_longest_static_prefix(vlog_node_t v);
bool vlog_equal_node(vlog_node_t a, vlog_node_t b);
uint32_t vlog_hash_node(vlog_node_t v);
vlog_node_t vlog_get_type(vlog_node_t v);

#define CANNOT_HANDLE(v) do {                                           \
      fatal_at(vlog_loc(v), "cannot handle %s in %s" ,                  \
               vlog_kind_str(vlog_kind(v)), __FUNCTION__);              \
   } while (0)

#endif  // _VLOG_UTIL_H
