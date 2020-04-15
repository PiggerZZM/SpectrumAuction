# 属性感知的经济鲁棒拍卖

毕设的cpp实现，一个小小的demo，可以模拟买卖双方获胜数量都为3的情形。

## 几点说明

1. 由于作者编程能力有限，程序目前写死了买卖双方的报价，保证双方的获胜数量都为3。
2. 一致性检验和组合一致性检验如果不通过，程序将直接终止。
3. 成对比较矩阵是随机生成的。为了能通过一致性检验使程序运行到底，目前的生成方法能保证出来的矩阵是一致性矩阵。
4. 为了能使程序运行到底，暂时注释掉了组合一致性检验。
5. 为了毕设展示的方便，干扰图目前写死为完全图，后续不难修改为可手动输入
