#!/usr/bin/python

import sys
import copy
import math
from collections import OrderedDict

if len(sys.argv) != 2:
    sys.exit('usage: ./the4_tester.py <CASE INDEX>')

inputs = [['root',3],
          ["root",["1",["2",["3",["4",["5",["6",["7",["8",["9",1]]]]]]]]]],
          ['r|r', ['a%a', ['c#c', 1], ['d!d', 2], ['e&e', ['i,i', 4], ['j.j', 5]]], ['b;b', ['f:f', 5], ['g$g', 5], ['h^g', 4]]],
          ['r', ['a', ['c', 1], ['d', 2], ['e', ['i', 5], ['j', 5]]], ['b', ['f', 5], ['g', 5], ['h', 4]]],
          ['r', ['a', ['c', 1], ['d', 2], ['e', ['i', 5], ['j', 5]]], ['b', ['f', 5], ['g', 5], ['h', 5]]],
          ['r', ['a', ['c', 1], ['d', 2], ['e', ['i', 5], ['j', 5]]], ['b', ['f', 5], ['g', 5], ['h', 6]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 3], ['j', 3]]], ['b', ['f', 3], ['g', 3], ['h', 3]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 2], ['j', 3]]], ['b', ['f', 3], ['g', 3], ['h', 3]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 3], ['h', 3]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 6], ['h', 3]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 6], ['h', 3]],['k',['l',100]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 6], ['h', 3]],['k',['l',['m',7]]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 6], ['h', 3]],['k',['l',['m',7]],['n',10]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 6], ['h', 3]],['k',['l',['m',7],['n',10]]]],
          ['r', ['a', ['c', 3], ['d', 3], ['e', ['i', 4], ['j', 3]]], ['b', ['f', 3], ['g', 9], ['h', 3]],['k',['l',['m',7],['n',['o',7]]]]],
          ['r', ['a', ['c', ['p',8]], ['d',13], ['e', ['i', 4], ['j', 13]]], ['b', ['f', 3], ['g', 9], ['h', 3]],['k',['l',['m',7],['n',['o',7]]]]],
          ['r', ['a', ['c', ['p',8]], ['d',13], ['e', ['i', 4], ['j', 13]]], ['b', ['f', 8], ['g', 9], ['h', 3]],['k',['l',['m',7],['n',['o',7]]]]],
          ['r', ['a', ['c', ['p',18]], ['d',13], ['e', ['i', 14], ['j', 13]]], ['b', ['f', 1], ['g', 19], ['h', 23]],['k',['l',['m',17],['n',['o',27]]]]],
          ['r', ['a', ['c', ['p',34]], ['d',33], ['e', ['i', 29], ['j', 29]]], ['b', ['f', 1], ['g', 29], ['h', 35]],['k',['l',['m',17],['n',['o',27]]]]],
          ['r', ['a', ['c', ['p',34]], ['d',33], ['e', ['i', 29], ['j', 29]]], ['b', ['f', 17], ['g', 29], ['h', 33]],['k',['l',['m',27],['n',['o',27]]]]]]

outputs = [[[], [], ['root']],
           [['root']],
           [['c#c'], ['d!d'], [], ['i,i', 'h^g'], ['r|r']],
           [['c'], ['d'], [], ['h'], ['r']],
           [['c'], ['d'], [], [], ['r']],
           [['c'], ['d'], [], [], ['a', 'f', 'g'], ['r']],
           [[], [], ['r']],
           [[], ['i'], ['r']],
           [[], [], ['c', 'd', 'j', 'b'], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], ['b'], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], ['b'], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], ['b'], ['l'], [], [], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], ['b'], ['m'], [], [], ['r']],
           [[], [], ['c', 'd', 'j', 'f', 'h'], ['a'], [], [], ['k'], [], ['r']],
           [[], [], ['f', 'h'], ['i'], [], [], ['k'], ['c'], ['b'], [], [], [], ['r']],
           [[], [], ['h'], ['i'], [], [], ['k'], ['c', 'f'], ['b'], [], [], [], ['r']],
           [['f'], [], [], [], [], [], [], [], [], [], [], [], ['d', 'j'], ['e'], [], [], ['m'], ['a'], ['g'], [], [], [], ['b'], [], [], [], ['r']],
           [['f'], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], ['m'], [], [], [], [], [], [], [], [], [], ['k'], [], ['e', 'g'], [], [], [], ['d'], ['a'], ['r']],
           [[], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], ['f'], [], [], [], [], [], [], [], [], [], ['k'], [], ['e', 'g'], [], [], [], ['d', 'b'], ['r']]]

