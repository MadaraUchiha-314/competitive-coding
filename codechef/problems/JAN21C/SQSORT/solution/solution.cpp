#include <cstdio>
#include <cassert>
#include <algorithm>
#include <queue>
#include <stack>
#include <deque>
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
const int STACK = 1, QUEUE = 0;
const int INVALID_COST = -1;
const int INVALID_ELEMENT = -1;

class StackQueue {
  public:
    int N, B, Z;
    deque<int> container[MAX_CONTAINERS];
    vector<int> C, D;
    vector<int> W;
    vector<pair<int, int> > operations;
    vector<int> container_type;
    int operation_costs;
    vector<pair<int, int> > sorted_containers;
    int primary_container, secondary_container;
    vector<bool> is_container_used;
    vector<int> mapped_container_index;
    int total_useful_containers;
    vector<int> initial_container_sizes;
    vector<int> initial_last_element;
    vector<int> buffer_containers;
    int current_buffer_container_index;
  public:
    /**
     * Initialises the StackQueueSort data structure
     * @param N The number of of container
     * @param B The number of blocks
     * @param Z The number of buffer containers
     */
    StackQueue(int N, int B, int Z) {
      this->N = N;
      this->B = B;
      this->Z = Z;
      this->C.resize(N);
      this->D.resize(N);
      this->W.resize(B);
      this->container_type.resize(N);
      this->operation_costs = 0;
      this->is_container_used.resize(N);
      this->mapped_container_index.resize(N);
      this->total_useful_containers = N - Z - 2;
      this->initial_container_sizes.resize(N);
      this->initial_last_element.resize(N);
      this->buffer_containers.resize(Z);
      this->current_buffer_container_index = 0;
    }

    /**
     * Used to initially populate block in container
     * @param index The index of the container
     * @param  block The element to be pushed
     */
    void populate(int index, int block) {
      container[index].push_back(block);
      initial_container_sizes[index] += 1;
      initial_last_element[index] = block;
    }

    /**
     * Adds properties of each container
     * @param index     The index of the container
     * @param pop_cost  The cost of popping an element from this container
     * @param push_cost The cost of pushing an element to this container
     */
    void set_container_properties(int index, int pop_cost, int push_cost) {
      if (pop_cost != INVALID_COST) {
        this->C[index] = pop_cost;
      }
      if (push_cost != INVALID_COST) {
        this->D[index] = push_cost;
      }
    }

    /**
     * Adds properties for each block
     * @param index        The index of the container
     * @param block_weight The weight of each block
     */
    void set_block_properties(int index, int block_weight) {
      W[index] = block_weight;
    }

    /**
     * Sets the container type
     * @param index The index of the container
     * @param type  The type of the container
     */
    void set_container_type(int index, int type) {
      container_type[index] = type;
     }

    int get_container_type(int index) {
      return container_type[index];
    }

    /**
     * Pops an element from the container at given index
     * @param index The index of the container
     */
    void pop(int index) {
      if (container_type[index] == QUEUE) {
        container[index].pop_front();
      } else {
        container[index].pop_back();
      }
    }

    /**
     * Pushes an element to the container at given index
     * @param index The index of the container
     * @param block The block to be pushed
     */
    void push(int index, int block) {
      container[index].push_back(block);
    }

    /**
     * The current element of the container on which an operation can be performed
     * @param  index The index of the container
     * @return       The block
     */
    int current(int index) {
      if (container[index].size() == 0) return INVALID_ELEMENT;
      if (container_type[index] == QUEUE) {
        return container[index].front();
      } else {
        return container[index].back();
      }
    }

    /**
     * The last element of the container
     * @param  index The index of the container
     * @return       The block
     */
    int last(int index) {
      return container[index].back();
    }

    /**
     * Pops the element from the src and pushed it to the dest
     * @param src  The index of the container from where element should be popped
     * @param dest  The index of the container from where the popped element should be pushed
     */
    void pop_push(int src, int dest) {
      assert(src != dest);
      int block = current(src);
      push(dest, block);
      pop(src);
      /**
       * Log the operation which was performed.
       */
      operations.push_back(make_pair(src, dest));
      operation_costs += W[block] * (C[src] + D[dest]);
    }

