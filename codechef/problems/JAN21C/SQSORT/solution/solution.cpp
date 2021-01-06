#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
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
vector<pair<int ,int> > sorted_containers;
vector<int> buffer_containers;
int used_containers[MAX_CONTAINERS];
vector<pair<int, int> > solution;
int container_index_mapping[MAX_CONTAINERS];

/**
 * Buffer container is a container where we keep our "inactive" blocks which which come into the picture only during latter iterations.
 */
int num_buffer_containers = 2;

int primary_container = 0;
int secondary_container = 1;


/**
 * Forward declaration of stuff.
 */
void input();
void verify_solution();
void print_solution();
void print_containers();
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

  debug("============\n");
  debug("Total Containers are %d\n", N);
  debug("Primary container Index is %d\n", primary_container);
  debug("Secondary container Index is %d\n", secondary_container);
  /**
   * We maintain a separate list for buffer_containers.
   */
  for (int i = 0; i < num_buffer_containers; i++) {
    buffer_containers.push_back(sorted_containers[i + 2].second);
    used_containers[sorted_containers[i + 2].second] = 1; // Mark as used
    debug("Buffer container Index is %d\n", sorted_containers[i + 2].second);
  }
  debug("============\n");
}

inline bool is_elibigle_for_buffer_container(int block) {
  return block > (B / (num_buffer_containers + 1));
}

inline int get_buffer_container_for_block(int block) {
  int total_capacity = B / (num_buffer_containers + 1);
  int buffer_container_index = min(
    (int)buffer_containers.size(),
    (block - 1) / total_capacity
  );
  return buffer_containers[buffer_container_index - 1];
}

inline int get_useful_containers() {
  return N - (int)buffer_containers.size() - 2;
}

inline int get_container_for_block(int block) {
  int total_usable_containers = get_useful_containers();
  int container_index = (block - 1) % total_usable_containers;
  return container_index_mapping[container_index];
}

inline int first_element_in_container_for_block(int block) {
  return ((block - 1) % get_useful_containers()) + 1;
}

void determine_container_index_mapping() {
  int last_used = -1;
  for(int i = 0; i < N; i++) {
    int j = i;
    while(j <= last_used || used_containers[j] == 1) {
      j += 1;
    }
    container_index_mapping[i] = j;
    last_used = j;
  }
}

/**
 * We transfer all the blocks from all the containers to two places.
 * 1. primary_container
 * 2. One of the buffer_containers based on the value of the block.
 */
