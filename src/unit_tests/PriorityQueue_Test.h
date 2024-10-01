/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

void PriorityQueue_Test()
{
    puts(">>PriorityQueue test start");
    PriorityQueue queue;
    int n_items = 10;
    Item items[n_items];
    for(int i=0; i<n_items; i++)
    {
        items[i].address = (void*) ((long) i+1);
        items[i].priority = 0;
    }
    PriorityQueue_INIT(&queue, items, n_items);
    for(int i=0, evictions=0; i<n_items*2; i++)
    {
        PriorityQueue_Push_Feedback feedback = PriorityQueue_Push(&queue, 1.0/((double) (n_items*2-i)));
        if(feedback.added)
        {
            printf("item was added %f %ld\n", feedback.addedItem.priority, (long)feedback.addedItem.address);
        }
        if(feedback.evicted)
        {
            printf("evicted item %f %ld\n", feedback.evictedItem.priority, (long)feedback.evictedItem.address);
            assert(evictions>0 || (feedback.evictedItem.priority - ((double)(1.0/((double) (n_items*2))))) < 0.00001, "the evicted item has to be the lowest priority one");
            assert(queue.itemsAmount < n_items+1, "eviction should only happen when full!");
            evictions++;
        }
    }
    puts("New test");
    // * 🚩【2024-10-01 13:04:57】优先队列 更强的测试
    {
        PriorityQueue queue;
        int n_items = 10;
        Item items[n_items];

        for(int i=0; i<n_items; i++)
        {
            items[i].address = 0;
            items[i].priority = 1;
        }
        PriorityQueue_INIT(&queue, items, n_items);
        for(int i=0, evictions=0; i<n_items; i++)
        {
            for(int i=0; i<queue.itemsAmount; i++)
            {
                Item c = queue.items[i];
                printf("%ld ", (long)c.address);
            }
            printf(" -> ");
            PriorityQueue_Push_Feedback feedback = PriorityQueue_Push(&queue, 1.0);
            if(feedback.added)
            {
                feedback.addedItem.address = (void*) ((long) i+1);
                queue.items[queue.itemsAmount-1] = feedback.addedItem;
            }
            for(int i=0; i<queue.itemsAmount; i++)
            {
                Item c = queue.items[i];
                printf("%ld ", (long)c.address);
            }

            if(feedback.added)
            {
                printf("item was added %f %ld\n", feedback.addedItem.priority, (long)feedback.addedItem.address);
            }
            if(feedback.evicted)
            {
                printf("evicted item %f %ld\n", feedback.evictedItem.priority, (long)feedback.evictedItem.address);
                evictions++;
            }
        }
    }
    puts("<<PriorityQueue test successful");
}
