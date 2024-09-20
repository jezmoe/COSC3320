import heapq
from collections import Counter


class Tree:
    def __init__(self, ch, freq, left=None, right=None):
        """
        takes a character and its frequency and creates a tree

        :param ch: character
        :param freq: frequency of the character
        :param left: left child
        :param right: right child
        """
        self.ch = ch
        self.freq = freq
        self.left = left
        self.right = right

    def __lt__(self, other):
        """returns true if frequency of current node is less than other node"""
        return self.freq < other.freq

    def display(self):
        lines, *_ = self._display_aux()
        for line in lines:
            print(line)

    def _display_aux(self):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child.
        if self.right is None and self.left is None:
            line = "%s" % self.freq + str((":" + self.ch) if self.ch else "")
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child.
        if self.right is None:
            lines, n, p, x = self.left._display_aux()
            s = "%s" % self.freq
            u = len(s)
            first_line = (x + 1) * " " + (n - x - 1) * "_" + s
            second_line = x * " " + "/" + (n - x - 1 + u) * " "
            shifted_lines = [line + u * " " for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child.
        if self.left is None:
            lines, n, p, x = self.right._display_aux()
            s = "%s" % self.freq
            u = len(s)
            first_line = s + x * "_" + (n - x) * " "
            second_line = (u + x) * " " + "\\" + (n - x - 1) * " "
            shifted_lines = [u * " " + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children.
        left, n, p, x = self.left._display_aux()
        right, m, q, y = self.right._display_aux()
        s = "%s" % self.freq
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


def build_tree(text):
    # count the frequency of each character
    counter = Counter(text)
    pq = [Tree(ch, counter[ch]) for ch in counter]
    # create a heap priority queue
    heapq.heapify(pq)
    # keep taking the smallest two nodes and merging them into a parent node
    # whose frequency is the sum of the two children and add it back to heap
    while len(pq) > 1:
        left = heapq.heappop(pq)
        right = heapq.heappop(pq)
        parent = Tree(None, left.freq + right.freq, left, right)
        heapq.heappush(pq, parent)
    return heapq.heappop(pq)


def build_map(root):
    """
    maps each character to its binary encoding

    :param root: root of the tree
    """

    def dfs(root, code, encoding_map):
        """
        performs a depth first search on the tree and maps each
        character to its binary encoding

        :param root: root of the tree
        :param code: the code written so far
        :param encoding_map: the encoding map
        """
        if root.ch:
            encoding_map[root.ch] = "".join(code)
        else:
            code.append("0")
            dfs(root.left, code, encoding_map)
            code.pop()
            code.append("1")
            dfs(root.right, code, encoding_map)
            code.pop()

    encoding_map = {}
    dfs(root, [], encoding_map)
    return encoding_map


def encode(text):
    """encode the text using huffman encoding"""
    root = build_tree(text)
    encoding_map = build_map(root)
    # create set of text
    # text_set = set(text)
    # sort the set
    # text_set = sorted(text_set)
    # for ch in text_set:
    # print(f"{ch}: {encoding_map[ch]}")
    return "".join([encoding_map[ch] for ch in text])


# print each character and its binary encoding
def print_encoding_map(text):
    map = get_encoding_map(text)
    for ch in map:
        print(f"{ch}: {map[ch]}")


# returns the length of the binary encoding of each character times the frequency
def get_encoding_length(text):
    map = get_encoding_map(text)
    # a dictionary of the characters and their binary encoding lengths
    encoding_length = {}
    for ch in map:
        encoding_length[ch] = len(map[ch])
    # sort the dictionary
    encoding_length = sorted(encoding_length.items())
    # a dictionary of the characters and their frequencies
    char_freq = {}
    for ch in text:
        if ch in char_freq:
            char_freq[ch] += 1
        else:
            char_freq[ch] = 1
    return sorted(map.items()), encoding_length, char_freq


def get_encoding_map(text):
    root = build_tree(text)
    return build_map(root)


def decode(encoded, root):
    """
    decodes the encoded text by traversing the tree
    using the binary encoding as a guide

    :param encoded: the encoded text
    :param root: the root of the tree
    """
    if root.ch:
        return root.ch * len(encoded)
    decoded = []
    node = root
    for bit in encoded:
        if bit == "0":
            node = node.left
        else:
            node = node.right
        if node.ch:
            decoded.append(node.ch)
            node = root
    return "".join(decoded)


# takes the dictionary of characters and their frequencies
# and creates a string of the characters repeated the number of times
def generate_string(char_freq):
    text = ""
    for ch in char_freq:
        text += ch * char_freq[ch]
    return text


# # print a visual representation of the tree
# def print_tree(root, level=0):
#     if root:
#         print_tree(root.right, level + 1)
#         print(
#             " " * 4 * level + str(root.freq) + str((":" + root.ch) if root.ch else "")
#         )
#         print_tree(root.left, level + 1)


# a function to unpack the tuple and print the data into a table
def print_table(map, encoding_length, char_freq):
    print("Character\tBinary  \tLength\tFrequency")
    for i in range(len(map)):
        print(
            f"{map[i][0]}\t\t{map[i][1]}\t\t{encoding_length[i][1]}\t{char_freq[map[i][0]]}"
        )


# a function to calculate the average length of the binary encoding
def average_length(encoding_length, char_freq):
    total = 0
    for i in range(len(encoding_length)):
        total += encoding_length[i][1] * char_freq[encoding_length[i][0]]
    print(f"total length = sum(length * frequency)")
    print(f"{' ' * len('total length')} = {total}", end="\n\n")
    print(f"average length = total length / total frequency")
    print(f"{' ' * len('average length')} = {total} / {sum(char_freq.values())}")
    # print(f"{total} / {sum(char_freq.values())} = {total / sum(char_freq.values())}")
    return total / sum(char_freq.values())


def main():
    """
    ############## INPUT HERE ##############
    """
    char_freq = {
        "a": 3,
        "b": 3,
        "c": 9,
        "d": 6,
        "e": 14,
        "f": 4,
        "g": 6,
        "h": 9,
        "i": 1,
        "j": 25,
    }

    """
    ############## END INPUT ##############
    """
    text = generate_string(char_freq)

    # encoded = encode(text)
    root = build_tree(text)
    # decoded = decode(encoded, root)

    # sum the values in the dictionary
    denominator = sum(char_freq.values())
    print()
    print(
        f"Integer values in tree are to be interpreted\nas the numerator in x/{denominator}",
        end="\n\n",
    )

    root.display()
    print()

    ln = get_encoding_length(text)

    # unpack the tuple ln
    encoding_map, encoding_length, char_freq = ln
    print_table(encoding_map, encoding_length, char_freq)
    print()
    print(
        f"{' ' * len('average length')} = {average_length(encoding_length, char_freq)}"
    )

    # print(f"Encoded: {encoded}")
    # print(f"Decoded: {decoded}")


if __name__ == "__main__":
    main()