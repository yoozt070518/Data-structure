# 队列
- 特点：先进先出，后进后出

## 顺序队列的缺陷
- 由于队列是由一个first和rear操作的数组
- 每次入队和出队都会执行加加操作
- 会导致始终访问不到前面的位置
- 从而导致空间浪费

## 环形队列
- 不去执行rear++的操作
- 执行rear = (rear+1) % lenth
- 这样当rear跑完整个队列之后又会回到起始位置

### 操作
1. 判空
    - first == rear
    - **注意：由于这种判空的方式 因此我们一般不会让环形队列的first和rear相等 也就是留出一个空间不用**
2. 入队
    - arr[rear] = val;
    - rear = (rear+1) % lenth;
3. 出队
    - first = (first+1) % lenth;
4. 判满
   - (rear+1) % lenth == first