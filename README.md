
# Philosophers

A 42 school project. It's purpose is to teach the student about threads and mutexes (standard version). And forks and semaphores (bonus version).

/!\ If you are a 42 student, do not copy this project as it isn't correct under this form. It is currently dependent on the computer's performance.

## Standard version

#### Subject :
```
Simply the dining philosophers problem, see wikipedia :

https://en.wikipedia.org/wiki/Dining_philosophers_problem.

Summary of rules :
- Each philosopher should be a thread.
- There is one fork between each philosopher.
- There should be no data race.
```

#### Permitted functions :
```
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```

#### Expected parameters :
```
- number_of_philosophers
- time_to_die time_to_eat
- time_to_sleep
- [number_of_times_each_philosopher_must_eat] (optional)
```

### Bonus version

#### Subject :
```
A new version of the dining philosophers problem :

Summary of rules :
- All rules of the standard project.
- Each philosopher should be a process. The main process shouldn't be a philosopher.
- All forks are at the center of the table, represented by a semaphore.
```

#### Permitted functions :
```
memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
```

#### Expected parameters :
```
- number_of_philosophers
- time_to_die time_to_eat
- time_to_sleep
- [number_of_times_each_philosopher_must_eat] (optional)
```
## Usage / Examples

#### Open a terminal window and clone the git repository (needs git).

```git clone git@github.com:PliegerNicolas/philosophers.git```

#### Enter the desired folder (philo or philo_bonus).

```cd philosophers/philo/ or cd philosophers/philo_bonus```

#### Compile the program.

```
Execute the desired command :
- make          <= this compiles the program.
- make re       <= this deletes everything and compiles everything as new.
- make clean    <= this clears .obj files. Those are not useful anymore once the program is compiled in our context.
- make fclean   <= this clears everything, even the program itself.
```

#### Run the program.

```
If in philo folder :
./philosophers

If in philo_bonus folder :
./philosophers_bonus

This should display the expected arguments.
```

Next ... Have fun !

# Tips for 42 students.

Use valgrind --tool=helgrind on launch or -fsanitize=thread in compilation to test deadlocks, data races, etc.

Philo :
There is a strategy based on parity to prevent deadlocks. But you should also think about priority and hierarchy in grabbing forks. The problem is that threads can some times have latency when launching so you have to add security (see srcs/life/philosopher_actions (try_thinking)).

Philo_bonus :
By using exit(exit_code) i can interpret the exit_code as information (finished eating or philosopher died).
My main process runs one thread for every created fork and waits for their exit. The forks themselves launch a thread to monitor the philosopher's life cycle.
