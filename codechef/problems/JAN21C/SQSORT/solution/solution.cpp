#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cassert>
using namespace std;

#define DEBUG 0

#if DEBUG
  #define debug printf
#else
  #define debug(...) 1 == 1
#endif

const int INFINITY = 1 << 30;
const int MAX_CONTAINERS = 128;
const int MAX_BLOCKS = 1024;

// Variables for the problem
int N, B;
int C[MAX_CONTAINERS], D[MAX_CONTAINERS], W[MAX_BLOCKS];
int A[MAX_CONTAINERS][MAX_BLOCKS];

// Variables for the solution
queue<int> container[MAX_CONTAINERS];
queue<int> container_init_state[MAX_CONTAINERS];
vector<pair<int, int> > solution;

int initial_full_container = 0;
int initial_empty_container = 1;

/**
 * Forward declaration of stuff.
 */
void input();
void verify_solution();

/**
 * Gets the next best container looking at the C[i] and D[i] values
 * @param index The index to ignore while choosing.
 * @return The index of the next best container.
 */
int get_next_best_container(int index) {
  int mins = INFINITY;
  int min_index = -1;
  for (int i = 0; i < N; i++) {
    if (i != index) {
      if (C[i] + D[i] < mins) {
        mins = C[i] + D[i];
        min_index = i;
      }
    }
  }
  return min_index;
}

/**
 * Decides which containers will the working containers.
 * We need to 2 containers to alternatively push and pop the blocks.
 */
void decide_empty_full_queues() {
  /**
   * Choose the best 2 containers based on C[i] and D[i] values.
   */
  initial_full_container = get_next_best_container(-1);
  initial_empty_container = get_next_best_container(initial_full_container);


  /**
   * Out of these two containers, which one do we want to be the initial full container ?
   * We decide that on the basis of the for the container i the heuristic that we use is, C[i] * sum(W[j]) for all j in that container initially
   * Based on the above heuristic, we swap the containers if necessary
   */
  int sum_full_queue = 0;
  int sum_empty_queue = 0;

  for (int i = 0; i < container[initial_full_container].size(); i++) {
    sum_full_queue += container[initial_full_container].front();
     container[initial_full_container].push(container[initial_full_container].front());
     container[initial_full_container].pop();
  }

  for (int i = 0; i < container[initial_empty_container].size(); i++) {
    sum_empty_queue += container[initial_empty_container].front();
     container[initial_empty_container].push(container[initial_empty_container].front());
     container[initial_empty_container].pop();
  }

  if (
    (sum_empty_queue * (C[initial_empty_container] + D[initial_full_container])) >
    (sum_full_queue * (C[initial_full_container] + D[initial_empty_container]))
  ) {
    swap(initial_empty_container, initial_full_container);
  }
  assert(initial_full_container != initial_empty_container);
}

/**
 * Transfer all the blocks to the zeroth queue
 */
void transfer_to_initial_full_queue() {
  int total = container[initial_full_container].size();
  while(total != B) {
    int mins = INFINITY, min_index = -1;
    for (int i = 0; i < N; i++) {
      if (i == initial_full_container) continue;
      if (container[i].size() > 0 && container[i].front() < mins) {
        mins = container[i].front();
        min_index = i;
      }
    }
    container[initial_full_container].push(
      container[min_index].front()
    );
    container[min_index].pop();
    solution.push_back(
      make_pair(
        min_index, initial_full_container
      )
    );
    total += 1;
  }
  /**
   * We assert that all elements have been transferred to the 0th queue.
   */
  assert(container[initial_full_container].size() == B);
}

