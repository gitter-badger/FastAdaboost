Fast Adaboost 
===============================================

Fast Adaboost is a adaboost library for classification task implemented in C++.AdaBoost, short for Adaptive Boosting, is a meta machine learning algorithm that can be used in conjunction with many other learning algorithms to improve their performance.Its main idea is to use weak learner to create strong learners and subsequent classifiers builtare tweaked in favor of those instances misclassified by previous classifier.One kind of weak classifiers is decision tree that uses some heuristics to find suboptimal trees such as using information gain or gini impurity.However most of those heuristics are too slow .This library aims at implementing a fast ada-boost library based on decision tree classifiers. Also , I will use feature hashing trick to deal with high dimension sparse data

===============================================
To compile and build the program, you need to install boost library http://www.boost.org/users/download/

After install the boost library,just input "make" under BoostedDecisionTree/BoostedDecisionTree/

===============================================
<h5>FFast Heuristic Decision Tree</h5>

Preprocessing the data by clustering data points with same label and data points with close value along each feature.
Try to find the best value threshold along each feature.

===============================================
<h5>Feature Hashing</h5>

Feature hashing is an effective strategy for dimensionality reduction and practical nonparametric estimation.Feature Hashing for Large Scale Multitask Learning show that interaction between random subspaces is negligible with high probability.
In this library I apply feature hashing to the data to further speed up the learning and predicting phase.
