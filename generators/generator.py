import random
import os

def get_array(size, start, end):
    return [random.randint(start, end) for _ in range(size)]

def get_tree(size):
    edges = []
    for i in range(1, size):
        parent = random.randint(0, i - 1)
        edges.append((parent, i))
    return edges

def relabel_tree_nodes(size, edges):
    seq = [i for i in range(size)]
    random.shuffle(seq)
    return [(seq[parent], seq[child]) for parent, child in edges]

def change_indexing(edges, base = 1):
    return [(parent + base, child + base) for parent, child in edges]

def generate_test_case(index, total_cases, file):
    # Fill this up for each question
    pass

def generate_test_files(base_dir, total_cases):
    files = ["in-{0}.txt".format(i) for i in range(total_cases)]
    for index, file in enumerate(files):
        test_file_name = "{0}/inputs/{1}".format(base_dir, file)
        os.makedirs(os.path.dirname(test_file_name), exist_ok=True)
        with open(test_file_name, "w+") as f:
            generate_test_case(index, total_cases, f)

if __name__ == "__main__":
    # Fix a new random seed for every problem
    random.seed(1729)
    total_cases = 10
    # Generate test files
    generate_test_files("intuit/problems/interview/ROBBER-ON-TREE", total_cases)