    /**
     * We sort the containers on the basis of the cost it takes to push and pop into those containers
     */
    void sort_containers_by_costs() {
      for (int i = 0; i < N; i++) {
        sorted_containers.push_back(make_pair(C[i] + D[i], i));
        std::sort(
          sorted_containers.begin(), sorted_containers.end()
        );
      }
    }

    /**
     * We choose the two best working containers as the primary_container and the secondary_container
     */
    void choose_working_containers() {
      primary_container = sorted_containers[0].second;
      secondary_container = sorted_containers[1].second;
      /**
       * When we choose a working container, we also mark them as used.
       */
      is_container_used[primary_container] = true;
      is_container_used[secondary_container] = true;

      /**
       * We will use the primary and secondary containers as stacks.
       */
      container_type[primary_container] = QUEUE;
      container_type[secondary_container] = QUEUE;
      /**
       * We pick Z buffer containers.
       */
      for (int i = 0; i < Z; i++) {
        int next_best_container = sorted_containers[i +  2].second;
        buffer_containers[i] = next_best_container;
        is_container_used[next_best_container] = true;
      }
    }

    /**
     * After we have chosen the primary and secondary containers
     */
    void remap_container_indices() {
      int last_used = -1;
      for (int i = 0; i < total_useful_containers; i++) {
        int j = last_used + 1;
        /**
         * Find the next unused container
         */
        while(is_container_used[j]) {
          j += 1;
        }
        mapped_container_index[i] = j;
        last_used = j;
      }
    }

    /**
     * Gets the container index for a give block
     * @param  block The block
     * @return Index of the container
     */
    int get_container_for_block(int block) {
      int original_container_index = block % total_useful_containers;
      int mapped_index = mapped_container_index[
        original_container_index
      ];
      assert(mapped_index != primary_container);
      assert(mapped_index != secondary_container);
      return mapped_index;
    }

    bool is_eligible_for_buffer_container(int block) {
      return block >= (B / (Z + 1));
    }

    int get_buffer_container_for_block(int block) {
      int buffer_container_capacity = B / (Z + 1);
      int buffer_container_index = min(
        block / buffer_container_capacity,
        Z
      );
      return buffer_containers[buffer_container_index - 1];
    }

    bool can_block_reisde_in_its_container(int block) {
      int container_for_block = get_container_for_block(block);
      if (container[container_for_block].size() > 0) {
        if (last(container_for_block) + total_useful_containers == block) {
          return true;
        } else if (last(container_for_block) == initial_last_element[container_for_block]) {
          if (block == (block % total_useful_containers)) {
            return true;
          } else {
            return false;
          }
        } else {
          return false;
        }
      } else {
        if (block == (block % total_useful_containers)) {
          return true;
        } else {
          return false;
        }
      }
    }

