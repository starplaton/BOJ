# 13496번 - The Merchant of Venice


=================================

2 초

512 MB

1414

885

829

62.425%

문제
--

“The Merchant of Venice” has perhaps one of the most interesting “villains” in Shylock, a Jewish moneylender who has been hurt many times and in different ways by Christians in general, and Antonio, the titular merchant, in particular. When Antonio’s friend Bassanio urgently needs to borrow 3000 ducats to woo the lady he loves, Antonio’s money is tied up in his trading fleet; instead, he signs a loan contract with Shylock promising him a pound of his own flesh in case the 3000 ducats are not repaid by the due date. When his fleet is lost in a storm, the plot thickens and the story turns more ominous.

We will ignore here the risk analysis that Antonio should probably have carried out, asking how likely each of his ships would return, and what the probability was that he would not be able to repay the money by the due date. Instead, we will focus on the question of how much money Antonio could repay Shylock by a given date, depending on where his ships are located at the start of the contract.

Specifically, you will be given the number of days until the due date and the speed at which ships travel. You will also be given, for each ship, its distance from Venice and the value of its load in ducats. You are to output the number of ducats Antonio can repay by the due date.

입력
--

The first line contains a number K ≥ 1, which is the number of input data sets in the file. This is followed by K data sets of the following form:

The first line of a data set contains three integers n, s, d; 0 ≤ n ≤ 200 is the number of ships Antonio owns, 1 ≤ s ≤ 100 is the speed of the ships in miles per day, and 1 ≤ d ≤ 365 the number of days until the contract’s due date.

This is followed by n lines, each containing two integers di, vi. 0 ≤ di ≤ 10000 is the distance of ship i from Venice, in miles, and 0 ≤ vi ≤ 100000 is the value of ship i’s load.

출력
--

For each data set, first output “Data Set x:” on a line by itself, where x is its number. Then, output the total number of ducats that Antonio could repay Shylock after d days. If a ship exactly arrives after d days, we assume that Antonio can use its cargo already to repay Shylock.

Each data set should be followed by a blank line.

제한
--

예제 입력 1
-------

2
3 20 31
42 70
1000 2000
512 121
3 10 3
29 1
30 2
31 4

예제 출력 1
-------

Data Set 1:
191

Data Set 2:
3

힌트
--

출처
--

[University](/category/5) > [The USC Programming Contest](/category/91) > [Fall 2016: Shakespeare](/category/detail/1539) A번