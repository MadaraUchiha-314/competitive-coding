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

// Variables for the problem
int N, B;
int C[128], D[128], W[1024];
int A[128][1024];

// Variables for the solution
queue<int> block_queues[128];
queue<int> copy_queue[128];
vector<pair<int, int> > solution;

int INITIAL_FULL_QUEUE = 0;
int INITIAL_EMPTY_QUEUE = 1;
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
      block_queues[i].push(A[i][j]);
      copy_queue[i].push(A[i][j]);
    }
  }
}

int get_min_not_at_index(int index) {
  int mins = 1 << 20;
  int min_index = -1;
  for (int i = 0; i < N; i++) {
    if (i != index) {
      if (C[i] + D[i] < mins) {
        mins = C[i] + D[i];
        min_index = i;
      }
    }
  }
  assert(min_index > -1);
  return min_index;
}

void decide_empty_full_queues() {
  INITIAL_FULL_QUEUE = get_min_not_at_index(-1);
  INITIAL_EMPTY_QUEUE = get_min_not_at_index(INITIAL_FULL_QUEUE);
  assert(INITIAL_FULL_QUEUE != INITIAL_EMPTY_QUEUE);
}

/**
 * Transfer all the blocks to the zeroth queue
 */
void transfer_to_initial_full_queue() {
  for (int i = 0; i < N; i++) {
    if (i == INITIAL_FULL_QUEUE) continue;
    while(block_queues[i].size() != 0) {
      block_queues[INITIAL_FULL_QUEUE].push(
        block_queues[i].front()
      );
      block_queues[i].pop();
      solution.push_back(
        make_pair(
          i, INITIAL_FULL_QUEUE
        )
      );
    }
  }
  /**
   * We assert that all elements have been transferred to the 0th queue.
   */
  assert(block_queues[INITIAL_FULL_QUEUE].size() == B);
}

void distribute_evenly() {
  int full_queue = INITIAL_FULL_QUEUE;
  int empty_queue = INITIAL_EMPTY_QUEUE;
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
  while (block_queues[full_queue].size() != 0) {
    /**
     * Each iteration goes through all the elements in the full queue.
     * In every iteration below atleast K elements will be processed.
     * More elements may be processed if the elements appear in ascending order. But that's for later.
     */
    while(block_queues[full_queue].size() != 0) {
      int block = block_queues[full_queue].front(); // The current element which is being processed
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
        (block_queues[queue_index].size() == 0 && block == queue_bucket + 1)
        || (block_queues[queue_index].size() > 0 && block == block_queues[queue_index].back() + K)
      ) {
        block_queues[queue_index].push(block);
        solution.push_back(
          make_pair(
            full_queue, queue_index
          )
        );
      } else {
        block_queues[empty_queue].push(block);
        solution.push_back(
          make_pair(
            full_queue, empty_queue
          )
        );
      }
      block_queues[full_queue].pop();
    }
    swap(empty_queue, full_queue);
  }
  /**
   * At the end of the process, both INITIAL queues must be empty.
   */
  assert(block_queues[INITIAL_FULL_QUEUE].size() == 0 && block_queues[INITIAL_EMPTY_QUEUE].size() == 0);
}

/**
 * Sort all the queue back to the empty queue.
 */
void sort_the_queues() {
  assert(block_queues[INITIAL_EMPTY_QUEUE].size() == 0);
  assert(block_queues[INITIAL_FULL_QUEUE].size() == 0);
  int empty_queue = INITIAL_FULL_QUEUE;
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
      if (block_queues[i].size() != 0) {
        block_queues[empty_queue].push(block_queues[i].front()); // Add it to the empty queue
        assert(block_queues[i].front() == total + 1);
        block_queues[i].pop(); // Remove it from the current queue
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
  assert(block_queues[empty_queue].size() == B);
}

void verify_solution() {
  // Assert that the solution size is also withing bounds
  assert(B < 1024 || solution.size() <= (B * B) / 2);
  // Doing the same operations as given in the solution in the copy queues that we have made
  for (auto move: solution) {
    assert((move.first < N) && (move.second < N));
    // You cannot push and pop to the same container. Verify this you idiot.
    assert(move.first != move.second);
    // Asserting we are not popping from an empty queue.
    assert(copy_queue[move.first].size() > 0);
    copy_queue[move.second].push(
      copy_queue[move.first].front()
    );
    copy_queue[move.first].pop();
  }
  // Now that we have done the Q operations, then we verify that it yielded that solution that we wanted
  int full_queue = -1;
  int num_empty_queue = 0;
  for (int i = 0; i < N; i++) {
    if (block_queues[i].size() != 0) {
      full_queue = i;
    } else {
      num_empty_queue += 1;
    }
  }
  // At the end, there should be atleast one full queue
  assert(full_queue != -1);
  // At the end there should be exactly N - 1 empty queues
  assert(num_empty_queue == N - 1);
  // The full queue should contain exactly B elements
  assert(copy_queue[full_queue].size() == B);
  // The B elements in the queue should be in sorted order from 1 to B
  int i = 1;
  while(copy_queue[full_queue].size() != 0) {
    assert(copy_queue[full_queue].front() == i);
    copy_queue[full_queue].pop();
    i += 1;
  }
  // Assert that the last element that we saw was B
  assert(i == B + 1);
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
