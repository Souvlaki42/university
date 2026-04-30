// An improved queue class for characters.
class Queue {
  // these members are now private
  private char q[]; // this array holds the queue
  private int putloc, getloc; // the put and get indices

  Queue(int size) {
    q = new char[size]; // allocate memory for queue
    putloc = getloc = 0;
  }

  // Put a characer into the queue.
  void put(char ch) {
    if(putloc==q.length) {
      System.out.println(" -- Queue is full.");
      return;
    }

    q[putloc++] = ch;
  }

  // Get a character from the queue.
  char get() {
    if(getloc == putloc) {
      System.out.println(" -- Queue is empty.");
      return (char) 0;
    }

    return q[getloc++];
  }
}

class QueueDemo {
  public static void main(String args[]) {
    Queue queue = new Queue(10);
    for (int i = 0; i < 10; i++) {
      queue.put((char)('A' + i));
    }
    for (int i = 0; i < 10; i++) {
      System.out.println(queue.get());
    }
  }
}