#undef TRACE_SYSTEM
#define TRACE_SYSTEM sample

#if !defined(_TRACE_MODULE_H_) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MODULE_H_

#include <linux/tracepoint.h>

#ifndef _TRACE_EVENT_SAMPLE_HELPER_FUCNTIONS
#define _TRACE_EVENT_SAMPLE_HELPER_FUCNTIONS

static inline int __length_of(const int *list)
{
	int i;

	if (!list)
		return 0;
	for (i = 0; list[i]; i++)
		;
	return i;
}

enum {
	TRACE_SAMPLE_FOO = 2,
	TRACE_SAMPLE_BAR = 4,
	TRACE_SAMPLE_ZOO = 8,
};
#endif

TRACE_EVENT(sameer_shaik,
	    
	    TP_PROTO(const char *string, int bar, const int *array, const char *random_str),
	    TP_ARGS(string, bar, array, random_str),
	    TP_STRUCT__entry(
			     __array(char, string , 10)
			     __field(int, bar)
			     __dynamic_array(int, list, __length_of(array)) 
			     __string(str, random_str)
			     /* __bitmask(cpus, num_possible_cpus()) */
			     ),
	    TP_fast_assign(
			   memcpy(__entry->string, string, 10);
			   __entry->bar = bar;
			   memcpy(__get_dynamic_array(list), array, __length_of(array) * sizeof(int));
			   __assign_str(str, random_str);
			   /* __assign_bitmask(cpus, cpumask_bits(mask), num_possible_cpus()); */
			   ),
	    TP_printk("sameer %s %d %s %s", __entry->string, __entry->bar, __print_array(__get_dynamic_array(list), __get_dynamic_array_len(list)/ sizeof(int), sizeof(int)), __get_str(str))
		      /* __print_symbolic(__entry->bar, */
		      /* 		       { 0, "zero"}, */
		      /* 		       { TRACE_SAMPLE_FOO, "TWO" }, */
		      /* 		       { TRACE_SAMPLE_BAR, "FOUR" }, */
		      /* 		       { TRACE_SAMPLE_ZOO, "EIGHT" }, */
		      /* 		       {10, "TEN" } */
		      /* 		       ), */
		      /* __print_flags(__entry->bar, "|", */
		      /* 		    { 1, "BIT1" }, */
		      /* 		    { 2, "BIT2" }, */
		      /* 		    { 4, "BIT3" }, */
		      /* 		    { 8, "BIT4" } */
		      /* 		    ), */
		      /* __print_array(__get_dynamic_array(list), */
		      /* 		    __get_dynamic_array_len(list) / sizeof(int), */
		      /* 		    sizeof(int)), */
		      /* __get_str(str), __get_bitmask(cpus)) */
	    );
#endif
#undef TRACE_INCLUDE_PATH
#undef TRACE_INCLUDE_FILE

#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE trace_module

#include <trace/define_trace.h>

