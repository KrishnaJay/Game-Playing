# Game-Playing
Project description

This project is a practical implementation of game developement.
In a typical zero sum two player game, players are generally competing for a
certain common resource, and their gain is a function of their share of the resource. Often players
have other challenges such as satisfying other constraints on other personal resources such as
time, energy or computational power in the course of the game. This is a game that captures the nature of a zero sum two player game with
strict limitation on allocated time for reasoning.
The task is creating a software agent that can play this game against a human or another agent.

Rules of the game

The Fruit Rage is a two player game in which each player tries to maximize his/her share from a
batch of fruits randomly placed in a box. The box is divided into cells and each cell is either empty
or filled with one fruit of a specific type.
At the beginning of each game, all cells are filled with fruits. Players play in turn and can pick a
cell of the box in their own turn and claim all fruit of the same type, in all cells that are connected
to the selected cell through horizontal and vertical paths. For each selection or move the agent
is rewarded a numeric value which is the square of the number of fruits claimed in that move.
Once an agent picks the fruits from the cells, their empty place will be filled with other fruits on
top of them (which fall down due to gravity), if any. In this game, no fruit is added during game
play. Hence, players play until all fruits have been claimed.
Another big constraint of this game is that every agent has a limited amount of time to spend for
thinking during the whole game. Spending more than the original allocated time will be penalized
harshly. Each player is allocated a fixed total amount of time. When it is your turn to play, you
will also be told how much remaining time you have. The time you take on each move will be
subtracted from your total remaining time. If your remaining time reaches zero, your agent will
automatically lose the game. Hence you should think about strategies for best use of your time
(spend a lot of time on early moves, or on later moves?)
The overall score of each player is the sum of rewards gained for every turn. The game will
terminate when there is no fruit left in the box or when a player has run out of time.


Approach and comments:
The initial approach was to enumerate all the possible combinations till the end at a given stage and determine the next best move using mini-max algorithm. This naive approach is slow and inefficient from the runtime and memory point of view. 
The fix was to use alpha-beta pruning which skips the moves that are guaranteed to not contribute dowards the decision. 

