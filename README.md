# Philosophers
My solution of philosophers problem
## Rules
There are some ```<number of philosophers>``` sitting around the table. They can only do one action at a time: eat, sleep, think. Each one does these action in a cycle.
To eat a philosopher needs two forks. Number of forks equals ```<number of philosophers>```. When a philosopher has taken two works he starts to eat for ```<time to eat>``` ms. After end of eating he will put down forks and sleep for ```<time to sleep>``` ms. After waking up a philosopher starts thinking until two forks are released.  If a philosopher does not eat ```<time to die>``` ms, he dies and simulation stops. Simulation also stops when all the philosophers ate at least ```<minimum number of meals>``` if specified.
### philo_threads
Each philosopher is a thread. Forks are placed between philosophers. Syncronization is acomplished using mutexes.
### philo_proccesses
Each philosopher is a process. All the forks are put in the middle of the table. Syncronization is acomplished using semaphores.
## Usage
For each one of solutions do
```
make
./philo <number of philosophers> <time to die(ms)> <time to eat(ms)> <time to sleep(ms)> <minimum number of meals>
```
