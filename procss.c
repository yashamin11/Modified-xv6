#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "pstat.h"



struct proc *queue[5][NPROC];
int q_tail[5] = {-1, -1, -1, -1, -1}, q_ticks_max[5] = {1, 2, 4, 8, 16}, q_ticks[5] = {0,0,0,0,0};

int add_proc_to_q(struct proc *p, int q_no);
int remove_proc_from_q(struct proc *p, int q_no);

void change_q_flag(struct proc* p)
{
	acquire(&ptable.lock);
	p-> change_q = 1;
	release(&ptable.lock);
}

void incr_curr_ticks(struct proc *p)
{
	acquire(&ptable.lock);
	p->curr_ticks++;
	p->ticks[p->queue]++;
	release(&ptable.lock);
}

void scheduler(void)
{
	struct cpu *c = mycpu();
	c->proc = 0;

	for (;;)
	{
		// cprintf("jyertd\n");

		// Enable interrupts on this processor.
		sti();

		// Loop over process table looking for process to run.
		acquire(&ptable.lock);
		// cprintf("arre");

		
		#else
		#ifdef FCFS
		// cprintf("FCFS\n");
		struct proc *p;
		struct proc *min_proc = 0;
		//cprintf("wheee\n");
		for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
		{

			if (p->state != RUNNABLE)
				continue;

			//if(p->pid > 1)
			{
				if (min_proc == 0)
					min_proc = p;
				else if (p->ctime < min_proc->ctime)
					min_proc = p;
			}
		}

		if (min_proc != 0 && min_proc->state == RUNNABLE)
		{
			#ifdef T
				cprintf("Process %s with PID %d and start time %d running\n",min_proc->name, min_proc->pid, min_proc->ctime);
			#endif
			p = min_proc;

			c->proc = p;
			switchuvm(p);
			p->num_run++;
			p->state = RUNNING;

			swtch(&(c->scheduler), p->context);
			switchkvm();

			// Process is done running for now.
			// It should have changed its p->state before coming back.
			c->proc = 0;
		}
		#else
		#ifdef PBS

			struct proc *p;
			struct proc *min_pr_proc = 0;
			
			for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
			{
				if (p->state != RUNNABLE)
					continue;	

				if (min_pr_proc == 0)
					min_pr_proc = p;
				
				else if (p-> priority < min_pr_proc-> priority)
					min_pr_proc = p;
				
			}

			if(min_pr_proc == 0)
			{
				release(&ptable.lock);
				continue;		
			}

			for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
			{
				struct proc *q; int flag =0;
				for(q = ptable.proc; q < &ptable.proc[NPROC]; q++)
				{
					// cprintf("yeet");
					if (q->state != RUNNABLE)
						continue;
					
					if(q->priority < min_pr_proc->priority)
						flag = 1;
				}

				if(flag == 1)
					// cprintf("yeet");
					break;
				

				if (p->state != RUNNABLE)
					continue;

				else if (p->priority == min_pr_proc->priority)
				{
					#ifdef T
						cprintf("Process %s with PID %d and priority %d running\n",p->name, p->pid, p->priority);
					#endif
					c->proc = p;
					switchuvm(p);
					p->num_run++;
					p->state = RUNNING;

					swtch(&(c->scheduler), p->context);
					switchkvm();
					//if (p->state == RUNNABLE) break;

					// Process is done running for now.
					// It should have changed its p->state before coming back.
					// cprintf("PID %d done !!!\n\n", min_pr_proc->pid);
					c->proc = 0;
				}
			}
		#else
		#ifdef MLFQ


			for(int i=1; i < 5; i++)
			{
				for(int j=0; j <= q_tail[i]; j++)
				{
					struct proc *p = queue[i][j];
					int age = ticks - p->enter;
					if(age > 30)
					{
						remove_proc_from_q(p, i);
						#ifdef T
							cprintf("Process %d moved up to queue %d due to age time %d\n", p->pid, i-1, age);
						#endif
						add_proc_to_q(p, i-1);
					}

				}
			}
			struct proc *p =0;

			// int oof = 0;
			for(int i=0; i < 5; i++)
			{
				if(q_tail[i] >=0)
				{
					//oof = 1;
					p = queue[i][0];
					remove_proc_from_q(p, i);
					break;
				}
			}

			if(p!=0 && p->state==RUNNABLE)
			{
				p->curr_ticks++;
				p->num_run++;
				#ifdef T
					cprintf("Scheduling %s with PID %d from Queue %d with current tick %d\n",p->name, p->pid, p->queue, p->curr_ticks);
				#endif
				p->ticks[p->queue]++;
				c->proc = p;
				switchuvm(p);
				p->state = RUNNING;
				swtch(&c->scheduler, p->context);
				switchkvm();
				c->proc = 0;

				if(p!=0 && p->state == RUNNABLE)
				{
					if(p->change_q == 1)
					{
						p->change_q = 0;
						p->curr_ticks = 0;
						// int old = p->queue;
						if(p->queue != 4)
							p->queue++;
						
						// cprintf("Moving Process from Queue %d to Queue %d\n", old,p->queue);

					}

					else p->curr_ticks = 0;
					
					// p->age = ticks;
					// cprintf("Adding Process %d to Queue %d\n",p->pid ,p->queue);
					add_proc_to_q(p, p->queue);

				}
			}
				 
		
		#endif
		#endif
		#endif
		#endif

		release(&ptable.lock);
	}
}
r.

int add_proc_to_q(struct proc *p, int q_no)
{	

	for(int i=0; i < q_tail[q_no]; i++)
	{
		if(p->pid == queue[q_no][i]->pid)
			return -1;
	}
	// cprintf("Process %d added to Queue %d\n", p->pid, q_no);
	p->enter = ticks;
	p -> queue = q_no;
	q_tail[q_no]++;
	queue[q_no][q_tail[q_no]] = p;
	//cprintf("yeet 1\n");

	return 1;
}

int remove_proc_from_q(struct proc *p, int q_no)
{
	int proc_found = 0, rem = 0;
	for(int i=0; i <= q_tail[q_no]; i++)
	{
		// cprintf("\n%d yeet\n", queue[q_no][i] -> pid);
		if(queue[q_no][i] -> pid == p->pid)
		{
			//cprintf("Process %d found in Queue %d\n", p->pid, q_no);
			rem = i;
			proc_found = 1;
			break;
		}
	}

	if(proc_found  == 0)
	{
		// cprintf("Process %d not found in Queue %d\n", p->pid, q_no);
		return -1;
	}

	for(int i = rem; i < q_tail[q_no]; i++)
		queue[q_no][i] = queue[q_no][i+1]; 

	q_tail[q_no] -= 1;
	// cprintf("Process %d removed from Queue %d\n", p->pid, q_no);
	return 1;

}