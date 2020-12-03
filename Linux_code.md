### task_struct



```cpp
struct task_struct {
	volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	void *stack;
	atomic_t usage;
	unsigned int flags;	/* per process flags, defined below */
	unsigned int ptrace;

	int lock_depth;		/* BKL lock depth */

#ifdef CONFIG_SMP
#ifdef __ARCH_WANT_UNLOCKED_CTXSW
	int oncpu;
#endif
#endif

	int prio, static_prio, normal_prio;
	unsigned int rt_priority;
	const struct sched_class *sched_class;
	struct sched_entity se;
	struct sched_rt_entity rt;

#ifdef CONFIG_PREEMPT_NOTIFIERS
	/* list of struct preempt_notifier: */
	struct hlist_head preempt_notifiers;
#endif

	/*
	 * fpu_counter contains the number of consecutive context switches
	 * that the FPU is used. If this is over a threshold, the lazy fpu
	 * saving becomes unlazy to save the trap. This is an unsigned char
	 * so that after 256 times the counter wraps and the behavior turns
	 * lazy again; this to deal with bursty apps that only use FPU for
	 * a short time
	 */
	unsigned char fpu_counter;
#ifdef CONFIG_BLK_DEV_IO_TRACE
	unsigned int btrace_seq;
#endif

	unsigned int policy;
	cpumask_t cpus_allowed;

#ifdef CONFIG_PREEMPT_RCU
	int rcu_read_lock_nesting;
	char rcu_read_unlock_special;
	struct list_head rcu_node_entry;
#endif /* #ifdef CONFIG_PREEMPT_RCU */
#ifdef CONFIG_TREE_PREEMPT_RCU
	struct rcu_node *rcu_blocked_node;
#endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */
#ifdef CONFIG_RCU_BOOST
	struct rt_mutex *rcu_boost_mutex;
#endif /* #ifdef CONFIG_RCU_BOOST */

#if defined(CONFIG_SCHEDSTATS) || defined(CONFIG_TASK_DELAY_ACCT)
	struct sched_info sched_info;
#endif

	struct list_head tasks;
#ifdef CONFIG_SMP
	struct plist_node pushable_tasks;
#endif

	struct mm_struct *mm, *active_mm;
#ifdef CONFIG_COMPAT_BRK
	unsigned brk_randomized:1;
#endif
#if defined(SPLIT_RSS_COUNTING)
	struct task_rss_stat	rss_stat;
#endif
/* task state */
	int exit_state;
	int exit_code, exit_signal;
	int pdeath_signal;  /*  The signal sent when the parent dies  */
	/* ??? */
	unsigned int personality;
	unsigned did_exec:1;
	unsigned in_execve:1;	/* Tell the LSMs that the process is doing an
				 * execve */
	unsigned in_iowait:1;


	/* Revert to default priority/policy when forking */
	unsigned sched_reset_on_fork:1;

	pid_t pid;
	pid_t tgid;

#ifdef CONFIG_CC_STACKPROTECTOR
	/* Canary value for the -fstack-protector gcc feature */
	unsigned long stack_canary;
#endif

	/* 
	 * pointers to (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with 
	 * p->real_parent->pid)
	 */
	struct task_struct *real_parent; /* real parent process */
	struct task_struct *parent; /* recipient of SIGCHLD, wait4() reports */
	/*
	 * children/sibling forms the list of my natural children
	 */
	struct list_head children;	/* list of my children */
	struct list_head sibling;	/* linkage in my parent's children list */
	struct task_struct *group_leader;	/* threadgroup leader */

	/*
	 * ptraced is the list of tasks this task is using ptrace on.
	 * This includes both natural children and PTRACE_ATTACH targets.
	 * p->ptrace_entry is p's link on the p->parent->ptraced list.
	 */
	struct list_head ptraced;
	struct list_head ptrace_entry;

	/* PID/PID hash table linkage. */
	struct pid_link pids[PIDTYPE_MAX];
	struct list_head thread_group;

	struct completion *vfork_done;		/* for vfork() */
	int __user *set_child_tid;		/* CLONE_CHILD_SETTID */
	int __user *clear_child_tid;		/* CLONE_CHILD_CLEARTID */

	cputime_t utime, stime, utimescaled, stimescaled;
	cputime_t gtime;
#ifndef CONFIG_VIRT_CPU_ACCOUNTING
	cputime_t prev_utime, prev_stime;
#endif
	unsigned long nvcsw, nivcsw; /* context switch counts */
	struct timespec start_time; 		/* monotonic time */
	struct timespec real_start_time;	/* boot based time */
/* mm fault and swap info: this can arguably be seen as either mm-specific or thread-specific */
	unsigned long min_flt, maj_flt;

	struct task_cputime cputime_expires;
	struct list_head cpu_timers[3];

/* process credentials */
	const struct cred __rcu *real_cred; /* objective and real subjective task
					 * credentials (COW) */
	const struct cred __rcu *cred;	/* effective (overridable) subjective task
					 * credentials (COW) */
	struct cred *replacement_session_keyring; /* for KEYCTL_SESSION_TO_PARENT */

	char comm[TASK_COMM_LEN]; /* executable name excluding path
				     - access with [gs]et_task_comm (which lock
				       it with task_lock())
				     - initialized normally by setup_new_exec */
/* file system info */
	int link_count, total_link_count;
#ifdef CONFIG_SYSVIPC
/* ipc stuff */
	struct sysv_sem sysvsem;
#endif
#ifdef CONFIG_DETECT_HUNG_TASK
/* hung task detection */
	unsigned long last_switch_count;
#endif
/* CPU-specific state of this task */
	struct thread_struct thread;
/* filesystem information */
	struct fs_struct *fs;
/* open file information */
	struct files_struct *files;
/* namespaces */
	struct nsproxy *nsproxy;
/* signal handlers */
	struct signal_struct *signal;
	struct sighand_struct *sighand;

	sigset_t blocked, real_blocked;
	sigset_t saved_sigmask;	/* restored if set_restore_sigmask() was used */
	struct sigpending pending;

	unsigned long sas_ss_sp;
	size_t sas_ss_size;
	int (*notifier)(void *priv);
	void *notifier_data;
	sigset_t *notifier_mask;
	struct audit_context *audit_context;
#ifdef CONFIG_AUDITSYSCALL
	uid_t loginuid;
	unsigned int sessionid;
#endif
	seccomp_t seccomp;

/* Thread group tracking */
   	u32 parent_exec_id;
   	u32 self_exec_id;
/* Protection of (de-)allocation: mm, files, fs, tty, keyrings, mems_allowed,
 * mempolicy */
	spinlock_t alloc_lock;

#ifdef CONFIG_GENERIC_HARDIRQS
	/* IRQ handler threads */
	struct irqaction *irqaction;
#endif

	/* Protection of the PI data structures: */
	raw_spinlock_t pi_lock;

#ifdef CONFIG_RT_MUTEXES
	/* PI waiters blocked on a rt_mutex held by this task */
	struct plist_head pi_waiters;
	/* Deadlock detection and priority inheritance handling */
	struct rt_mutex_waiter *pi_blocked_on;
#endif

#ifdef CONFIG_DEBUG_MUTEXES
	/* mutex deadlock detection */
	struct mutex_waiter *blocked_on;
#endif
#ifdef CONFIG_TRACE_IRQFLAGS
	unsigned int irq_events;
	unsigned long hardirq_enable_ip;
	unsigned long hardirq_disable_ip;
	unsigned int hardirq_enable_event;
	unsigned int hardirq_disable_event;
	int hardirqs_enabled;
	int hardirq_context;
	unsigned long softirq_disable_ip;
	unsigned long softirq_enable_ip;
	unsigned int softirq_disable_event;
	unsigned int softirq_enable_event;
	int softirqs_enabled;
	int softirq_context;
#endif
#ifdef CONFIG_LOCKDEP
# define MAX_LOCK_DEPTH 48UL
	u64 curr_chain_key;
	int lockdep_depth;
	unsigned int lockdep_recursion;
	struct held_lock held_locks[MAX_LOCK_DEPTH];
	gfp_t lockdep_reclaim_gfp;
#endif

/* journalling filesystem info */
	void *journal_info;

/* stacked block device info */
	struct bio_list *bio_list;

#ifdef CONFIG_BLOCK
/* stack plugging */
	struct blk_plug *plug;
#endif

/* VM state */
	struct reclaim_state *reclaim_state;

	struct backing_dev_info *backing_dev_info;

	struct io_context *io_context;

	unsigned long ptrace_message;
	siginfo_t *last_siginfo; /* For ptrace use.  */
	struct task_io_accounting ioac;
#if defined(CONFIG_TASK_XACCT)
	u64 acct_rss_mem1;	/* accumulated rss usage */
	u64 acct_vm_mem1;	/* accumulated virtual memory usage */
	cputime_t acct_timexpd;	/* stime + utime since last update */
#endif
#ifdef CONFIG_CPUSETS
	nodemask_t mems_allowed;	/* Protected by alloc_lock */
	int mems_allowed_change_disable;
	int cpuset_mem_spread_rotor;
	int cpuset_slab_spread_rotor;
#endif
#ifdef CONFIG_CGROUPS
	/* Control Group info protected by css_set_lock */
	struct css_set __rcu *cgroups;
	/* cg_list protected by css_set_lock and tsk->alloc_lock */
	struct list_head cg_list;
#endif
#ifdef CONFIG_FUTEX
	struct robust_list_head __user *robust_list;
#ifdef CONFIG_COMPAT
	struct compat_robust_list_head __user *compat_robust_list;
#endif
	struct list_head pi_state_list;
	struct futex_pi_state *pi_state_cache;
#endif
#ifdef CONFIG_PERF_EVENTS
	struct perf_event_context *perf_event_ctxp[perf_nr_task_contexts];
	struct mutex perf_event_mutex;
	struct list_head perf_event_list;
#endif
#ifdef CONFIG_NUMA
	struct mempolicy *mempolicy;	/* Protected by alloc_lock */
	short il_next;
	short pref_node_fork;
#endif
	atomic_t fs_excl;	/* holding fs exclusive resources */
	struct rcu_head rcu;

	/*
	 * cache last used pipe for splice
	 */
	struct pipe_inode_info *splice_pipe;
#ifdef	CONFIG_TASK_DELAY_ACCT
	struct task_delay_info *delays;
#endif
#ifdef CONFIG_FAULT_INJECTION
	int make_it_fail;
#endif
	struct prop_local_single dirties;
#ifdef CONFIG_LATENCYTOP
	int latency_record_count;
	struct latency_record latency_record[LT_SAVECOUNT];
#endif
	/*
	 * time slack values; these are used to round up poll() and
	 * select() etc timeout values. These are in nanoseconds.
	 */
	unsigned long timer_slack_ns;
	unsigned long default_timer_slack_ns;

	struct list_head	*scm_work_list;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	/* Index of current stored address in ret_stack */
	int curr_ret_stack;
	/* Stack of return addresses for return function tracing */
	struct ftrace_ret_stack	*ret_stack;
	/* time stamp for last schedule */
	unsigned long long ftrace_timestamp;
	/*
	 * Number of functions that haven't been traced
	 * because of depth overrun.
	 */
	atomic_t trace_overrun;
	/* Pause for the tracing */
	atomic_t tracing_graph_pause;
#endif
#ifdef CONFIG_TRACING
	/* state flags for use by tracers */
	unsigned long trace;
	/* bitmask of trace recursion */
	unsigned long trace_recursion;
#endif /* CONFIG_TRACING */
#ifdef CONFIG_CGROUP_MEM_RES_CTLR /* memcg uses this to do batch job */
	struct memcg_batch_info {
		int do_batch;	/* incremented when batch uncharge started */
		struct mem_cgroup *memcg; /* target memcg of uncharge */
		unsigned long nr_pages;	/* uncharged usage */
		unsigned long memsw_nr_pages; /* uncharged mem+swap usage */
	} memcg_batch;
#endif
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	atomic_t ptrace_bp_refcnt;
#endif
};
```

