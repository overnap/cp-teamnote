priority_queue<int> pq, eraser;
pq.push(value), eraser.push(value);
while (!pq.empty() && !eraser.empty() && pq.top == eraser.top())
    pq.pop(), eraser.pop();