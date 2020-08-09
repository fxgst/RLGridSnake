# RLGridSnake

Implementation of reinforcement learning using exploring starts Monte Carlo methods.

Main reinforcement learning algorithm is based on the algorithm in this [book][book_link] in chapter 5.

## Usage

Run `./run` and then open `snakeUI.html`, select the `policy.txt` file and watch the snake eating apples. The snake will not learn live, it just acts according to the learned policy. If the snake is stuck or leaves the board too often, you can adjust the parameters of the learning process in `Utils.hpp`.

[book_link]: http://incompleteideas.net/book/the-book-2nd.html
