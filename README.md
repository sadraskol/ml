# Algebra

Algebra is a personal learning project. The goals are to rediscover c++ with
this [books](http://neuralnetworksanddeeplearning.com/chap1.html)'
code reimplementation. It mostly contains experiments and unoptimized code,
but i guessed that you should already know that since it has only learning
purposes.

If you have suggestion on the code itself or the tooling used, i am open to
learn cool new stuff.

## Building

The code should be easily compile on any unix compatible OS, but it's not
tested. Dependencies are contained in the `/deps` directory.

To run the code you should be running

```` bash
make && ./bin/run
````

Test are launched with `make test` command.

## Acknowledgments

Neural network is highly inspired by:
Michael A. Nielsen, "Neural Networks and Deep Learning", Determination Press, 2015

The original python code is available at
[https://github.com/mnielsen/neural-networks-and-deep-learning](https://github.com/mnielsen/neural-networks-and-deep-learning.git)
