#include <memory.h>

#include <cstdio>
using namespace std;
typedef long long ll;

int dp[31][10001];
int bitMask[31];
int maxValueSum[31];
int minValueSum[31];
int divisor, upperLimit;

int calculateSubsetCount(int bitIndex, int remainder) {
    if (bitIndex == -1) {
        if (remainder == 0) return 1;
        return 0;
    }
    if (dp[bitIndex][remainder] != -1) return dp[bitIndex][remainder];

    int subsetCount = calculateSubsetCount(bitIndex - 1, (remainder + (1 << bitIndex)) % divisor);
    if (!bitMask[bitIndex]) subsetCount += calculateSubsetCount(bitIndex - 1, remainder);

    return dp[bitIndex][remainder] = subsetCount;
}

int calculateValidSubsets(int bitIndex, int currentSum) {
    if (currentSum + (ll)minValueSum[bitIndex] > upperLimit) return 0;
    if (currentSum + (ll)maxValueSum[bitIndex] <= upperLimit) return calculateSubsetCount(bitIndex, currentSum % divisor);

    int subsetCount = calculateValidSubsets(bitIndex - 1, (currentSum + (1 << bitIndex)));
    if (!bitMask[bitIndex]) subsetCount += calculateValidSubsets(bitIndex - 1, currentSum);
    return subsetCount;
}

int main() {
    int bitCount, bitPosition, bitMaskValue = 0, validSubsetCount = 0;
    scanf("%d %d %d", &bitCount, &divisor, &upperLimit);
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < bitCount; i++) {
        scanf("%d", &bitPosition);
        bitMask[bitPosition] = 1;
        bitMaskValue |= 1 << bitPosition;
    }

    if (divisor > 10000) {
        for (ll i = divisor; i <= upperLimit; i += divisor)
            if ((i & (ll)bitMaskValue) == (ll)bitMaskValue) validSubsetCount++;
        return !printf("%d", validSubsetCount);
    }

    for (int i = 0; i < 31; i++) {
        maxValueSum[i] = 1 << i;
        if (i) maxValueSum[i] += maxValueSum[i - 1];

        minValueSum[i] = (1 << i) * bitMask[i];
        if (i) minValueSum[i] += minValueSum[i - 1];
    }

    validSubsetCount = calculateValidSubsets(30, 0);
    if (bitCount == 0) validSubsetCount--;

    printf("%d", validSubsetCount);
}
