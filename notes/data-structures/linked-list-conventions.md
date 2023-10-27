# Head and Tail Conventions in Linked Lists[^1]

This table gives implementations of basic list-processing operations with four commonly used conventions. This type of code is used in simple applications where the list-processing code is inline.

## Circular, Never Empty

| operation           | code                                                         |
| ------------------- | ------------------------------------------------------------ |
| *first insert*      | `head.next = head;`                                          |
| *insert t after x*  | `t.next = x.next; x.next = t`                                |
| *remove after x*    | `x.next = x.next.next;`                                      |
| *traversal Loop*    | `t = head;` <br/> `do {... t = t.next; } while(t != head);` |
| *test if one item*  | `if(head.next == head)`                                     |

## Head Reference, Null Tail

| operation           | code                                                                                           |
| ------------------- | ---------------------------------------------------------------------------------------------- |
| *initialize*        | `head = null;`                                                                                 |
| *insert t after x*  | `if(x == null){ head = t; head.next = null; }` <br/> `else { t.next = x.next; x.next = t; }`   |
| *remove after x*    | `t = x.next; x.next = t.next;`                                                                 |
| *traversal Loop*    | `for(t = head; t != null; t = t.next)`                                                         |
| *test if empty*     | `if(head == null)`                                                                             |

## Dummy Head Node, Null Tail

| operation           | code                                                                                           |
| ------------------- | ---------------------------------------------------------------------------------------------- |
| *initialize*        | `head = new Node();` <br/> `head.next = null;`                                                 |
| *insert t after x*  | `t.next = x.next; x.next = t;`                                                                 |
| *remove after x*    | `t = x.next; x.next = t.next;`                                                                 |
| *traversal Loop*    | `for(t = head.next; t != null; t = t.next)`                                                    |
| *test if empty*     | `if(head.next == null)`                                                                        |

## Dummy Head Node and Tail Nodes

| operation           | code                                                                                           |
| ------------------- | ---------------------------------------------------------------------------------------------- |
| *initialize*        | `head = new Node();` <br/> `z = new Node();` <br/> `head.next = z; z.next = z;`                |
| *insert t after x*  | `t.next = x.next; x.next = t;`                                                                 |
| *remove after x*    | `x.next = x.next.next;`                                                                        |
| *traversal Loop*    | `for(t = head.next; t != z; t = t.next)`                                                       |
| *test if empty*     | `if(head.next == z)`                                                                           |

[^1]: Section 3.4 Page 103 Algorithms in Java Third Edition Parts 1-4 by Robert Sedgewick
