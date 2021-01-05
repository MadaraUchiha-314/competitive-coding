#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
using namespace std;

#define DEBUG 1

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
vector<pair<int ,int> > sorted_containers;
vector<int> buffer_containers;
int used_containers[MAX_CONTAINERS];
vector<pair<int, int> > solution;

/**
 * Buffer container is a container where we keep our "inactive" blocks which which come into the picture only during latter iterations.
 */
int num_buffer_containers = 1;

int primary_container = 0;
int secondary_container = 1;


/**
 * Forward declaration of stuff.
 */
void input();
void verify_solution();
void print_solution();

/**
 * Sorts the containers based on the heuristic of the smalled C[i] + D[i] for each container.
 */
void sort_containers_based_on_heuristic() {
  for (int i = 0; i < N; i++) {
    sorted_containers.push_back(
      make_pair(
        C[i] + D[i],
        i
      )
    );
  }
  sort(sorted_containers.begin(), sorted_containers.end());
}

/**
 * We choose the best 2 containers for as the "working" containers and the rest as the buffer/inactive containers.
 */
void choose_fixed_containers() {
  /**
   * The below 2 will be our initial working containers.
   */
  primary_container = sorted_containers[0].second;
  secondary_container = sorted_containers[1].second;

  used_containers[sorted_containers[0].second] = 1; // Mark as used
  used_containers[sorted_containers[1].second] = 1; // Mark as used
  /**
   * We maintain a separate list for buffer_containers.
   */
  for (int i = 0; i < num_buffer_containers; i++) {
    buffer_containers.push_back(sorted_containers[i + 2].second);
    used_containers[sorted_containers[i + 2].second] = 1; // Mark as used
  }
  debug("Buffer containers are: \n");
  for (auto container: buffer_containers) {
    debug("%d ", container);
  }
  debug("\n");
}

bool is_elibigle_for_buffer_container(int block) {
  debug("Block %d eligibility %d\n", block, block > (B / (num_buffer_containers + 1)));
  return block > (B / (num_buffer_containers + 1));
}

int get_buffer_container_for_block(int block) {
  int total_capacity = B / (num_buffer_containers + 1);
  int buffer_container_index = (block - 1)/ total_capacity;
  debug("Buffer container index %d\n", buffer_container_index);
  fflush(stdout);
  return buffer_containers[buffer_container_index - 1];
}

/**
 * We transfer all the blocks from all the containers to two places.
 * 1. primary_container
 * 2. One of the buffer_containers based on the value of the block.
 */
void transfer_blocks_to_containers() {
  /**
   * We determine the upper limit for the working group.
   * The rest of the blocks will go to one of the buffer containers.
   */
  int working_block_upper_limit = B / (num_buffer_containers + 1);
  /**
   * Before we do all the transfer.
   * We can transfer temporarily inactive blocks from the primary_container to the buffer_containers if required.
   */
  debug("Preparing to clear everything from primary container %d\n", primary_container);
  while(container[primary_container].size() != 0) {
    int block = container[primary_container].front();
    debug("Clearing block %d from primary container\n", block);
    if (!is_elibigle_for_buffer_container(block)) {
      /**
       * In this case, literally we have no where to push it to.
       * So we push it to secondary_container.
       */
      container[secondary_container].push(block);
      container[primary_container].pop();
      debug("Added block %d to secondary container %d\n", block, secondary_container);
      /**
       * Add it to the solution.
       */
      solution.push_back(
        make_pair(
          primary_container, secondary_container
        )
      );
    } else {
      /**
       * We push it to one of the buffer containers.
       */
      int buffer_container = get_buffer_container_for_block(block);
      container[buffer_container].push(block);
      container[primary_container].pop();
      debug("Added block %d to buffer container %d\n", block, buffer_container);
      /**
       * Add it to the solution.
       */
      solution.push_back(
        make_pair(
          primary_container, buffer_container
        )
      );
    }
  }
  /**
   * We do the same for our buffer containers also.
   * We put all the buffer container stuff in the secondary conatiner.
   */
  for (int i = 0; i < buffer_containers.size(); i++) {
    int buffer_container = buffer_containers[i];
    debug("Preparing to clear everything from buffer container %d\n", buffer_container);
    while(container[buffer_containers[i]].size() != 0) {
      int block = container[buffer_container].front();
      debug("Clearing block %d from primary container\n", block);
      container[secondary_container].push(block);
      container[buffer_container].pop();
      debug("Added block %d to secondary container %d\n", block, secondary_container);
      /**
       * Add it to the solution.
       */
      solution.push_back(
        make_pair(
          buffer_container, secondary_container
        )
      );
    }
  }
  for (int i = 0; i < N; i++) {
    if (used_containers[i] != 0) continue;
    debug("Preparing to clear everything from normal container %d\n", i);
    while(container[i].size() != 0) {
      int block = container[i].front();
      debug("Clearing block %d from normal container\n", block);
      if (!is_elibigle_for_buffer_container(block)) {
        /**
         * Remove it from the current container and add it to the primary_container
         */
        container[primary_container].push(block);
        container[i].pop();
        debug("Added block %d to primary container %d\n", block, primary_container);
        /**
         * Add it to the solution.
         */
        solution.push_back(
          make_pair(
            i, primary_container
          )
        );
      } else {
        int buffer_container = get_buffer_container_for_block(block);
        container[buffer_container].push(block);
        container[i].pop();
        debug("Added block %d to buffer container %d\n", block, buffer_container);
        /**
         * Add it to the solution.
         */
        solution.push_back(
          make_pair(
            i, buffer_container
          )
        );
      }
    }
  }
  // Asserts!!
  for (int i = 0; i < N; i++){
    if (used_containers[i] != 1) {
      assert(container[i].size() == 0);
    } else {
      debug("Used Container Size is %lu\n", container[i].size());
    }
  }
}

void solve() {
  sort_containers_based_on_heuristic();
  fflush(stdout);
  choose_fixed_containers();
  fflush(stdout);
  transfer_blocks_to_containers();
}

int main() {
  input();
  solve();
  // verify_solution();
  // print_solution();
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
