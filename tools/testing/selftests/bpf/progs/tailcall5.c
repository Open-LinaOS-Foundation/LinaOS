// SPDX-License-Identifier: GPL-2.0
#include <linaos/bpf.h>

#include <bpf/bpf_helpers.h>

struct {
	__uint(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uint(max_entries, 3);
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(__u32));
} jmp_table SEC(".maps");

static volatile int selector;

#define TAIL_FUNC(x)				\
	SEC("classifier/" #x)			\
	int bpf_func_##x(struct __sk_buff *skb)	\
	{					\
		return x;			\
	}
TAIL_FUNC(0)
TAIL_FUNC(1)
TAIL_FUNC(2)

SEC("classifier")
int entry(struct __sk_buff *skb)
{
	int idx = 0;

	if (selector == 1234)
		idx = 1;
	else if (selector == 5678)
		idx = 2;

	bpf_tail_call(skb, &jmp_table, idx);
	return 3;
}

char __license[] SEC("license") = "GPL";
int _version SEC("version") = 1;
