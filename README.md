# Huffman Coding Algorithm

We are creating and consuming data more than ever before. Data from different fields like social media, health, education scientific research, etc. are increasing. Due to the exponential increase in data, a new field for focusing the efficient utilization of enormous amount of data has been introduced which is known as Big Data. Big data are those datasets whose size is beyond the capability of typical database software tools to capture, store, manage and analyze. Big data creates new opportunities and values that helps to gain in-depth understanding of the associated data.

One of the major concerns in big data is to store the enormous volume of data efficiently. Every second vast amount of data is being generated. This requires state of the art technique to store them.Traditional database techniques are incapable of handling the massive flow of data. Although the cost of storage technique is cheaper than before, the cost of storage may not cope up with the rate at which the data are being produced making the storage unsustainable. One way of handling this problem is to get rid of the data, but the risk associated with it is significant and the solution might not be an optimum one. Therefore, One of the most favorable solution is to compress the data and store them. If data size can be reduced by using compression techniques, then it will make a significant contribution saving the volume and hence cost.

Compression can be one of the viable technique to handle this issue. Apache Spark is a cluster computing general data processing platform. Apache Spark2 has been increasingly in use for handling various big data analysis. Though, various compression techniques have already been implemented in Apache Spark, Huffman Coding Algorithm has not yet been implemented for data compression in Spark. Huffman coding algorithm is a lossless data compression algorithm which is based on the frequency of occurrence of a data item.

In this project we have tried to:
* Implement Huffman Coding Algorithm to achieve maximum compression.
* Measure time taken by Spark to achieve above mentioned compression in various system configurations.

This project was implemented in generic parallel programming model using MapReduce. MapReduce allows simplified data processing on large clusters enabling inexperienced developers to use parallel and large distributed system with an ease.
