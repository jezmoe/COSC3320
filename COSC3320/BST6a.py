class BstNode:
    def __init__(self, key):
        self.key = key
        self.right = None
        self.left = None

    def insert(self, key):
        if self.key == key:
            return
        elif self.key < key:
            if self.right is None:
                self.right = BstNode(key)
            else:
                self.right.insert(key)
        else:  # self.key > key
            if self.left is None:
                self.left = BstNode(key)
            else:
                self.left.insert(key)

    # delete function
    def delete(self, key):
        if self.key == key:
            if self.left is None and self.right is None:
                return None
            elif self.left is None:
                return self.right
            elif self.right is None:
                return self.left
            else:
                min_node = self.right
                while min_node.left is not None:
                    min_node = min_node.left
                self.key = min_node.key
                self.right = self.right.delete(min_node.key)
        elif self.key < key:
            self.right = self.right.delete(key)
        else:
            self.left = self.left.delete(key)
        return self

    def display(self):
        lines, *_ = self._display_aux()
        for line in lines:
            print(line)

    def _display_aux(self):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child.
        if self.right is None and self.left is None:
            line = "%s" % self.key
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child.
        if self.right is None:
            lines, n, p, x = self.left._display_aux()
            s = "%s" % self.key
            u = len(s)
            first_line = (x + 1) * " " + (n - x - 1) * "_" + s
            second_line = x * " " + "/" + (n - x - 1 + u) * " "
            shifted_lines = [line + u * " " for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child.
        if self.left is None:
            lines, n, p, x = self.right._display_aux()
            s = "%s" % self.key
            u = len(s)
            first_line = s + x * "_" + (n - x) * " "
            second_line = (u + x) * " " + "\\" + (n - x - 1) * " "
            shifted_lines = [u * " " + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children.
        left, n, p, x = self.left._display_aux()
        right, m, q, y = self.right._display_aux()
        s = "%s" % self.key
        u = len(s)
        first_line = (x + 1) * " " + (n - x - 1) * "_" + s + y * "_" + (m - y) * " "
        second_line = (
            x * " " + "/" + (n - x - 1 + u + y) * " " + "\\" + (m - y - 1) * " "
        )
        if p < q:
            left += [n * " "] * (q - p)
        elif q < p:
            right += [m * " "] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * " " + b for a, b in zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2


def step1(lst, root):
    for num in lst:
        print("-" * 20)
        print("Inserting", num)
        if root is None:
            root = BstNode(num)
        else:
            root.insert(num)
        root.display()
        # print("-" * 20)
    return root


def step2(lst, root):
    for num in lst:
        print("-" * 20)
        print("Deleting", num)
        root = root.delete(num)
        root.display()
        # print("\n")


"""
################ INPUT HERE ################
"""
# modify insert_list as needed
insert_list = [6, 7, 8, 9, 0, 1, 2, 4, 5, 3]
# modify delete_list as needed
delete_list = [6, 8, 2, 5, 3]
"""
############################################
"""


root = None
print()
print("(a) Insert:", insert_list, "\n")
root = step1(insert_list, root)
print("-" * 20, end="\n\n")
print("(b) Delete:", delete_list, "\n")
root = step2(delete_list, root)