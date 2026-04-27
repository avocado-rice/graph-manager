## 🍴 Dining Philosophers - C++ Multithreading & Visual Simulation
A high-performance C++ implementation of the Dining Philosophers Problem. It serves as a practical study of thread synchronization and resource allocation.
### Overview
The main focus of this project was conducting an in-depth analysis of thread synchronisation and examining different resource allocation management strategies.
### Goals
* Identifying critical sections and potential race conditions in order to perform a synchronisation analysis.
* Ensuring the implementation eliminates deadlocks while minimizing thread starvation.
* Measuring the effectiveness of the proposed synchronization solutions.
* Observing how the system behaves as the number of threads and shared resources increases.
### Key features

### Implemented solutions
The following solutions were implemented and tested in terms of synchronisation and resource allocation.
#### 1. Naive Approach
Each philosopher picks up the left fork followed by the right one. After acquiring both forks he begins to eat. After finishing his meal ge frees the resources and goes back to thinking. While simple to implement, this method is prone to circular wait conditions that lead to system-wide deadlocks and uneven resource distribution.

#### 2. Resource Hierarchy
This algorithm prevents deadlocks by requiring philosophers to pick up forks in a predefined numerical order (lower-numbered fork first). By breaking the cycle of dependency, it ensures at least one philosopher can always proceed. although it may result in imbalances in meal counts.

#### 3. Arbitrator (Waiter) Solution
A central controller manages fork access, granting permission only when both required forks are simultaneously available. This prevents the scenario where philosophers are stuck with a single resource, utilizing mutexes to ensure safe and synchronized access.
