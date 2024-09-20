def complete_extended_euclidean(a, m):
    old_r, r = a, m
    old_s, s = 1, 0
    old_t, t = 0, 1
    
    euclidean_graph = [{'a_i': old_r, 'x_i': old_s, 'y_i': old_t, 'q_i': ''}]
    
    while r != 0:
        quotient = old_r // r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t
        euclidean_graph.append({'a_i': old_r, 'x_i': old_s, 'y_i': old_t, 'q_i': quotient})
    
    # Add the last row where r is 0 if it's not already there
    if euclidean_graph[-1]['a_i'] != 0:
        euclidean_graph.append({'a_i': 0, 'x_i': s, 'y_i': t, 'q_i': old_r // m})
    
    return euclidean_graph

# Given numbers
a = 93765
m = 524288

# Compute the complete extended Euclidean algorithm graph for the given numbers
complete_graph = complete_extended_euclidean(a, m)

# Output the complete graph
for row in complete_graph:
    print(f"a_i: {row['a_i']}, x_i: {row['x_i']}, y_i: {row['y_i']}, q_i: {row['q_i']}")

# Extract the second last row which contains the multiplicative inverse before the remainder became 0
if complete_graph[-2]['a_i'] == 1:
    inverse = complete_graph[-2]['x_i'] % m
    print(f"The multiplicative inverse of {a} modulo {m} is {inverse}")
else:
    print("No multiplicative inverse exists.")

print( "DONT USE THE ZERO a_i: 0 LINE")