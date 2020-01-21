/**
 * 支持栈的Push和Pop操作以及第三种操作FindMin的数据结构
 * FindMin返回该数据结构最小元素
 * 所有操作在最坏的情况下的运行时间都是O(1)
 * */
/**
 * Let E be our extended stack. We will implement E with two stacks. One stack, 
 * which we’ll call S, is used to keep track of the Push and Pop operations, 
 * and the other, M, keeps track of the minimum. To implement Push(X,E), we 
 * perform Push(X,S). If X is smaller than or equal to the top element in stack 
 * M, then we also perform Push(X,M). To implement Pop(E), we perform Pop(S). 
 * If X is equal to the top element in stack M, then we also Pop(M). FindMin(E) 
 * is performed by examining the top of MO. All these operations are clearly O
 * (1).
 * 让 E 成为我们的扩展堆栈。我们将用两个堆栈实现 E。一个堆栈，我们称之为S，用于跟踪推送和弹出操
 * 作，另一个，M，跟踪最小值。为了实现推送（X，E），我们执行推送（X，S）。如果 X 小于或等于堆
 * 栈 M 中的顶部元素，则我们还执行 Push（X，M）。为了实现 Pop（E），我们执行 Pop（S）。如果 
 * X 等于堆栈 M 中的顶部元素，则我们也弹出（M）。FindMin（E）是通过检查 MO 的顶部来执行的。所
 * 有这些操作显然是 O（1）。
 * */

/**
 * 证明，如果我们加入第四种操作DeleteMin，那么至少有一种操作必须花Ω(log N)时间
 * */
/**
 * This result follows from a theorem in Chapter 7 that shows that 
 * sorting must take Ω(N log N) time. O(N) operations in the 
 * repertoire, including DeleteMin, would be sufficient to sort. 
 * */
