


EXIT(1)							User Commands							EXIT(1)
https://man7.org/linux/man-pages/man1/exit.1p.html    POSIX definition of exit builtin in the shell


EXIT(2)							User Commands							EXIT(2)
https://man7.org/linux/man-pages/man2/_exit.2.html 	GLIBC definition of _exit system call, which is called by exit() in libc


EXIT(3)							User Commands							EXIT(3)
https://man7.org/linux/man-pages/man3/exit.3.html  GLIBC definition of exit() in the C library




BASH GIT
https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/




/* exit builtin
↓
get_exitstat() → returns (42 & 255)
↓
last_command_exit_value = 42
↓
exit(42)  ← libc
↓
sys_exit_group(42)  ← kernel



N is the *argument* to the `exit` builtin: `exit 42`, `exit -1`, `exit 999`, etc.
The **exit status** is the *final integer Bash publishes as the shell’s termination status* (and as `$?` while still running.
In Bash, exit statuses are treated as **8-bit values** (0–255). So any numeric `N` is normalized modulo 256 using a bitmask.

*/


/* WEBSITE https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/builtins/exit.def


This file is exit.def, from which is created exit.c.
It implements the builtins "exit", and "logout" in Bash.

Copyright (C) 1987-2024 Free Software Foundation, Inc.

This file is part of GNU Bash, the Bourne Again SHell.

Bash is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Bash is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Bash.  If not, see <http://www.gnu.org/licenses/>.

$PRODUCES exit.c

$BUILTIN exit
$FUNCTION exit_builtin
$SHORT_DOC exit [n]
Exit the shell.


Exits the shell with a status of N.  If N is omitted, the exit status
is that of the last command executed.
$END
 */



#include <config.h>

#include "../bashtypes.h"
#include <stdio.h>

#if defined (HAVE_UNISTD_H)
#  include <unistd.h>
#endif

#include "../bashintl.h"

#include "../shell.h"
#include "../execute_cmd.h"
#include "../jobs.h"
#include "../trap.h"

#include "common.h"
#include "builtext.h"	/* for jobs_builtin */



static int exit_or_logout (WORD_LIST *);

int
exit_builtin (WORD_LIST *list)
{
  CHECK_HELPOPT (list);

  if (interactive)
    {
      fprintf (stderr, login_shell ? _("logout\n") : "exit\n");
      fflush (stderr);
    }

  return (exit_or_logout (list));
}


///$BUILTIN logout

// in file BASH   builtins/common.c.\
// https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/builtins/common.c


static int
exit_or_logout (WORD_LIST *list)
{
  int exit_value;

/* #if defined (JOB_CONTROL)
  int exit_immediate_okay, stopmsg;

  exit_immediate_okay = (interactive  == 0 ||
			 last_shell_builtin == exit_builtin ||
			 last_shell_builtin == logout_builtin ||
			 last_shell_builtin == jobs_builtin);

  /* Check for stopped jobs if the user wants to.
  if (exit_immediate_okay == 0)
    {
      register int i;
      for (i = stopmsg = 0; i < js.j_jobslots; i++)
	if (jobs[i] && STOPPED (i))
	  stopmsg = JSTOPPED;
	else if (check_jobs_at_exit && stopmsg == 0 && jobs[i] && RUNNING (i))
	  stopmsg = JRUNNING;

      if (stopmsg == JSTOPPED)
	fprintf (stderr, _("There are stopped jobs.\n"));
      else if (stopmsg == JRUNNING)
	fprintf (stderr, _("There are running jobs.\n"));

      if (stopmsg && check_jobs_at_exit)
        list_all_jobs (JLIST_STANDARD);

      if (stopmsg)
	{
	  this_shell_builtin = last_shell_builtin = exit_builtin;
	  return (EXECUTION_FAILURE);
	}
    }
#endif  JOB_CONTROL  */

  /* Get return value if present.  This means that you can type
     `logout 5' to a shell, and it returns 5. */

  /* If we're running the exit trap (running_trap == 1, since running_trap
     gets set to SIG+1), and we don't have a argument given to `exit'
     (list == 0), use the exit status we saved before running the trap
     commands (trap_saved_exit_value). get_exitstat() handles the case of
     running exit from any other trap action (POSIX interp 1602). */


  exit_value = (running_trap == 1 && list == 0) ? trap_saved_exit_value : get_exitstat (list);	////// in get_exit is N normalized to an 8 bit int
  if (exit_value > EX_SHERRBASE)
    return (exit_value);

  bash_logout ();

  last_command_exit_value = exit_value;		///// SET THE EXIT STATUS TO THE ARGUMENT GIVEN TO EXIT, OR THE EXIT STATUS OF THE LAST COMMAND IF NO ARGUMENTS WERE GIVEN, SO THAT IT CAN BE RETURNED TO THE PARENT PROCESS

  /* Exit the program. */
  jump_to_top_level (EXITBLTIN);			/// JUMP TO TOP LEVEL, WHICH CALLS exit_shell() TO EXIT THE SHELL WITH THE EXIT STATUS SET ABOVE
  /*NOTREACHED*/
}





