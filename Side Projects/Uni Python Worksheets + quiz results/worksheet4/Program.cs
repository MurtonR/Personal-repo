using System.Diagnostics;
using System.Net.Sockets;
using System.Runtime.CompilerServices;

namespace comp101_worksheet4
{
    class Program
    {
        public static void Main(string[] args)
        {
            Stack stack = new Stack(2);
            stack.Push(1);
            stack.Push(2);
            stack.Push(3);
            
            Console.WriteLine(stack.Pop());
            Console.WriteLine(stack.Pop());
            Console.WriteLine(stack.Pop());
            
            Console.WriteLine("Queue: ");
            Queue queue = new Queue(2);
            queue.Enqueue(1);
            queue.Enqueue(2);
            Console.WriteLine(queue.Dequeue());
            Console.WriteLine(queue.Dequeue());
        }
    }

    public class Stack
    {
        public const int ERROR_VALUE = -1;
        int size = 0;
        List<int> stackList;
        public Stack(int initialSize)
        {
            stackList = new List<int>();
            size = initialSize;
        }

        public void Push(int item)
        {

            stackList.Insert(0, item);
        }

        void EnsureCapacity(int newCap)
        {
          
        }

        public int Pop()
        {
            if (stackList.Count == 0)
            {
                return ERROR_VALUE;
            }
            else
            {

                int pop = stackList.First();
                stackList.RemoveAt(0);
                return pop;
            }
           
        }

        public int Peek()
        {
            if (stackList.Count == 0)
            {
                return ERROR_VALUE;
            }
            else
            {


                int peek = stackList.First();
                return peek;
            }

        }

        public bool IsEmpty()
        {
            if (stackList.Count == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        

        public int GetSize()
        {
            return stackList.Count();
        }

    }

    public class Queue
    {
        public const int ERROR_VALUE = -1;
        int size = 0;
        List<int> queueList;

        public Queue(int capacity)
        {
            queueList = new List<int>();
        }

        public int Front()
        {
            if (queueList.Count == 0)
            {
                return ERROR_VALUE;
            }
            else
            {

                int front = queueList.First();
                return front;
            }
        }
        
        public void Enqueue(int item)
        {
            queueList.Add(item);

        }

        public int Dequeue()
        {
           
            if ( queueList.Count == 0)
            {
                return ERROR_VALUE;
            }
            else
            {

                int dequeue = queueList.First();
                queueList.RemoveAt(0);
                return dequeue;
            }

        }

        public bool IsEmpty()
        {

            if (queueList.Count == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public int GetSize()
        {
            return queueList.Count();
        }
    }
}