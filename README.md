# push_swap

push_swap is a program that will sort a list of integers using two stacks.

## Performance Test
To test the performance of this push_swap you can generate lists of random numbers, run them through `push_swap`, and then check them with `checker` all in one line using the following command
```
ARGS=($(shuf -i "0-1000" -n 500)) && ./push_swap $ARGS | ./checker $ARGS && ./push_swap $ARGS | wc -l
```
sample output
```
OK
6153
```
Where `6153` is the number of operations performed, and will vary on each run.
The number of numbers in the list can be changed by changing the `-n` option from `500` to any positive integer.