////////////////////    DETAILS	THE WAY BACK FROM GETTING STATUS FROM N TO exit(int status) ////////////////////




void
no_args (WORD_LIST *list, int fatal)
{
  if (list)
    {
      builtin_error (_("too many arguments"));
      top_level_cleanup ();
      set_exit_status (EX_BADUSAGE);
      /* for now, the caller determines whether this is a fatal error */
      if (interactive_shell == 0 && fatal)
	jump_to_top_level (EXITPROG);
      else
	jump_to_top_level (DISCARD);
    }
}



/* Get an eight-bit status value from LIST */        	// in file BASH   builtins/common.c.
														// https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/builtins/common.c
int get_exitstat (WORD_LIST *list)
{
  int status;
  intmax_t sval;
  char *arg;

  if (list && list->word && ISOPTION (list->word->word, '-'))
    list = list->next;

  if (list == 0)
    {
      if (this_shell_builtin == return_builtin && running_trap > 0 && running_trap != DEBUG_TRAP+1 && trap_return_context == funcnest + sourcenest)
	return (trap_saved_exit_value);

      if (this_shell_builtin == exit_builtin && running_trap > 0 && running_trap != DEBUG_TRAP+1 && trap_return_context == funcnest + sourcenest)
	return (trap_saved_exit_value);
      return (last_command_exit_value);          ////////// IF NO ARGUMENTS, RETURN THE EXIT STATUS OF THE LAST COMMAND
    }

  arg = list->word->word;
  if (arg == 0 || valid_number (arg, &sval) == 0)
    {
      sh_neednumarg (list->word->word ? list->word->word : "`'");
      return EX_USAGE;
    }
  no_args (list->next, 0);

  status = sval & 255;							////////// IF ARGUMENTS, RETURN THE ARGUMENTS AS AN 8-BIT INTEGER// (POSIX INTERP 1602: "If the exit status is specified, the shell shall exit with the value of the expression modulo 256.")
  return status;
}


//// in shell.c   --> https://cgit.git.savannah.gnu.org/cgit/bash.git/tree/shell.c
///// JUMP TO TOP LEVEL, WHICH CALLS exit_shell() TO EXIT THE SHELL WITH THE EXIT STATUS SET ABOVE
{
	top_level_arg_index = arg_index;
	old_errexit_flag = exit_immediately_on_error;

	code = setjmp_sigs (top_level);
	if (code)
    {
		if (code == EXITPROG || code == ERREXIT || code == EXITBLTIN)
		exit_shell (last_command_exit_value);
	}
}




/* Exit the shell with status S. */
void
exit_shell (int s)
{
  fflush (stdout);		/* XXX */
  fflush (stderr);


#if defined (READLINE)
  if (bash_readline_initialized && RL_ISSTATE (RL_STATE_TERMPREPPED) && rl_deprep_term_function)
    (*rl_deprep_term_function) ();
#endif
  if (read_tty_modified ())
    read_tty_cleanup ();


  if (signal_is_trapped (0))
    s = run_exit_trap ();

#if defined (PROCESS_SUBSTITUTION)
  unlink_all_fifos ();
#endif

#if defined (HISTORY)
  if (remember_on_history)
    maybe_save_shell_history ();
#endif /* HISTORY */

#if defined (COPROCESS_SUPPORT)
  coproc_flush ();
#endif

#if defined (JOB_CONTROL)
  /* If the user has run `shopt -s huponexit', hangup all jobs when we exit
     an interactive login shell.  ksh does this unconditionally. */
  if (interactive_shell && login_shell && hup_on_exit)
    hangup_all_jobs ();

  /* If this shell is interactive, or job control is active, terminate all
     stopped jobs and restore the original terminal process group.  Don't do
     this if we're in a subshell and calling exit_shell after, for example,
     a failed word expansion.  We want to do this even if the shell is not
     interactive because we set the terminal's process group when job control
     is enabled regardless of the interactive status. */
  if (subshell_environment == 0)
    end_job_control ();
#endif /* JOB_CONTROL */

  /* Always return the exit status of the last command to our parent. */
  sh_exit (s);
}



/* A wrapper for exit that (optionally) can do other things, like malloc
   statistics tracing. */
void
sh_exit (int s)
{
#if defined (MALLOC_DEBUG) && defined (USING_BASH_MALLOC)
  if (malloc_trace_at_exit && (subshell_environment & (SUBSHELL_COMSUB|SUBSHELL_PROCSUB)) == 0)
    trace_malloc_stats (get_name_for_error (), NULL);

#endif

  exit (s);														// CALL THE LIBC exit() FUNCTION TO EXIT THE SHELL WITH THE EXIT STATUS PASSED TO sh_exit()
}
