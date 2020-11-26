# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        return successorGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        def maxmin(state, depth, agentIndex):
            numGhosts=state.getNumAgents()-1
            if state.isWin() or state.isLose() or depth == 0:
                return self.evaluationFunction(state)
            legalMoves=state.getLegalActions(agentIndex)
            if agentIndex == 0:
                scores = [maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1) for action in legalMoves]
                return max(scores)
            if agentIndex == numGhosts:
                scores = [maxmin(state.generateSuccessor(agentIndex, action), depth - 1, 0) for action in legalMoves]
                return min(scores)
            scores = [maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1) for action in legalMoves]
            return min(scores)
        legalMoves = gameState.getLegalActions(0)
        scores = [maxmin(gameState.generateSuccessor(0,action),self.depth,1) for action in legalMoves]
        bestScore=max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices)  # Pick randomly among the best
        return legalMoves[chosenIndex]
        # util.raiseNotDefined()

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        def maxmin(state, depth, agentIndex,alpha,beta):
            # ghost的数量
            numGhosts=state.getNumAgents()-1
            if state.isWin() or state.isLose() or depth == 0:
                return self.evaluationFunction(state)
            # 当前状态传入agent的合法action
            legalMoves=state.getLegalActions(agentIndex)
            # pacman 选择最大值
            if agentIndex == 0:
                # 下一层是ghost
                score=-float('inf')
                for action in legalMoves:
                    score=max(score,maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1,alpha,beta))
                    if score>beta:
                        return score
                    alpha=max(alpha,score)
                return score
            # ghost 选取最小值
            # 最后一个ghost
            score = float('inf')
            if agentIndex == numGhosts:
                # 下一次是pacman
                for action in legalMoves:
                    score=min(score,maxmin(state.generateSuccessor(agentIndex, action), depth - 1, 0,alpha,beta))
                    if score<alpha:
                        return score
                    beta=min(beta,score)
                return score
            # 其他ghost 下一层还是ghost
            for action in legalMoves:
                score = min(score, maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1, alpha, beta))
                if score < alpha:
                    return score
                beta = min(beta, score)
            return score

        #------------------------------------------------------------
        legalMoves = gameState.getLegalActions(0)
        score=-float('inf')
        alpha=-float('inf')
        beta=float('inf')
        # 选择最好的action
        bestMove=Directions.STOP
        for action in legalMoves:
            new_score=max(score,maxmin(gameState.generateSuccessor(0,action),self.depth,1,score,beta))
            if score<new_score:
                score=new_score
                bestMove=action
            # if score>=beta:
            #     return bestMove
            # alpha=max(alpha,score)
        return bestMove

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"

        def maxmin(state, depth, agentIndex):
            # ghost的数量
            numGhosts = state.getNumAgents() - 1
            if state.isWin() or state.isLose() or depth == 0:
                return self.evaluationFunction(state)
            # 当前状态传入agent的合法action
            legalMoves = state.getLegalActions(agentIndex)
            # pacman 选择最大值
            if agentIndex == 0:
                # 下一层是ghost
                scores = [maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1) for action in
                          legalMoves]
                return max(scores)
            # ghost 选取期望值
            # 最后一个ghost
            numActions=len(legalMoves)
            if agentIndex == numGhosts:
                # 下一次是pacman
                scores = [maxmin(state.generateSuccessor(agentIndex, action), depth - 1, 0) for action in legalMoves]
            # 其他ghost 下一层还是ghost
            else:
                scores = [maxmin(state.generateSuccessor(agentIndex, action), depth, agentIndex + 1) for action in
                      legalMoves]
            return sum(scores)/numActions

        # ----------------------------------------
        legalMoves = gameState.getLegalActions(0)
        # 选择最好的action
        scores = [maxmin(gameState.generateSuccessor(0, action), self.depth, 1) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices)  # Pick randomly among the best
        return legalMoves[chosenIndex]
        # util.raiseNotDefined()
from pacman import GameState
def betterEvaluationFunction(currentGameState:GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    # 首先判断当前是否已经结束
    if currentGameState.isWin():
        return float('inf')
    if currentGameState.isLose():
        return -float('inf')
    score = currentGameState.getScore()
    # 考虑food
    foods = currentGameState.getFood().asList()
    foodDis=[util.manhattanDistance(currentGameState.getPacmanPosition(),food) for food in foods]
    foodDis.sort(reverse=True)
    numFoods = 3
    if currentGameState.getNumFood()<3:
        numFoods=currentGameState.getNumFood()
    score-=foodDis[0]*1.5
    # for i in range(numFoods):
    #     score-=(numFoods-i)*foodDis[i]
    # 如果附近有food 最好可以吃到
    score-=(currentGameState.getNumFood()*4)
    # 考虑ghost
    ghostDis=[util.manhattanDistance(currentGameState.getPacmanPosition(),ghost) for ghost in currentGameState.getGhostPositions()]
    score+=max(3,min(ghostDis))*2
    # 考虑capsule
    score-=len(currentGameState.getCapsules())*4
    return score
    # util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