    /**
     * This distributes the blocks evenly among all the containers
     */
    void distribute_blocks() {
      /**
       * We distribute all the blocks to either the buffer_containers if eligible
       * Or their respective containers if eligible
       * Or the primary_container or the secondary_container
       */
      for (int i = 0; i < N; i++) {
        while(initial_container_sizes[i] > 0 && container[i].size() > 0) {
          int block = current(i);
          if (is_eligible_for_buffer_container(block)) {
            int buffer_container_index = get_buffer_container_for_block(
              block
            );
            if (i != buffer_container_index) {
              pop_push(
                i, buffer_container_index
              );
              // debug("Placing block %d in buffer_container %d\n", block, buffer_container_index);
            } else {
              pop_push(i, secondary_container);
            }
          } else if (can_block_reisde_in_its_container(block)) {
            int container_index = get_container_for_block(
              block
            );
            if (i != container_index) {
              pop_push(
                i, container_index
              );
            } else {
              pop_push(
                i, secondary_container
              );
            }
          } else {
            if (i == primary_container) {
              pop_push(i, secondary_container);
            } else {
              pop_push(i, primary_container);
            }
          }
          if (block == initial_last_element[i]) break;
        }
      }
      while(container[secondary_container].size() > 0) {
        int block = current(secondary_container);
        if (is_eligible_for_buffer_container(block)) {
          // debug("Placing block %d in buffer_container %d\n", block, get_buffer_container_for_block(block));
          pop_push(
            secondary_container, get_buffer_container_for_block(block)
          );
        } else {
          pop_push(secondary_container, primary_container);
        }
      }
      /**
       * Now all the blocks are in the primary_container or secondary_container or already in their respective places.
       */
      int current_primary = primary_container, current_secondary = secondary_container;
      while(container[current_primary].size() > 0) {
        int total_blocks_placed = 0;
        while(container[current_primary].size() > 0) {
          int block = current(current_primary);
          if (can_block_reisde_in_its_container(block)) {
            pop_push(current_primary, get_container_for_block(block));
            total_blocks_placed += 1;
          } else {
            pop_push(current_primary, current_secondary);
          }
        }
        swap(current_primary, current_secondary);
        if (total_blocks_placed == 0 || container[current_primary].size() == 0) {
          for (auto buffer_container: buffer_containers) {
            if (container[buffer_container].size() > 0) {
              while(container[buffer_container].size() != 0) {
                pop_push(buffer_container, current_primary);
              }
              break;
            }
          }
        }
      }
      assert(container[primary_container].size() == 0);
      assert(container[secondary_container].size() == 0);
    }

    /**
     * Sorts a given container. All the elements eventually go to the primary container. This uses the secondary container as the buffer.
     * @param index The index of the container
     */
    void sort_containers() {
      int total = 0;
      while(total != B) {
        for (int i = 0; i < N; i++) {
          if (i == primary_container || i == secondary_container) continue;
          if (container[i].size() == 0) continue;
          pop_push(i, primary_container);
          total += 1;
        }
      }
    }

    void sort() {
      /**
       * This is our strategy to sort.
       * 1. Sort the containers baased on their C[i] + D[i] for ith container
       * 2. Choose 2 to be our working containers. Empty them.
       * 3. Now we have K = N - 2 containers
       * 4. For each block, add the ith block to the (i % K)th empty container
       * 5. Now go through each of the filled containers and sort them
       */
      sort_containers_by_costs();
      choose_working_containers();
      remap_container_indices();
      distribute_blocks();
      sort_containers();
    }

    void verify_sorting() {
      int total_empty = 0, total_full = 1;
      int full_container_index = -1;
      assert(operations.size() <= (B*B)/2);
      for (int i = 0; i < N; i++) {
        if (container[i].size() > 0) {
          total_full += 1;
          full_container_index = i;
        } else {
          total_empty += 1;
        }
      }
      assert(total_empty == N - 1);
      assert(total_full = 1);
      int current_block = 0, increment = 1, last_block = B;
      if (container_type[full_container_index] == STACK) {
        current_block = B - 1;
        increment = -1;
        last_block = -1;
      }
      while (container[full_container_index].size() > 0) {
        int block = current(full_container_index);
        assert(block == current_block);
        pop(full_container_index);
        current_block += increment;
      }
      assert(current_block == last_block);
    }
};

int main() {
  /**
   * Start of input.
   */
  int N, B, C, D, W, M, A;
  scanf("%d %d", &N, &B);
  StackQueue sq(N, B, 2);
  for (int i = 0; i < N; i++) {
    scanf("%d", &C);
    sq.set_container_properties(i, C, INVALID_COST);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &D);
    sq.set_container_properties(i, INVALID_COST, D);
  }
  for (int i = 0; i < B; i++) {
    scanf("%d", &W);
    sq.set_block_properties(i, W);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &M);
    for (int j = 0; j < M; j++) {
      scanf("%d", &A);
      sq.populate(i, A - 1);
    }
  }
  /**
   * End of input.
   */
  sq.sort();
  sq.verify_sorting();
  for (int i = 0; i < N; i++) {
    if (sq.get_container_type(i) == QUEUE) {
      printf("Q");
    } else {
      printf("S");
    }
  }
  printf("\n");
  printf("%lu\n", sq.operations.size());
  for (auto op: sq.operations) {
    printf("%d %d\n", op.first + 1, op.second + 1);
  }
}