### thread_info

为了快速获得task_struct指针。

由于x86寄存器比较珍贵

x86的thread_info会在栈的尾端创建，这是为了通过计算偏移量间接的寻找task_struct结构。

在x86上，current把栈指针的后13个有效位品笔调，用来计算thread_info的偏移量，该操作是由current_thred_info()函数来完成的，汇编代码如下：

```asm
movl $-8192, %eax
andl %esp, %eax
```

这里假设栈的大小为8K，当4K栈启用时就要用4096，而不是8192

最后，current在从thread_info的task域中提取并返回task_struct的地址：

`current_thread_info()->task;`

对比PowerPC，task_struct保存在一个寄存器中，也就是说在PPC上，current宏只需要把r2寄存器的值返回就行了。和x86不同，PPC有足够的寄存器，由于访问进程描述符是一个重要的频繁操作，所以PPC的内核开发者觉得完全有必要为此使用一个专门的寄存器。

```cpp
struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	__u32			flags;		/* low level flags */
	__u32			status;		/* thread synchronous flags */
	__u32			cpu;		/* current CPU */
	int			preempt_count;	/* 0 => preemptable,
						   <0 => BUG */
	mm_segment_t		addr_limit;
	struct restart_block    restart_block;
	void __user		*sysenter_return;
#ifdef CONFIG_X86_32
	unsigned long           previous_esp;   /* ESP of the previous stack in
						   case of nested (IRQ) stacks
						*/
	__u8			supervisor_stack[0];
#endif
	int			uaccess_err;
};
```



