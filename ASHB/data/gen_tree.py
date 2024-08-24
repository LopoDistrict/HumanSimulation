
class TreeNode:
    def __init__(self, value, children=[]):
        self.value = value
        self.children = children

    def add_child(self, child):
        self.children.append(child)

    def print_leaf_nodes(self):
        if not self.children:
            print(self.value)
        else:
            for child in self.children:
                child.print_leaf_nodes()

    def get_parents(self):
        parents = []
        current_node = self
        while current_node.parent:
            parents.append(current_node.parent.value)
            current_node = current_node.parent
        return parents

    def get_sons(self):
        sons = []
        for child in self.children:
            sons.append(child.value)
        return sons

    def print_tree(self, level=0):
        print("  " * level + "|__" + str(self.value))
        for child in self.children:
            child.print_tree(level + 1)


