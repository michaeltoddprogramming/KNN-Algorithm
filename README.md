# KNN-Algorithm
The k-Nearest Neighbors algorithm implemented in C++

# What is the KNN Algorithm?
It is a simple and widely used supervised machine learning algorithm for classification and regression tasks. It operates on the principle that similar data points are likely to belong to the same class or have similar numeric values.

# How it works...
Training Phase: The algorithm stores the entire training dataset in memory.

Prediction Phase: When a new input is provided, the algorithm calculates the distance between the input and all points in the training dataset. The "k" nearest neighbors are then identified based on the calculated distances.

Classification (or Regression): For classification tasks, the algorithm assigns the most common class among the k neighbors to the new input. For regression tasks, it calculates the average (or weighted average) of the target values of the k neighbors and assigns this as the predicted value.