### sched.c  (kernel/sched.c)

```cpp
/*
 * This is the priority-queue data structure of the RT scheduling class:
 */
struct rt_prio_array {
	DECLARE_BITMAP(bitmap, MAX_RT_PRIO+1); /* include 1 bit for delimiter */
	struct list_head queue[MAX_RT_PRIO];
};

struct rt_bandwidth {
	/* nests inside the rq lock: */
	raw_spinlock_t		rt_runtime_lock;
	ktime_t			rt_period;
	u64			rt_runtime;
	struct hrtimer		rt_period_timer;
};

static struct rt_bandwidth def_rt_bandwidth;

static int do_sched_rt_period_timer(struct rt_bandwidth *rt_b, int overrun);

static enum hrtimer_restart sched_rt_period_timer(struct hrtimer *timer)
{
	struct rt_bandwidth *rt_b =
		container_of(timer, struct rt_bandwidth, rt_period_timer);
	ktime_t now;
	int overrun;
	int idle = 0;

	for (;;) {
		now = hrtimer_cb_get_time(timer);
		overrun = hrtimer_forward(timer, now, rt_b->rt_period);

		if (!overrun)
			break;

		idle = do_sched_rt_period_timer(rt_b, overrun);
	}

	return idle ? HRTIMER_NORESTART : HRTIMER_RESTART;
}
```

```cpp

struct cfs_rq;

static LIST_HEAD(task_groups);

/* task group related information */
struct task_group {
	struct cgroup_subsys_state css;

#ifdef CONFIG_FAIR_GROUP_SCHED
	/* schedulable entities of this group on each cpu */
	struct sched_entity **se;
	/* runqueue "owned" by this group on each cpu */
	struct cfs_rq **cfs_rq;
	unsigned long shares;

	atomic_t load_weight;
#endif

#ifdef CONFIG_RT_GROUP_SCHED
	struct sched_rt_entity **rt_se;
	struct rt_rq **rt_rq;

	struct rt_bandwidth rt_bandwidth;
#endif

	struct rcu_head rcu;
	struct list_head list;

	struct task_group *parent;
	struct list_head siblings;
	struct list_head children;

#ifdef CONFIG_SCHED_AUTOGROUP
	struct autogroup *autogroup;
#endif
};
```

#### csf_rq

```cpp
/* CFS-related fields in a runqueue */
struct cfs_rq {
	struct load_weight load;
	unsigned long nr_running;

	u64 exec_clock;
	u64 min_vruntime;

	struct rb_root tasks_timeline;
	struct rb_node *rb_leftmost;

	struct list_head tasks;
	struct list_head *balance_iterator;

	/*
	 * 'curr' points to currently running entity on this cfs_rq.
	 * It is set to NULL otherwise (i.e when none are currently running).
	 */
	struct sched_entity *curr, *next, *last, *skip;

	unsigned int nr_spread_over;

#ifdef CONFIG_FAIR_GROUP_SCHED
	struct rq *rq;	/* cpu runqueue to which this cfs_rq is attached */

	/*
	 * leaf cfs_rqs are those that hold tasks (lowest schedulable entity in
	 * a hierarchy). Non-leaf lrqs hold other higher schedulable entities
	 * (like users, containers etc.)
	 *
	 * leaf_cfs_rq_list ties together list of leaf cfs_rq's in a cpu. This
	 * list is used during load balance.
	 */
	int on_list;
	struct list_head leaf_cfs_rq_list;
	struct task_group *tg;	/* group that "owns" this runqueue */

#ifdef CONFIG_SMP
	/*
	 * the part of load.weight contributed by tasks
	 */
	unsigned long task_weight;

	/*
	 *   h_load = weight * f(tg)
	 *
	 * Where f(tg) is the recursive weight fraction assigned to
	 * this group.
	 */
	unsigned long h_load;

	/*
	 * Maintaining per-cpu shares distribution for group scheduling
	 *
	 * load_stamp is the last time we updated the load average
	 * load_last is the last time we updated the load average and saw load
	 * load_unacc_exec_time is currently unaccounted execution time
	 */
	u64 load_avg;
	u64 load_period;
	u64 load_stamp, load_last, load_unacc_exec_time;

	unsigned long load_contribution;
#endif
#endif
};
```

#### rt_rq

