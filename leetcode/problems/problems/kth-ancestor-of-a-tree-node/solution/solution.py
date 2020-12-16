class TreeAncestor:
    def __init__(self, n, parent):
        # Constructing the tree
        self.tree = [[] for _ in range(n)]
        for dest, src in enumerate(parent):
            if src != -1:
                self.tree[src].append(dest)

        # Storing a small subset of ancestors for each node
        self.ancestors = [[] for _ in range(n)]

        self.populate_ancestors(0, [0])

    def populate_ancestors(self, root, stack):
        i = 1
        ancestor_index = 0
        while ancestor_index < len(stack):
            self.ancestors[root].append(stack[-1 * ancestor_index - 1])
            ancestor_index = pow(2, i - 1)
            i += 1

        for child in self.tree[root]:
            stack.append(child)
            self.populate_ancestors(child, stack)
            stack.pop()


    def getKthAncestor(self, node, k):
        try:
            ancestor = node
            k_binary = "{0:b}".format(k)
            i = 1
            for digit in k_binary:
                if digit == "1":
                    ancestor = self.ancestors[ancestor][len(k_binary) - i + 1]
                i += 1
            return ancestor
        except:
            return -1

if __name__ == "__main__":
    treeAncestor = TreeAncestor(18, [-1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 15, 16])
    print(treeAncestor.getKthAncestor(17, 1))
    print(treeAncestor.getKthAncestor(17, 2))
    print(treeAncestor.getKthAncestor(17, 3))
    print(treeAncestor.getKthAncestor(17, 4))
    print(treeAncestor.getKthAncestor(17, 5))
    print(treeAncestor.getKthAncestor(17, 7))
