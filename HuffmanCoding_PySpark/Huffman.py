#!/usr/local/bin/python
import json
from operator import add
from array import *
from NodeTree import NodeTree
import re

def mASCII(str):
    ascii_str = ''
    x = re.findall('.{16}|.+', str)
    for i in range(0, len(x)):
        ascii_str += unichr(int(x[i][0:len(x[i])].ljust(16, '0'), 2))
    return ascii_str

def mBin(str):
    return bin(ord(str))[2:].rjust(16,'0')

def decom(tmp):
    # load from file for decompression:
    with open('huff_binCodeTest.json', 'r') as f:
        try:
            huff_bin = json.load(f)
        # if the file is empty the ValueError will be thrown
        except ValueError:
            huff_bin = {}
    pointer = 0
    decompressed_str = ''
    for i in range(pointer, len(tmp)-1):
        code = huff_bin.get(tmp[pointer:i+1])
        if code is not None:
            decompressed_str += code
            pointer = i+1
    return decompressed_str

## Tansverse the NodeTress in every possible way to get codings
def huffmanCodeTree(node, left=True, binString=""):
    if type(node) is unicode:
        return {node: binString}
    (l, r) = node.kids()
    d = dict()
    d.update(huffmanCodeTree(l, True, binString + "0"))
    d.update(huffmanCodeTree(r, False, binString + "1"))
    return d

lines = sc.wholeTextFiles("s3n://<AWS_ACCESS_KEY_ID>:<AWS_SECRET_ACCESS_KEY>@spark.huffman/gutenberg")

counts = lines.flatMap(lambda x: x[1]).map(lambda x: (x, 1)).reduceByKey(add).sortByKey(False)
freq = {}
freq = counts.collectAsMap()

#Sort the frequency table based on occurrence this will also convert the
#dict to a list of tuples
freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)
nodes = freq

while len(nodes) > 1:
    key1, c1 = nodes[-1]
    key2, c2 = nodes[-2]
    nodes = nodes[:-2]
    node = NodeTree(key1, key2)
    nodes.append((node, c1 + c2))
    # Re-sort the list
    nodes = sorted(nodes, key=lambda x: x[1], reverse=True)

huffmanCode = huffmanCodeTree(nodes[0][0])

bitCount = 0
bitCountBefore = 0
print("  Char    |  Freq     |  Length  |          Huffman code ")
print("------------------------------------------------------------------")
for char, frequency in freq:
    print("%10d| %9d | %8d | %28s" % (ord(char), frequency, len(huffmanCode[char]), huffmanCode[char]))
    bitCount += len(huffmanCode[char]) * frequency
    bitCountBefore += 8 * frequency

# Write huffmanCode to file for decompression
# need to swap key and values here
#my_huffmanCode = {y: x for x, y in huffmanCode.items()}

# Converting the characters to binary codes
binaryRDD = lines.flatMap(lambda x: x[1]).map(lambda x: huffmanCode[x])

n = binaryRDD.mapPartitions(lambda iterator: [''.join(iterator)]).map(mASCII)

# print("Count of the bits after compression:   %8d " % bitCount)
print("Size after compression:  MB %8f" % (bitCount/(1.0*(2**23))))
# print("Count of the bits before compression:  %8d " % bitCountBefore)
print("Size before compression: MB %8f" % (bitCountBefore/(1.0*(2**23))))
print("Compression rate:  %8f Percent " % ((bitCount/(1.0*bitCountBefore)*100)))

# it is better to use saveAsHadoopFile or saveAsSequenceFile to save as unicode string resulting in correct compression