```cpp
/* Real-Time classes' related field in a runqueue: */
struct rt_rq {
	struct rt_prio_array active;
	unsigned long rt_nr_running;
#if defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED
	struct {
		int curr; /* highest queued rt task prio */
#ifdef CONFIG_SMP
		int next; /* next highest */
#endif
	} highest_prio;
#endif
#ifdef CONFIG_SMP
	unsigned long rt_nr_migratory;
	unsigned long rt_nr_total;
	int overloaded;
	struct plist_head pushable_tasks;
#endif
	int rt_throttled;
	u64 rt_time;
	u64 rt_runtime;
	/* Nests inside the rq lock: */
	raw_spinlock_t rt_runtime_lock;

#ifdef CONFIG_RT_GROUP_SCHED
	unsigned long rt_nr_boosted;

	struct rq *rq;
	struct list_head leaf_rt_rq_list;
	struct task_group *tg;
#endif
};
```

#### rq

```cpp
/*
 * This is the main, per-CPU runqueue data structure.
 *
 * Locking rule: those places that want to lock multiple runqueues
 * (such as the load balancing or the thread migration code), lock
 * acquire operations must be ordered by ascending &runqueue.
 */
struct rq {
	/* runqueue lock: */
	raw_spinlock_t lock;

	/*
	 * nr_running and cpu_load should be in the same cacheline because
	 * remote CPUs use both these fields when doing load calculation.
	 */
	unsigned long nr_running;
	#define CPU_LOAD_IDX_MAX 5
	unsigned long cpu_load[CPU_LOAD_IDX_MAX];
	unsigned long last_load_update_tick;
#ifdef CONFIG_NO_HZ
	u64 nohz_stamp;
	unsigned char nohz_balance_kick;
#endif
	unsigned int skip_clock_update;

	/* capture load from *all* tasks on this cpu: */
	struct load_weight load;
	unsigned long nr_load_updates;
	u64 nr_switches;

	struct cfs_rq cfs;
	struct rt_rq rt;

#ifdef CONFIG_FAIR_GROUP_SCHED
	/* list of leaf cfs_rq on this cpu: */
	struct list_head leaf_cfs_rq_list;
#endif
#ifdef CONFIG_RT_GROUP_SCHED
	struct list_head leaf_rt_rq_list;
#endif

	/*
	 * This is part of a global counter where only the total sum
	 * over all CPUs matters. A task can increase this counter on
	 * one CPU and if it got migrated afterwards it may decrease
	 * it on another CPU. Always updated under the runqueue lock:
	 */
	unsigned long nr_uninterruptible;

	struct task_struct *curr, *idle, *stop;
	unsigned long next_balance;
	struct mm_struct *prev_mm;

	u64 clock;
	u64 clock_task;

	atomic_t nr_iowait;

#ifdef CONFIG_SMP
	struct root_domain *rd;
	struct sched_domain *sd;

	unsigned long cpu_power;

	unsigned char idle_at_tick;
	/* For active balancing */
	int post_schedule;
	int active_balance;
	int push_cpu;
	struct cpu_stop_work active_balance_work;
	/* cpu of this runqueue: */
	int cpu;
	int online;

	unsigned long avg_load_per_task;

	u64 rt_avg;
	u64 age_stamp;
	u64 idle_stamp;
	u64 avg_idle;
#endif

#ifdef CONFIG_IRQ_TIME_ACCOUNTING
	u64 prev_irq_time;
#endif

	/* calc_load related fields */
	unsigned long calc_load_update;
	long calc_load_active;

#ifdef CONFIG_SCHED_HRTICK
#ifdef CONFIG_SMP
	int hrtick_csd_pending;
	struct call_single_data hrtick_csd;
#endif
	struct hrtimer hrtick_timer;
#endif

#ifdef CONFIG_SCHEDSTATS
	/* latency stats */
	struct sched_info rq_sched_info;
	unsigned long long rq_cpu_time;
	/* could above be rq->cfs_rq.exec_clock + rq->rt_rq.rt_runtime ? */

	/* sys_sched_yield() stats */
	unsigned int yld_count;

	/* schedule() stats */
	unsigned int sched_switch;
	unsigned int sched_count;
	unsigned int sched_goidle;

	/* try_to_wake_up() stats */
	unsigned int ttwu_count;
	unsigned int ttwu_local;
#endif
};
```

### CFS(kernel/sched_fair.c)

CFS的出发点基于一个简单的理念：进程调度的效果应如同系统具备一个理想中的完美多任务处理器。在这种系统中，每个进程将能获得1/n的处理器时间——n是指可运行进程的数量。同时，我们可以调度给它们无限小的时间周期，所以在任何可测量周期内，我们给予n个程序中每个进程同样多的时间。举例来说，假如我们有两个运行进程，那么在标准Unix调度模型中，我们先运行其中一个5ms，再运行另一个5ms。但它们任何一个运行时都将抢占100%的处理器，而在理想情况下，完美的多任务处理器模型应该是这样的：我们能在10ms内同时运行两个进程，它们各自使用处理器一半的能力。

然而要考虑调度代价、缓存等。

CFS的做法是允许每个进程运行一段时间、循环轮转、选择运行最少的进程作为下一个运行进程，从而不再采用分配给每个进程时间片的做法了，CFS在所有可运行进程总数基础上计算出一个进程应该运行多久，而不是依靠nice值来计算时间片。nice值在CFS中被作为进程获得的处理器运行比的权重：越高的nice值（越低的优先级）进程获得更低的处理器使用权重，这是相对默认nice值进程的进程而言的。相反，更低nice值（越高的优先级）的进程获得更高的处理器使用权重。

CFS引入每个进程获得的时间片底线，这个底线称为最小力度。默认值是1ms。



假如nice值为0和5，5的进程权重是默认（0）的1/3 ，那么假设20ms，它们分别获得15ms、5ms，如果权重为10 和 15？ 还是15ms、5ms！绝对nice不再影响调度决策，只有相对值才会影响处理器时间的分配比例。

CFS中nice值对于时间片的作用不再是算数加权，而是几何加权。

### 1.时间记账

#### 1.调度器实体结构(/include/linux/sched.h)

CFS不再有时间片的概念，但它也要维护每个进程的时间记账。