void distribute_evenly() {
  int full_queue = initial_full_container;
  int empty_queue = initial_empty_container;
  /**
   * We have the zeroth queue as the full queue.
   * We have the first queue as the buffer.
   * Now there are N - 2 other empty queues. Let K = N -2.
   * Algorithm:
   * Target: ith queue will contain i, i + K, i + 2*K, i + 3*K etc.
   */
  int K = N - 2;
  /**
   * We have to keep doing this until all our elements are put into their respective queues.
   */
  while (container[full_queue].size() != 0) {
    /**
     * Each iteration goes through all the elements in the full queue.
     * In every iteration below atleast K elements will be processed.
     * More elements may be processed if the elements appear in ascending order. But that's for later.
     */
    while(container[full_queue].size() != 0) {
      int block = container[full_queue].front(); // The current element which is being processed
      int queue_bucket = (block - 1) % K; // The bucket in which it falls
      int queue_index = queue_bucket;

      queue_index += queue_index >= min(empty_queue, full_queue) ? 1 : 0;
      queue_index += queue_index >= max(empty_queue, full_queue) ? 1 : 0;
      /**
       * There are 2 scenarios.
       * The element is the first element to be inserted into the respective queue
       * The element is K + the previous element in the respective queue
       */
      if (
        (container[queue_index].size() == 0 && block == queue_bucket + 1)
        || (container[queue_index].size() > 0 && block == container[queue_index].back() + K)
      ) {
        container[queue_index].push(block);
        solution.push_back(
          make_pair(
            full_queue, queue_index
          )
        );
      } else {
        container[empty_queue].push(block);
        solution.push_back(
          make_pair(
            full_queue, empty_queue
          )
        );
      }
      container[full_queue].pop();
    }
    swap(empty_queue, full_queue);
  }
  /**
   * At the end of the process, both INITIAL queues must be empty.
   */
  assert(container[initial_full_container].size() == 0 && container[initial_empty_container].size() == 0);
}

/**
 * Sort all the queue back to the empty queue.
 */
void sort_the_queues() {
  assert(container[initial_empty_container].size() == 0);
  assert(container[initial_full_container].size() == 0);
  int empty_queue = initial_full_container;
  int total = 0;
  /**
   * We need to add all the blocks to the solution.
   */
  while(total < B) {
    /**
     * Go through the K (N - 2) buckets to add the numbers one after the other
     */
    for (int i = 0; i < N; i++) {
      if (i == empty_queue) continue;
      if (container[i].size() != 0) {
        container[empty_queue].push(container[i].front()); // Add it to the empty queue
        assert(container[i].front() == total + 1);
        container[i].pop(); // Remove it from the current queue
        // Add it to the solution
        solution.push_back(
          make_pair(
            i, empty_queue
          )
        );
        total += 1;
      }
    }
  }
  assert(container[empty_queue].size() == B);
}



void print_solution() {
  for (int i = 0; i < N; i++) {
    printf("Q");
  }
  printf("\n");
  printf("%lu\n", solution.size());
  for (auto move: solution) {
    printf("%d %d\n", move.first + 1, move.second + 1);
  }
}

void solve() {
  decide_empty_full_queues();
  transfer_to_initial_full_queue();
  distribute_evenly();
  sort_the_queues();
}

int main() {
  input();
  solve();
  verify_solution();
  print_solution();
  return 0;
}

/**
 * Take the input
 */
void input() {
  scanf("%d %d", &N, &B);
  for (int i = 0; i < N; i++) {
    scanf("%d", C + i);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", D + i);
  }
  for (int i = 0; i < B; i++) {
    scanf("%d", W + i);
  }
  for (int i = 0; i < N; i++) {
    int M;
    scanf("%d", &M);
    for (int j = 0; j < M; j++) {
      scanf("%d", &A[i][j]);
      container[i].push(A[i][j]);
      container_init_state[i].push(A[i][j]);
    }
  }
}

void verify_solution() {
  assert(B < 1024 || solution.size() <= (B * B) / 2); // Assert that the solution size is also withing bounds
  // Doing the same operations as given in the solution in the copy queues that we have made
  for (auto move: solution) {
    assert((move.first < N) && (move.second < N)); // Valid container indices
    assert(move.first != move.second); // You cannot push and pop to the same container. Verify this you idiot.
    assert(container_init_state[move.first].size() > 0);   // Asserting we are not popping from an empty queue.
    container_init_state[move.second].push(
      container_init_state[move.first].front()
    );
    container_init_state[move.first].pop();
  }
  // Now that we have done the Q operations, then we verify that it yielded that solution that we wanted
  int full_queue = -1;
  int num_empty_queue = 0;
  for (int i = 0; i < N; i++) {
    if (container[i].size() != 0) {
      full_queue = i;
    } else {
      num_empty_queue += 1;
    }
  }
  assert(full_queue != -1); // At the end, there should be atleast one full queue
  assert(num_empty_queue == N - 1); // At the end there should be exactly N - 1 empty queues
  assert(container_init_state[full_queue].size() == B); // The full queue should contain exactly B elements
  // The B elements in the queue should be in sorted order from 1 to B
  int i = 1;
  while(container_init_state[full_queue].size() != 0) {
    assert(container_init_state[full_queue].front() == i);
    container_init_state[full_queue].pop();
    i += 1;
  }
  assert(i == B + 1); // Assert that the last element that we saw was B
}
