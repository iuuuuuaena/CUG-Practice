# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    # print("Start:", problem.getStartState())
    # print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    stack1 = util.Stack()
    stack2 = util.Stack()
    stack1.push(problem.getStartState())
    stack2.push([])
    searched = set()
    while not stack1.isEmpty():
        state = stack1.pop()
        path = stack2.pop()
        if problem.isGoalState(state):
            return path
        searched.add(state)
        for new in problem.getSuccessors(state):
            if new[0] not in searched and new[0] not in stack2.list:
                stack1.push(new[0])
                stack2.push(path+[new[1]])

    # return []
    # util.raiseNotDefined()

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    queue1=util.Queue()
    queue2=util.Queue()
    searched = set()
    queue1.push(problem.getStartState())
    queue2.push([])
    # print("Start:", problem.getStartState())
    # print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    searched.add(problem.getStartState())
    while not queue1.isEmpty():
        state = queue1.pop()
        path = queue2.pop()
        if problem.isGoalState(state):
            return path
        for new in problem.getSuccessors(state):
            if new[0] not in queue1.list and new[0] not in searched:
                searched.add(new[0])
                queue1.push(new[0])
                queue2.push(path+[new[1]])
    # util.raiseNotDefined()

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    # print("Start:", problem.getStartState(),type(problem.getStartState()))
    # print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    # print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    # from searchAgents import manhattanHeuristic
    # class Node:
    #     def __init__(self,state,parent,f,g,h,action=''):
    #         self.state=state
    #         self.parent=parent
    #         self.f=f
    #         self.g=g
    #         self.h=h
    #         self.action=action
    # def minNode(nodes:list):
    #     current=nodes[0]
    #     for node in nodes:
    #         if node.f<current.f:
    #             current=node
    #     return current
    # def contain(nodes:list,state):
    #     for n in nodes:
    #         if state==n.state:
    #             return n
    #     return None
    # open_list=list()
    # close_list=list()
    # start=problem.getStartState()
    # start_node=Node(start,None,manhattanHeuristic(start,problem),0,manhattanHeuristic(start,problem))
    # open_list.append(start_node)
    # goal=None
    # i=0
    # while not goal and len(open_list)!=0:
    #     node=minNode(open_list)
    #     open_list.remove(node)
    #     close_list.append(node)
    #     for state,action,_ in problem.getSuccessors(node.state):
    #         if not contain(close_list,state):
    #             temp=contain(open_list,state)
    #             if not temp:
    #                 g=node.g+1
    #                 h=manhattanHeuristic(state,problem)
    #                 newNode=Node(state,node,g+h,g,h,action)
    #                 open_list.append(newNode)
    #                 if problem.isGoalState(state):
    #                     goal=newNode
    #             else:
    #                 if temp.g>node.g+1:
    #                     temp.parent=node
    #                     temp.g=node.g+1
    #                     temp.f=temp.g+temp.h
    # result=util.Queue()
    # if goal:
    #     while(goal.parent):
    #         result.push(goal.action)
    #         goal=goal.parent
    # return result.list
    fringe = util.PriorityQueue()
    # Make an empty list of explored nodes
    visited = []
    # Make an empty list of actions
    actionList = []
    # Place the starting point in the priority queue
    fringe.push((problem.getStartState(), actionList), heuristic(problem.getStartState(), problem))
    while fringe:
        node, actions = fringe.pop()
        if not node in visited:
            visited.append(node)
            if problem.isGoalState(node):
                return actions
            for successor in problem.getSuccessors(node):
                coordinate, direction, cost = successor
                nextActions = actions + [direction]
                nextCost = problem.getCostOfActions(nextActions) + \
                           heuristic(coordinate, problem)
                fringe.push((coordinate, nextActions), nextCost)
    return []
    # util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