```cpp
struct sched_entity {
	struct load_weight	load;		/* for load-balancing */
	struct rb_node		run_node;
	struct list_head	group_node;
	unsigned int		on_rq;

	u64			exec_start;
	u64			sum_exec_runtime;
	u64			vruntime;
	u64			prev_sum_exec_runtime;

	u64			nr_migrations;

#ifdef CONFIG_SCHEDSTATS
	struct sched_statistics statistics;
#endif

#ifdef CONFIG_FAIR_GROUP_SCHED
	struct sched_entity	*parent;
	/* rq on which this entity is (to be) queued: */
	struct cfs_rq		*cfs_rq;
	/* rq "owned" by this entity/group: */
	struct cfs_rq		*my_q;
#endif
};
```

#### 2.虚拟实时(/kernel/sched_fair.c)

vruntime变量存放进程的虚拟运行时间，该运行时间的计算是经过了所有可运行进程总数的标准化。虚拟时间是以ns为单位的，所以vruntime和定时器节拍不再相关。

```cpp
/*
 * Update the current task's runtime statistics. Skip current tasks that
 * are not in our scheduling class.
 */
static inline void
__update_curr(struct cfs_rq *cfs_rq, struct sched_entity *curr,
	      unsigned long delta_exec)
{
	unsigned long delta_exec_weighted;

	schedstat_set(curr->statistics.exec_max,
		      max((u64)delta_exec, curr->statistics.exec_max));

	curr->sum_exec_runtime += delta_exec;
	schedstat_add(cfs_rq, exec_clock, delta_exec);
	delta_exec_weighted = calc_delta_fair(delta_exec, curr);

	curr->vruntime += delta_exec_weighted;
	update_min_vruntime(cfs_rq);

#if defined CONFIG_SMP && defined CONFIG_FAIR_GROUP_SCHED
	cfs_rq->load_unacc_exec_time += delta_exec;
#endif
}

static void update_curr(struct cfs_rq *cfs_rq)
{
	struct sched_entity *curr = cfs_rq->curr;
	u64 now = rq_of(cfs_rq)->clock_task;
	unsigned long delta_exec;

	if (unlikely(!curr))
		return;

	/*
	 * Get the amount of time the current task was running
	 * since the last time we changed load (this cannot
	 * overflow on 32 bits):
	 */
	delta_exec = (unsigned long)(now - curr->exec_start);
	if (!delta_exec)
		return;

	__update_curr(cfs_rq, curr, delta_exec);
	curr->exec_start = now;

	if (entity_is_task(curr)) {
		struct task_struct *curtask = task_of(curr);

		trace_sched_stat_runtime(curtask, delta_exec, curr->vruntime);
		cpuacct_charge(curtask, delta_exec);
		account_group_exec_runtime(curtask, delta_exec);
	}
}
```

delta_exec存放计算后的当前进程执行时间，传递给__update_curr，然后更新vruntime。

### 2.进程选择(/kernel/sched_fair.c)

CFS选择具有最小vruntime的任务。

CFS使用红黑树来组织可运行进程队列，利用其迅速找到最小的vruntime值的进程。

#### 1.挑选下一个任务

```cpp
static struct sched_entity *__pick_next_entity(struct sched_entity *se)
{
	struct rb_node *next = rb_next(&se->run_node);

	if (!next)
		return NULL;

	return rb_entry(next, struct sched_entity, run_node);
}
```

__pick_next_entity并不会遍历树，而是将该值rb_leftmost字段中。

#### 2.向树中加入进程

在将进程变为可运行状态（被唤醒）或者是通过fork()调用第一次创建子进程时。

```cpp
static void
enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	/*
	 * Update the normalized vruntime before updating min_vruntime
	 * through callig update_curr().
	 */
	if (!(flags & ENQUEUE_WAKEUP) || (flags & ENQUEUE_WAKING))
		se->vruntime += cfs_rq->min_vruntime;

	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);
	update_cfs_load(cfs_rq, 0);
	account_entity_enqueue(cfs_rq, se);
	update_cfs_shares(cfs_rq);

	if (flags & ENQUEUE_WAKEUP) {
		place_entity(cfs_rq, se, 0);
		enqueue_sleeper(cfs_rq, se);
	}

	update_stats_enqueue(cfs_rq, se);
	check_spread(cfs_rq, se);
	if (se != cfs_rq->curr)
		__enqueue_entity(cfs_rq, se);
	se->on_rq = 1;

	if (cfs_rq->nr_running == 1)
		list_add_leaf_cfs_rq(cfs_rq);
}
```

更新运行时间和其它统计数据，并调用__enqueue_entity()进行红黑树插入。

在插入之后会维护最左节点的缓存。

注意到一旦向右走那么久不可能是最小值 leftmost = 0，只有一直向左走才会形成新的最小值此时 leftmost = 1，我们可以用它来判断是否要更新最小值缓存。

```cpp
/*
 * Enqueue an entity into the rb-tree:
 */
static void __enqueue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	struct rb_node **link = &cfs_rq->tasks_timeline.rb_node;
	struct rb_node *parent = NULL;
	struct sched_entity *entry;
	s64 key = entity_key(cfs_rq, se);
	int leftmost = 1;

	/*
	 * Find the right place in the rbtree:
	 */
	while (*link) {
		parent = *link;
		entry = rb_entry(parent, struct sched_entity, run_node);
		/*
		 * We dont care about collisions. Nodes with
		 * the same key stay together.
		 */
		if (key < entity_key(cfs_rq, entry)) {
			link = &parent->rb_left;
		} else {
			link = &parent->rb_right;
			leftmost = 0;
		}
	}

	/*
	 * Maintain a cache of leftmost tree entries (it is frequently
	 * used):
	 */
	if (leftmost)
		cfs_rq->rb_leftmost = &se->run_node;

	rb_link_node(&se->run_node, parent, link);
	rb_insert_color(&se->run_node, &cfs_rq->tasks_timeline);
}
```

#### 4.从树中删除进程

删除动作发生在进程阻塞（变为不可运行状态）或者终止时（结束运行）：

