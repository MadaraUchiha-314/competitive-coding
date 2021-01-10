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
    int N, B;
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
    int useful_container_capacity;
    vector<int> initial_container_sizes;
    vector<int> initial_last_element;
  public:
    /**
     * Initialises the StackQueueSort data structure
     * @param N The number of of container
     * @param B The number of blocks
     */
    StackQueue(int N, int B) {
      this->N = N;
      this->B = B;
      this->C.resize(N);
      this->D.resize(N);
      this->W.resize(B);
      this->container_type.resize(N);
      this->operation_costs = 0;
      this->is_container_used.resize(N);
      this->mapped_container_index.resize(N);
      this->total_useful_containers = N - 2;
      this->initial_container_sizes.resize(N);
      this->initial_last_element.resize(N);
      this->useful_container_capacity = max(1, B / (N - 2));
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
      secondary_container = sorted_containers[0].second;
      primary_container = sorted_containers[1].second;
      /**
       * When we choose a working container, we also mark them as used.
       */
      is_container_used[primary_container] = true;
      is_container_used[secondary_container] = true;

      /**
       * We will use the primary and secondary containers as stacks.
       */
      container_type[primary_container] = STACK;
      container_type[secondary_container] = QUEUE;
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
      int original_container_index = block / (int)useful_container_capacity;
      int mapped_index = mapped_container_index[
        min(
          original_container_index,
          N - 3
        )
      ];
      return mapped_index;
    }

    /**
     * This distributes the blocks evenly among all the containers
     */
    void distribute_blocks() {
      /**
       * Now we will empty the primary container.
       */
      while(container[primary_container].size() != 0) {
        pop_push(
          primary_container,
          get_container_for_block(
            current(primary_container)
          )
        );
      }
      assert(container[primary_container].size() == 0);
      /**
       * For every other container, we will empty them and put the blocks in their appropriate places.
       */
      for (int i = 0; i < N; i++) {
        while(initial_container_sizes[i] > 0 && container[i].size() > 0) {
          int block = current(i);
          int dest = get_container_for_block(block);
          /**
           * There are 2 cases here. Each container can either go into its own block or into another block.
           * If its the former case, then we need one extra operation to push it to the primary container and then pop it to its actual container.
           */
          if (dest == i) {
            pop_push(i, primary_container);
            pop_push(primary_container, dest);
          } else {
            pop_push(i, dest);
          }
          /**
           * Some blocks may have come into the queue because of our operations. We don't want to apply the operations on them.
           * @param block [description]
           */
          if (block == initial_last_element[i]) {
            break;
          }
        }
      }
    }

    /**
     * Sorts a given container. All the elements eventually go to the primary container. This uses the secondary container as the buffer.
     * @param index The index of the container
     */
    void sort_container(int index) {
      int from = index, to = secondary_container;
      while(container[from].size() > 0) {
        while(container[from].size() > 0) {
          int block = current(from);
          if (current(primary_container) == block - 1) {
            pop_push(from, primary_container);
          } else {
            pop_push(from, to);
          }
        }
        swap(from, to);
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
      for(int i = 0; i < N; i++) {
        if (i == primary_container || i == secondary_container) continue;
        if (container[i].size() > 0) {
          sort_container(i);
        }
      }
    }

    void verify_sorting() {
      int total_empty = 0, total_full = 1;
      int full_container_index = -1;
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
      int current_block = B - 1;
      while (container[full_container_index].size() > 0) {
        int block = current(full_container_index);
        pop(full_container_index);
        assert(block == current_block);
        current_block -= 1;
      }
      assert(current_block == -1);
    }
};

int main() {
  /**
   * Start of input.
   */
  int N, B, C, D, W, M, A;
  scanf("%d %d", &N, &B);
  StackQueue sq(N, B);
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
