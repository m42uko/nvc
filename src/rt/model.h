//
//  Copyright (C) 2022-2025  Nick Gasson
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

#ifndef _RT_MODEL_H
#define _RT_MODEL_H

#include "prim.h"
#include "rt/rt.h"

typedef enum {
   WATCH_EVENT,
   WATCH_POSTPONED,
} watch_kind_t;

typedef enum {
   END_OF_INITIALISATION,
   START_OF_SIMULATION,
   START_OF_PROCESSES,
   END_OF_PROCESSES,
   START_OF_POSTPONED,
   LAST_KNOWN_DELTA_CYCLE,
   NEXT_TIME_STEP,
   END_TIME_STEP,
   NEXT_CYCLE,
   END_OF_SIMULATION,
} model_phase_t;

rt_model_t *model_new(jit_t *jit, cover_data_t *cover);
void model_free(rt_model_t *m);
void model_reset(rt_model_t *m);
void model_run(rt_model_t *m, uint64_t stop_time);
bool model_step(rt_model_t *m);
bool model_can_create_delta(rt_model_t *m);
int64_t model_now(rt_model_t *m, unsigned *deltas);
int64_t model_next_time(rt_model_t *m);
void model_stop(rt_model_t *m);
void model_interrupt(rt_model_t *m);
int model_exit_status(rt_model_t *m);

rt_watch_t *watch_new(rt_model_t *m, sig_event_fn_t fn, void *user,
                      watch_kind_t kind, unsigned slots);
void watch_free(rt_model_t *m, rt_watch_t *w);

void model_set_phase_cb(rt_model_t *m, model_phase_t phase, rt_event_fn_t fn,
                        void *user);
rt_watch_t *model_set_event_cb(rt_model_t *m, rt_signal_t *s, rt_watch_t *w);
void model_set_timeout_cb(rt_model_t *m, uint64_t when, rt_event_fn_t fn,
                          void *user);

void call_with_model(rt_model_t *m, void (*cb)(void *), void *arg);

rt_model_t *get_model(void);
rt_model_t *get_model_or_null(void);
rt_proc_t *get_active_proc(void);
rt_scope_t *get_active_scope(rt_model_t *m);
cover_data_t *get_coverage(rt_model_t *m);

rt_scope_t *find_scope(rt_model_t *m, tree_t container);
rt_scope_t *root_scope(rt_model_t *m);
rt_scope_t *child_scope(rt_scope_t *scope, tree_t decl);
rt_scope_t *child_scope_at(rt_scope_t *scope, int index);
rt_signal_t *find_signal(rt_scope_t *scope, tree_t decl);
rt_proc_t *find_proc(rt_scope_t *scope, tree_t proc);
bool is_signal_scope(rt_scope_t *scope);
rt_scope_t *create_scope(rt_model_t *m, tree_t block, rt_scope_t *parent);

void get_instance_name(rt_scope_t *s, text_buf_t *tb);
void get_path_name(rt_scope_t *s, text_buf_t *tb);

const void *signal_value(rt_signal_t *s);
const void *signal_last_value(rt_signal_t *s);
uint8_t signal_size(rt_signal_t *s);
uint32_t signal_width(rt_signal_t *s);
size_t signal_expand(rt_signal_t *s, uint64_t *buf, size_t max);
void force_signal(rt_model_t *m, rt_signal_t *s, const void *values,
                  int offset, size_t count);
void release_signal(rt_model_t *m, rt_signal_t *s, int offset, size_t count);
void deposit_signal(rt_model_t *m, rt_signal_t *s, const void *values,
                    int offset, size_t count);
void sched_deposit(rt_model_t *m, rt_signal_t *s, const void *values,
                   int offset, size_t count, int64_t after, bool nonblock);
rt_watch_t *find_watch(rt_nexus_t *n, sig_event_fn_t fn);
void get_forcing_value(rt_signal_t *s, uint8_t *value);

#endif  // _RT_MODEL_H