```cpp
static void
dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se, int flags)
{
	/*
	 * Update run-time statistics of the 'current'.
	 */
	update_curr(cfs_rq);

	update_stats_dequeue(cfs_rq, se);
	if (flags & DEQUEUE_SLEEP) {
#ifdef CONFIG_SCHEDSTATS
		if (entity_is_task(se)) {
			struct task_struct *tsk = task_of(se);

			if (tsk->state & TASK_INTERRUPTIBLE)
				se->statistics.sleep_start = rq_of(cfs_rq)->clock;
			if (tsk->state & TASK_UNINTERRUPTIBLE)
				se->statistics.block_start = rq_of(cfs_rq)->clock;
		}
#endif
	}

	clear_buddies(cfs_rq, se);

	if (se != cfs_rq->curr)
		__dequeue_entity(cfs_rq, se);
	se->on_rq = 0;
	update_cfs_load(cfs_rq, 0);
	account_entity_dequeue(cfs_rq, se);
	update_min_vruntime(cfs_rq);
	update_cfs_shares(cfs_rq);

	/*
	 * Normalize the entity after updating the min_vruntime because the
	 * update can refer to the ->curr item and we need to reflect this
	 * movement in our normalized position.
	 */
	if (!(flags & DEQUEUE_SLEEP))
		se->vruntime -= cfs_rq->min_vruntime;
}
```

删除的辅助函数

```cpp
static void __dequeue_entity(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	if (cfs_rq->rb_leftmost == &se->run_node) {
		struct rb_node *next_node;

		next_node = rb_next(&se->run_node);
		cfs_rq->rb_leftmost = next_node;
	}

	rb_erase(&se->run_node, &cfs_rq->tasks_timeline);
}
```

### 3.调度器入口(kernel/sched.c)

schedule会调用pick_next_task

```cpp

/*
 * schedule() is the main scheduler function.
 */
asmlinkage void __sched schedule(void)
{
	struct task_struct *prev, *next;
	unsigned long *switch_count;
	struct rq *rq;
	int cpu;

need_resched:
	preempt_disable();
	cpu = smp_processor_id();
	rq = cpu_rq(cpu);
	rcu_note_context_switch(cpu);
	prev = rq->curr;

	schedule_debug(prev);

	if (sched_feat(HRTICK))
		hrtick_clear(rq);

	raw_spin_lock_irq(&rq->lock);

	switch_count = &prev->nivcsw;
	if (prev->state && !(preempt_count() & PREEMPT_ACTIVE)) {
		if (unlikely(signal_pending_state(prev->state, prev))) {
			prev->state = TASK_RUNNING;
		} else {
			/*
			 * If a worker is going to sleep, notify and
			 * ask workqueue whether it wants to wake up a
			 * task to maintain concurrency.  If so, wake
			 * up the task.
			 */
			if (prev->flags & PF_WQ_WORKER) {
				struct task_struct *to_wakeup;

				to_wakeup = wq_worker_sleeping(prev, cpu);
				if (to_wakeup)
					try_to_wake_up_local(to_wakeup);
			}
			deactivate_task(rq, prev, DEQUEUE_SLEEP);

			/*
			 * If we are going to sleep and we have plugged IO queued, make
			 * sure to submit it to avoid deadlocks.
			 */
			if (blk_needs_flush_plug(prev)) {
				raw_spin_unlock(&rq->lock);
				blk_schedule_flush_plug(prev);
				raw_spin_lock(&rq->lock);
			}
		}
		switch_count = &prev->nvcsw;
	}

	pre_schedule(rq, prev);

	if (unlikely(!rq->nr_running))
		idle_balance(cpu, rq);

	put_prev_task(rq, prev);
	next = pick_next_task(rq);
	clear_tsk_need_resched(prev);
	rq->skip_clock_update = 0;

	if (likely(prev != next)) {
		rq->nr_switches++;
		rq->curr = next;
		++*switch_count;

		context_switch(rq, prev, next); /* unlocks the rq */
		/*
		 * The context switch have flipped the stack from under us
		 * and restored the local variables which were saved when
		 * this task called schedule() in the past. prev == current
		 * is still correct, but it can be moved to another cpu/rq.
		 */
		cpu = smp_processor_id();
		rq = cpu_rq(cpu);
	} else
		raw_spin_unlock_irq(&rq->lock);

	post_schedule(rq);

	preempt_enable_no_resched();
	if (need_resched())
		goto need_resched;
}
EXPORT_SYMBOL(schedule);
```

pick_next_task会以优先级为序，从高到低，依次检查每一个调度类，并且从优先级最高的调度类中，选择最高优先级的进程：

注意其中的一个优化：

 nr_running 保存的是类中运行的进程数目，如果我们知道全部的进程都在cfs中，那么我们就可以直接调用cfs的pick_next_task。

遍历类的时候是按照优先级顺序的，先遍历高优先级的类。

```cpp
#define for_each_class(class) \
   for (class = sched_class_highest; class; class = class->next)

/*
 * Pick up the highest-prio task:
 */
static inline struct task_struct *
pick_next_task(struct rq *rq)
{
	const struct sched_class *class;
	struct task_struct *p;

	/*
	 * Optimization: we know that if all tasks are in
	 * the fair class we can call that function directly:
	 */
	if (likely(rq->nr_running == rq->cfs.nr_running)) {
		p = fair_sched_class.pick_next_task(rq);
		if (likely(p))
			return p;
	}

	for_each_class(class) {
		p = class->pick_next_task(rq);
		if (p)
			return p;
	}

	BUG(); /* the idle class will always have a runnable task */
}
```

### 4.睡眠和唤醒

休眠（被阻塞）的进程处于一个特殊的不可执行状态。

当进去休眠时，进程把自己标记成休眠状态，从可执行红黑树中移出，放入等待队列，然后调用schedule()选择和执行一个其他进程。唤醒过程则刚好相反：进程被置为可执行状态，然后再从等待队列中移到可执行红黑树中。

休眠有两种状态：

TASK_INTERRUPTIBLE和TASK_UNINTERRUPTIBLE。

TASK_UNINTERRUPTIBLE会忽略信号，而TASK_INTERRUPTIBLE状态的进程如果收到一个信号，会被提前唤醒并响应该信号。

两种状态的进程位于同一个等待队列上，等待某些事件，不能够运行。