case = int(sys.argv[1])
case_point = 100.0 / len(inputs)

def leaves_open(leaf_maps):
    for node in leaf_maps.keys():
        if leaf_maps[node]:
            return True
    return False

def is_leaf(tree):
    if not tree:
        return True
    elif len(tree) == 2 and type(tree[1]) == int:
        return True
    else:
        return False

def datum(tree):
    return tree[0]

def children(tree):
    return tree[1:]

def get_leaves(tree):
    if is_leaf(tree):
        return [tree[:]]
    else:
        result = []
        for child in children(tree):
            result += get_leaves(child)
        return result


def get_leaf_maps(tree, dct):
    dct[datum(tree)] = get_leaves(tree)
    if not is_leaf(tree):
        for child in children(tree):
            get_leaf_maps(child,dct)
    return dct

def delete_leaf(owner, leaf, leaf_maps):
    for node in leaf_maps.keys():
        if owner == node:
            continue
        if leaf in leaf_maps[node]:
            leaf_maps[node].remove(leaf)

def delete_leaves(owner, leaves, leaf_maps):
    for leaf in leaves:
        delete_leaf(owner, leaf,leaf_maps)

def decrease_leaves(maps):
    for node in maps.keys():
        for leaf in maps[node]:
            leaf[1] -= 1

def all_done(leaves):
    for leaf in leaves:
        if leaf[1] != 0:
            return False
    return True

def is_it_a_solution(result):
    leaf_maps = get_leaf_maps(inputs[case], OrderedDict())
    t = 0
    while t < len(result):
        if not leaves_open(leaf_maps): # if all leaves is done but there is node in result --> wrong closing.
            return False
        decrease_leaves(leaf_maps)
        for node in result[t]:
            if not all_done(leaf_maps[node]):
                return False
            else:
                delete_leaves(node, leaf_maps[node], leaf_maps)
                del leaf_maps[node]
        t += 1
    return (not leaves_open(leaf_maps)) # if all leaves done then solution is valid

def get_number_of_closing(result):
    closed = 0
    for c_t in result:
        closed += len(c_t)
    return closed

def get_total_valves(tree):
    if not tree:
        return 0
    if is_leaf(tree):
        return 1
    else:
        total = 1
        for child in children(tree):
            total += get_total_valves(child)
        return total 

def calculate_partial(p):
    fp = p % 1
    if fp == 0.0:
        return p
    elif fp > 0.5:
        return math.ceil(p)
    else:
        return math.floor(p) + 0.5
        

with open("result.txt", 'a') as result_file:
    try:
        import the4
        try:
            result = the4.chalchiuhtlicue(copy.deepcopy(inputs[case]))
            if is_it_a_solution(result):
                minimum_closing = get_number_of_closing(outputs[case])
                number_of_closing = get_number_of_closing(result)
                total_valves = get_total_valves(inputs[case])
                if number_of_closing == minimum_closing:
                    result_file.write("CASE " + str(case) + ": [OK] ---> " + str(case_point) + " points\n")
                elif number_of_closing == total_valves: # to eliminate trivial solutions
                    result_file.write("CASE " + str(case) + ": [FAILED] ---> 0 points\n")
                    result_file.write("\tACTUAL:" + str(result) + '\n')
                    result_file.write("\tSAMPLE EXPECTED:" + str(outputs[case]) + '\n') 
                else:
                    partial_point_raw = case_point * ( float(minimum_closing) / number_of_closing ) \
                                        * ( float(minimum_closing) / total_valves )
                    partial_point = calculate_partial(partial_point_raw)
                    result_file.write("CASE " + str(case) + ": [PARTIAL] ---> " + str(partial_point) + " points\n")
                    result_file.write("\tACTUAL:" + str(result) + '\n')
                    result_file.write("\tSAMPLE EXPECTED:" + str(outputs[case]) + '\n') 
            else:
                result_file.write("CASE " + str(case) + ": [FAILED] ---> 0 points\n")
                result_file.write("\tACTUAL:" + str(result) + '\n')
                result_file.write("\tSAMPLE EXPECTED:" + str(outputs[case]) + '\n')    
        except Exception as e:
            result_file.write("CASE " + str(case) + ": [FAILED with exception]\n")
            result_file.write("\tERROR: " + str(e) + "\n")
            sys.stderr.write("CASE " + str(case) + ": [FAILED with exception]\n")
            sys.stderr.write("\tERROR: " + str(e) + "\n")
    except:
        sys.stderr.write('Module cannot be imported\n')