void transfer_blocks_to_initial_containers() {
  /**
   * Before we do all the transfer.
   * We can transfer temporarily inactive blocks from the primary_container to the buffer_containers if required.
   */
  while(container[primary_container].size() != 0) {
    int block = container[primary_container].front();
    debug("Transferring Block %d from primary container %d to secondary container %d\n", block, primary_container, secondary_container);
    /**
     * In this case, literally we have no where to push it to.
     * So we push it to secondary_container.
     */
    container[secondary_container].push(block);
    container[primary_container].pop();
    /**
     * Add it to the solution.
     */
    solution.push_back(
      make_pair(
        primary_container, secondary_container
      )
    );
  }
  /**
   * We do the same for our buffer containers also.
   * We put all the buffer container stuff in the secondary conatiner.
   */
  for (int i = 0; i < buffer_containers.size(); i++) {
    int buffer_container = buffer_containers[i];
    while(container[buffer_containers[i]].size() != 0) {
      int block = container[buffer_container].front();
      debug("Transferring block %d from buffer to secondary\n", block);
      container[secondary_container].push(block);
      container[buffer_container].pop();
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
  swap(primary_container, secondary_container);
  debug("Primary container Index is %d\n", primary_container);
  debug("Secondary container Index is %d\n", secondary_container);
  print_containers();
  for (int i = 0; i < N; i++) {
    if (used_containers[i] != 0) continue;
    debug("Working on container %d\n", i);
    while(container[i].size() != 0) {
      int block = container[i].front();
      if (!is_elibigle_for_buffer_container(block)) {
        debug("Transferring Block %d from container %d to primary_container container %d\n", block, i, primary_container);
        debug("Size of container %d is %lu\n", i, container[i].size());
        /**
         * Remove it from the current container and add it to the primary_container
         */
        container[primary_container].push(block);
        container[i].pop();
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
        debug("Transferring Block %d from container %d to buffer_container container %d\n", block, i, buffer_container);
        container[buffer_container].push(block);
        container[i].pop();
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
  debug("============\n");
  for (int i = 0; i < N; i++) {
    debug("Container %d size is %lu\n", i, container[i].size());
  }
  debug("============\n");
}

/**
 * Now we will transfer each block their respective containers.
 */
void transfer_blocks_to_respective_containers() {
  int total = 0;
  while(total != B) {
    // debug("Total Blocks Placed %d\n", total);
    int found_useful_block =  0;
    while(container[primary_container].size() > 0) {
      int block = container[primary_container].front();
      int block_mapped_container = get_container_for_block(block);
      debug("Processing Block %d\n", block);
      if (container[block_mapped_container].size() > 0) {
        int previous_block = container[block_mapped_container].back();
        if (previous_block + get_useful_containers() == block) {
          container[block_mapped_container].push(block);
          container[primary_container].pop();
          /**
           * Add it to the solution.
           */
          solution.push_back(
            make_pair(
              primary_container, block_mapped_container
            )
          );
          found_useful_block += 1;
          total += 1;
        } else {
          container[secondary_container].push(block);
          container[primary_container].pop();
          /**
           * Add it to the solution.
           */
          solution.push_back(
            make_pair(
              primary_container, secondary_container
            )
          );
        }
      } else {
        if (block == first_element_in_container_for_block(block)) {
          container[block_mapped_container].push(block);
          container[primary_container].pop();
          /**
           * Add it to the solution.
           */
          solution.push_back(
            make_pair(
              primary_container, block_mapped_container
            )
          );
          total += 1;
          found_useful_block += 1;
        } else {
          container[secondary_container].push(block);
          container[primary_container].pop();
          /**
           * Add it to the solution.
           */
          solution.push_back(
            make_pair(
              primary_container, secondary_container
            )
          );
        }
      }
    }
    if (found_useful_block == 0) {
      for (auto buffer_container: buffer_containers) {
        if (container[buffer_container].size() > 0 ) {
          while(container[secondary_container].size() != 0) {
            int block = container[secondary_container].front();
            container[buffer_container].push(block);
            container[secondary_container].pop();
            /**
             * Add it to the solution.
             */
            solution.push_back(
              make_pair(
                secondary_container, buffer_container
              )
            );
          }
          primary_container = buffer_container;
          assert(container[secondary_container].size() == 0);
          assert(container[primary_container].size() != 0);
          break;
        }
      }
    } else {
      swap(primary_container, secondary_container);
    }
  }
}

void sort_containers() {
  primary_container = container[primary_container].size() == 0 ? primary_container : secondary_container;
  assert(container[primary_container].size() == 0);
  int total = 0;
  while(total < B) {
    for (int i = 0; i < N; i++) {
      if (i == primary_container) continue;
      if (container[i].size() > 0) {
        int block = container[i].front();
        assert(block == total + 1);
        container[primary_container].push(block);
        container[i].pop();
        /**
         * Add it to the solution.
         */
        solution.push_back(
          make_pair(
            i, primary_container
          )
        );
        total += 1;
      }
    }
  }
}

void solve() {
  sort_containers_based_on_heuristic();
  debug("Sorting based on heuristic complete\n");
  debug("============\n");
  print_containers();
  choose_fixed_containers();
  debug("Choosing fixed contaiers complete\n");
  debug("============\n");
  transfer_blocks_to_initial_containers();
  debug("Transferred blocks to initial container\n");
  debug("============\n");
  determine_container_index_mapping();
  debug("Determined container index mappings\n");
  debug("============\n");
  transfer_blocks_to_respective_containers();
  debug("Transferrign blocks to respective containers\n");
  debug("============\n");
  sort_containers();
  debug("Sorting containers\n");
  debug("============\n");
}

int main() {
  input();
  solve();
  // verify_solution();
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

void print_containers() {
  for(int i = 0; i < N; i++) {
    debug("Container %d size is %lu\n", i, container[i].size());
    if (container[i].size() > 0) {
      debug("Front is %d\n", container[i].front());
    }
  }
}