#### 1.等待队列

内核用wake_queue_head_t来代表等待队列。等待队列可以通过DECLARE_WAITQUEUE()静态创建，也可以用init_waitqueue_head()动态创建。

对于休眠，为了防止接口带来的竞争条件：有可能导致在判定条件变为真之后，进程却开始了休眠，那么久会使得进程无期限地休眠下去。所以在内核进行休眠的推荐操作就相对复杂：

```cpp
/* q是我们希望休眠的等待队列*/
DEFINE_WAIT(wait);

add_wait_queue(q, &wait);
while(!condition){/* ‘condition’是我们等待的事件 */
  prepare_to_wait(&q, &wait, TASK_INTERRUPTIBLE);
	if(signal_pending(current))
    schedule();
}
finish_wait(&q, &wait);
```

进程通过执行以下几个步骤将自己加入等待队列中：

1）调用宏DEFINE_WAIT()创建一个等待队列的项。

2）调用add_wait_queue()方法将自己加到队列中。该队列会在进程等待的条件满足时唤醒它，当然我们必须在其他地方撰写代码，当事件发生时，对等待队列执行weak_up()操作。

3）调用prepare_to_wait()方法将进程的状态变更为TASK_INTERRUPTIBLE或者TASK_UNINTERRUPTIBLE。而且该函数如果有必要的话会将进程加回到等待队列中，这是在接下来循环遍历中需要的。

4）如果状态被设置为TASK_INTERRUPTIBLE，则信号唤起进程。这就是所谓的伪唤醒（唤醒并不是因为事件的发生），因此检查并处理信号。

5）当进程被唤醒的时候，它会再次检查条件是否为真。如果是，就退出循环；如果不是，就会再次调用schedule()并一直重复。

6）当条件满足后，进程将自己设置为TASK_RUNNING并调用finish_wait()方法把自己移出等待队列。

如果在进程进入休眠之前条件就已经达成了，那么循环会推出，进程不会存在错误地进入休眠的倾向。需要注意的是，内核代码在循环体内常常需要完成一些其他的任务，比如调用schedule前要释放掉锁门之后再重新获取它们，或者响应其他事件。



 fs/notify/inotify/inotify_user.c 负责从通知文件描述符中获取信息。

prepare_to_wait里面完成了加入等待队列的动作。

```cpp
/*define on /include/linux/wait.h*/
#define DEFINE_WAIT_FUNC(name, function)				\
	wait_queue_t name = {						\
		.private	= current,				\
		.func		= function,				\
		.task_list	= LIST_HEAD_INIT((name).task_list),	\
	}

#define DEFINE_WAIT(name) DEFINE_WAIT_FUNC(name, autoremove_wake_function)


static ssize_t inotify_read(struct file *file, char __user *buf,
			    size_t count, loff_t *pos)
{
	struct fsnotify_group *group;
	struct fsnotify_event *kevent;
	char __user *start;
	int ret;
	DEFINE_WAIT(wait);

	start = buf;
	group = file->private_data;

	while (1) {
		prepare_to_wait(&group->notification_waitq, &wait, TASK_INTERRUPTIBLE);

		mutex_lock(&group->notification_mutex);
		kevent = get_one_event(group, count);
		mutex_unlock(&group->notification_mutex);

		pr_debug("%s: group=%p kevent=%p\n", __func__, group, kevent);

		if (kevent) {
			ret = PTR_ERR(kevent);
			if (IS_ERR(kevent))
				break;
			ret = copy_event_to_user(group, kevent, buf);
			fsnotify_put_event(kevent);
			if (ret < 0)
				break;
			buf += ret;
			count -= ret;
			continue;
		}

		ret = -EAGAIN;
		if (file->f_flags & O_NONBLOCK)
			break;
		ret = -EINTR;
		if (signal_pending(current))
			break;

		if (start != buf)
			break;

		schedule();
	}

	finish_wait(&group->notification_waitq, &wait);
	if (start != buf && ret != -EFAULT)
		ret = buf - start;
	return ret;
}
```

/kernel/wait.c

注意为了保证互斥，代码中使用了自旋锁（目前还不太了解）

每次检查list_empty为了只在第一次创建时插入队列，避免重复插入。

在自旋锁里set_current_state，就可以防止进程错误的进行休眠。

```cpp
/*
 * Note: we use "set_current_state()" _after_ the wait-queue add,
 * because we need a memory barrier there on SMP, so that any
 * wake-function that tests for the wait-queue being active
 * will be guaranteed to see waitqueue addition _or_ subsequent
 * tests in this thread will see the wakeup having taken place.
 *
 * The spin_unlock() itself is semi-permeable and only protects
 * one way (it only protects stuff inside the critical region and
 * stops them from bleeding out - it would still allow subsequent
 * loads to move into the critical region).
 */
void
prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait, int state)
{
	unsigned long flags;

	wait->flags &= ~WQ_FLAG_EXCLUSIVE;
	spin_lock_irqsave(&q->lock, flags);
	if (list_empty(&wait->task_list))
		__add_wait_queue(q, wait);
	set_current_state(state);
	spin_unlock_irqrestore(&q->lock, flags);
}
EXPORT_SYMBOL(prepare_to_wait);
```

#### 2.唤醒

唤醒操作通过weak_up()进行，会唤醒指定的等待队列上的所有进程。它调用函数try_to_weak_up()，该函数负责将进程置为TASK_RUNNING状态，调用enqueue_task()将进程放入红黑树，如果被唤醒的进程优先级比当前进程高，还要设置need_resched标志。

### 抢占和上下文切换

由kernel/sched.c context_switch函数完成，每当新的进程别选出来准备投入运行的时候，schedule函数就会调用此函数。它完成了两件基本的工作：

调用声明在 asm/mmu_context.h中 switch_mm()，该函数负责把虚拟内存从上一个进程映射到新的进程。

调用声明在 asm/system 中的switch_to,该函数负责从上一个进程的处理器状态更新到新的进程的处理器状态.这包括保存、恢复栈信息和寄存器信息,还有其他任何与体系结构相关的信息,都必须以每个进程为对象进行管理和保护.

```cpp
/*
 * context_switch - switch to the new MM and the new
 * thread's register state.
 */
static inline void
context_switch(struct rq *rq, struct task_struct *prev,
	       struct task_struct *next)
{
	struct mm_struct *mm, *oldmm;

	prepare_task_switch(rq, prev, next);

	mm = next->mm;
	oldmm = prev->active_mm;
	/*
	 * For paravirt, this is coupled with an exit in switch_to to
	 * combine the page table reload and the switch backend into
	 * one hypercall.
	 */
	arch_start_context_switch(prev);

	if (!mm) {
		next->active_mm = oldmm;
		atomic_inc(&oldmm->mm_count);
		enter_lazy_tlb(oldmm, next);
	} else
		switch_mm(oldmm, mm, next);

	if (!prev->mm) {
		prev->active_mm = NULL;
		rq->prev_mm = oldmm;
	}
	/*
	 * Since the runqueue lock will be released by the next
	 * task (which is an invalid locking op but in the case
	 * of the scheduler it's an obvious special-case), so we
	 * do an early lockdep release here:
	 */
#ifndef __ARCH_WANT_UNLOCKED_CTXSW
	spin_release(&rq->lock.dep_map, 1, _THIS_IP_);
#endif

	/* Here we just switch the register state and the stack. */
	switch_to(prev, next, prev);

	barrier();
	/*
	 * this_rq must be evaluated again because prev may have moved
	 * CPUs since it called schedule(), thus the 'rq' on its stack
	 * frame will be invalid.
	 */
	finish_task_switch(this_rq(), prev);
}
```

```cpp
extern void switch_mm(struct mm_struct *prev, struct mm_struct *next,
		      struct task_struct *tsk);
```

```cpp
#define switch_to(P,N,L)						 \
  do {									 \
    (L) = alpha_switch_to(virt_to_phys(&task_thread_info(N)->pcb), (P)); \
    check_mmu_context();						 \
  } while (0)
```

内核必须要知道什么时候调用schedule(). 内核提供了一个need_resched标志来表示是哦副需要重新执行一次调度.

1) 当某个进程应该被抢占时,scheduler_tick()就会设置这个标志

2) 当一个优先级高的进程进入可执行状态时,try_to_wake_up()也会设置这个标志.

内核检查该标志确认其被设置,调用schedule()来切换到一个新的进程. 该标志对于内核来讲是一个信息,它提示有其他进程应当被运行,要尽快进行调度.
再返回用户空间以及从中断中返回的时候,内核也会检查need_resched标志.如果已被设置,内核会在继续执行之前调用调度程序.

每个进程都包含一个nned_resched标志,这是因为访问进程描述符内的数值要比访问一个全局变量快(因为current宏速度很快,并且描述符通常都在高速缓存中).

#### 用户抢占

内核无论是在中断处理程序还是在系统调用后返回,都会检查need_resched标志.如果它被设置了,那么,内核会选择一个更合适的进程投入运行

用户抢占在以下情况发生:

* 从系统调用返回用户空间时.
* 从中断处理程序返回用户空间时.

#### 内核抢占

Linux完整的支持内核抢占,只要没有锁,内核就可以进行抢占.

为了支持内核抢占所做的第一出变动就是为每个进程的thread_info引入preempt_count计数器.该计数器初始化为0,每当使用锁的时候加1,释放锁的时候减1.当数值为0的时候内核就可以执行抢占.

从中断中返回内核空间时,如果need_resched被设置,并且preempt_count为0的话,说明有一个更为重要的任务需要执行,并且可以安全地抢占,程序就会被调用.

内核抢占发生在:

* 中断处理程序正在执行,且返回内核之前
* 内核代码再一次具有可抢占性的时候
* 如果内核中的任务显示地睇啊用schedule()
* 如果内核中的任务阻塞

### 实时调度策略

Linux下两种实时调度策略SCHED_FIFO 和 SCHED_RR, 而普通的、非实时的调度策略时SCHED_NORMAL.

## 系统调用

getpid()系统调用,在内核中的实现:

```cpp
SYSCALL_DEFINE0(getpid)
{
  return task_tgid_vnr(current);
}
```

SYSCALL_DEFINE0是一个宏,展开后

```cpp
asmlinkage long sys_getpid(void)
```



asmlinkage, 编译指令,通知编译器仅从栈中提取该函数的参数,返回long 为了 32 位、64位兼容

用户空间返回int,内核空间返回long.

用户空间的getpid , 内核空间定义为sys_getpid ,加了一个sys_,这是一般规则.

#### 系统调用处理程序

通知内核的机制靠软中断实现:通过引发一个异常来促使系统切换到内核态执行异常处理程序.

x86上预定义的软中断号128,通过int $0x80 指令出发中断,该指令会触发异常导致系统切换到内核态并执行第128号异常处理程序,而该程序正是系统调用处理程序.这个处理程序名字起的很怯贴叫做sys_call(),x86-64的entry_64.S文件中用汇编编写. x86 也新增了一条指令叫做sysenter的指令,与int中断指令相比,这条指令提供了更快更专业的陷入内核执行系统调用的方式.

#### 指定恰当的系统调用

中断号通过eax传给内核,system_call会将中断好与NR_syscalls做比较检查有效性.如果大于等于NR_syscalls就返回-ENOSYS,否则就执行相应的系统调用

`call * sys_call_table(,%rax,8)`

由于系统调用的表项是以64位存储的,所以内核需要将给定的系统调用号乘4,然后用结果在表中查询其位置,在x86-64上代码很类似,只是用4代替8.

#### 参数检验

参数合法、有合法权限

#### 绑定一个系统调用的最后步骤

1) 首先,在系统调用表的最后加入一个表项.

2) 对于所有支持的各种体系结构,系统调用号都必须定义于<asm/unistd.h>中

3) 系统调用必须被编译进内核映像(不能被编译成模块).这只要把它放进kernel/下的一个相关文件夹中就可以了,比如sys.c,它包含了各种各样的系统调用.

## 内核数据结构





## 中断和中断处理

中断值